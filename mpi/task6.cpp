/*
6. Разработать программу, в которой два процесса многократно обмениваются
сообщениями длиной `n` байт. Выполнить эксперименты и оценить зависимость
времени выполнения операции от длины сообщения. Рассмотреть два варианта обмена
сообщениями:

	a. `PingPong` - двунаправленная передача. Выполняется передача данных от
одного процесса другому с последующим возвратом переданных данных в исходный
процесс. Время выполнение замеряется после получения обратного ответа на
исходном процессе.

	b. `PingPing` - однонаправленная передача. Два процесса одновременно
выполняют передачу данных друг другу. Время выполнение замеряется после
получения сообщения каждым процессом.
*/

#include <chrono>
#include <iostream>
#include <mpi.h>
#include <string>

using namespace std;

typedef unsigned char byte_t;

// message length, bytes
const int MESSAGE_LENGTH = (1024 * 1024); // 1 MiB
// how many times a measurement should be performed
const int BENCHMARK_RUNS = (10000);
// nanoseconds to seconds
const double NNSEC_TO_SEC = (1000000000.0);

// rank of master process
const int GENERAL_PROCESS = 0;

struct BenchmarkResult {
	// how many times the code was run
	alignas(8) unsigned int runs;
	// total elapsed time, seconds
	double total_time;
	// averate time per run, seconds
	double average_time;
};

#pragma comment(linker, "/STACK:10000000")

/**
 * Benchmark a function in an MPI environment.
 * One process is allocated as master, the rest is used to run the function.
 * Slave processes are synchronized at the start and in the end.
 *
 * The function must accept a communicator that the slave processes will use.
 * MPI_COMM_WORLD must not be used as this will break the synchronization.
 *
 * The function must return a boolean value:
 * - true - the function execution time will be used to calculate average time;
 * - false - the function execution time will be ignored.
 *
 * The result is only returned for master process.
 *
 * Return status codes:
 * - 0 - ok
 * - 1 - not enough processes present
 */

int benchmark(MPI_Comm global_comm, int GENERAL_PROCESS, bool f(MPI_Comm),
			  	unsigned int runs, BenchmarkResult &result) {
	int global_rank;
	MPI_Comm_rank(global_comm, &global_rank);

	int global_size;
	MPI_Comm_size(global_comm, &global_size);

	if (global_size < 2) {
		cerr << "Cannot run a benchmark with a single process!" << endl;
		return 1;
	}

	// create slave communicator for synchronizing

	MPI_Comm slave_comm;

	const int color = global_rank != GENERAL_PROCESS ? 0 : MPI_UNDEFINED;
	MPI_Comm_split(global_comm, color, global_rank, &slave_comm);

	int slave_comm_size = global_size - 1;

	// seconds
	double total_time = 0;
	double *total_times = nullptr;

	// measure average time deltas with slave processes
	if (global_rank != GENERAL_PROCESS) {
		for (int i = 0; i < runs; i++) {
		MPI_Barrier(slave_comm);
		auto start = chrono::high_resolution_clock::now();

		bool include = f(slave_comm);

		MPI_Barrier(slave_comm);
		auto end = chrono::high_resolution_clock::now();

		if (include) {
			auto delta_ns = chrono::duration_cast<chrono::nanoseconds>(end - start);
			total_time += delta_ns.count() / NNSEC_TO_SEC;
			// cout << "delta=" << delta_ns.count() << "ns, total=" << total_time
			//      << "s" << endl;
			}
		}
	}

	// allocate buffer for deltas on master process
	if (global_rank == GENERAL_PROCESS) {
		total_times = new double[slave_comm_size];
	}

	// collect average deltas
	MPI_Gather(&total_time, 1, MPI_DOUBLE, total_times, 1, MPI_DOUBLE,
				GENERAL_PROCESS, global_comm);

	// compute average delta on master process
	if (global_rank == GENERAL_PROCESS) {
		for (int i = 0; i < slave_comm_size; i++) {
			total_time += total_times[i];
		}

		delete[] total_times;

		double avg_time = total_time / runs / slave_comm_size;

		result.total_time = total_time;
		result.runs = runs;
		result.average_time = avg_time;
	}

	return 0;
}

void print_benchmark_result(string function_identifier,
							unsigned int message_size,
							BenchmarkResult &result) {
	cout << function_identifier << ": " << message_size << "-byte message, "
		<< result.runs << " runs, avg. " << result.average_time << "s, "
		<< result.total_time << "s total" << endl;
}

bool ping_pong(MPI_Comm comm) {
	int global_rank;
	MPI_Comm_rank(comm, &global_rank);

	int global_size;
	MPI_Comm_size(comm, &global_size);

	if (global_size < 2) {
		cerr << "PingPong: not enough processes! Need at least 2" << endl;
		return false;
	}

	MPI_Comm local_comm;

	int color;
	if (global_rank == 0 || global_rank == 1) {
		color = 0;
	} else {
		return false;
	}

	MPI_Comm_split(comm, color, global_rank, &local_comm);

	int local_rank;
	MPI_Comm_rank(local_comm, &local_rank);

	// create message buffer
	byte_t* buffer = new byte_t[MESSAGE_LENGTH];

	if (local_rank == 0) {
		// send message
		MPI_Send(buffer, MESSAGE_LENGTH, MPI_BYTE, 1, 0, local_comm);

		// receive message back
		MPI_Recv(buffer, MESSAGE_LENGTH, MPI_BYTE, 1, 0, local_comm,
				MPI_STATUS_IGNORE);
	} else {
		// receive message
		MPI_Recv(buffer, MESSAGE_LENGTH, MPI_BYTE, 0, 0, local_comm,
				MPI_STATUS_IGNORE);

		// send message back
		MPI_Send(buffer, MESSAGE_LENGTH, MPI_BYTE, 0, 0, local_comm);
	}

	delete [] buffer;
	return true;
}

bool ping_ping(MPI_Comm comm) {
	int global_rank;
	MPI_Comm_rank(comm, &global_rank);

	int global_size;
	MPI_Comm_size(comm, &global_size);

	if (global_size < 2) {
		cerr << "PingPing: not enough processes! Need at least 2" << endl;
		return false;
	}

	MPI_Comm local_comm;

	int color;
	if (global_rank == 0 || global_rank == 1) {
		color = 0;
	} else {
		return false;
	}

	MPI_Comm_split(comm, color, global_rank, &local_comm);

	int local_rank;
	MPI_Comm_rank(local_comm, &local_rank);

	int other_rank = local_rank == 0 ? 1 : 0;

	// create message buffers
	byte_t* send_buffer = new byte_t[MESSAGE_LENGTH];
	byte_t* recv_buffer = new byte_t[MESSAGE_LENGTH];

	// 0 - send
	// 1 - recv
	MPI_Request requests[2];

	// receive message
	MPI_Irecv(recv_buffer, MESSAGE_LENGTH, MPI_BYTE, other_rank, 0, local_comm,
				&requests[1]);

	// send message
	MPI_Isend(send_buffer, MESSAGE_LENGTH, MPI_BYTE, other_rank, 0, local_comm,
				&requests[0]);

	// complete requests
	MPI_Waitall(2, requests, MPI_STATUS_IGNORE);

	delete [] send_buffer;
	delete [] recv_buffer;

	return true;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    int ProcNum;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    // assuming that rank 0 is master and ranks 1, 2 are slaves
    if (ProcNum != 3) {
		cerr << "Incorrect processors! Need 3! Current: " << ProcNum << endl;
		MPI_Finalize();
		return 1;
    }

    BenchmarkResult result;

    if (benchmark(MPI_COMM_WORLD, GENERAL_PROCESS, ping_pong, BENCHMARK_RUNS, result)) {
		cerr << "PingPong benchmark failed @ rank " << ProcRank << endl;
		MPI_Finalize();
		return 1;
    }
    if (ProcRank == GENERAL_PROCESS)
    	print_benchmark_result("PingPong", MESSAGE_LENGTH, result);

    if (benchmark(MPI_COMM_WORLD, GENERAL_PROCESS, ping_ping, BENCHMARK_RUNS, result)) {
		cerr << "PingPing benchmark failed @ rank " << ProcRank << endl;
		MPI_Finalize();
		return 1;
    }
    if (ProcRank == GENERAL_PROCESS)
   		print_benchmark_result("PingPing", MESSAGE_LENGTH, result);

    MPI_Finalize();
}
