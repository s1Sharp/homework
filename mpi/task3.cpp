#include "mpi.h"
#include <iostream>
#include <limits>
#include <array>
#include <memory>
#include "stdlib.h"
#include "math.h"

#include "randvector.h"

#define MAS_SIZE 10
#define GENERAL_PROCESS 0
#define SIDE_PROCESS 1
#define SEND_ANY_TAG 0

#define USE_GET_COUNT

int main(int argc, char *argv[]){   

	srand(time(0));

    int ProcNum;
    int ProcRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == SIDE_PROCESS)
    {
        std::array<int, MAS_SIZE> a;
	    rand_vec(a.data(), MAS_SIZE);
        for (size_t i = 0; i < ProcNum; i++) {
            if (i == SIDE_PROCESS) {
                continue;
            }
            const size_t procSendTo = i;
            MPI_Send((void *)a.data(), (int)a.size(), MPI_INT, (int)procSendTo, MAS_SIZE, (MPI_Comm)MPI_COMM_WORLD);
        }
    }

    if (ProcRank != SIDE_PROCESS) {
        MPI_Status status;
        int count;
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD, &status);

#ifdef USE_GET_COUNT
        MPI_Get_count(&status, MPI_INT, &count);
#else
        count = status.MPI_TAG;
#endif

        auto buff = std::make_unique<int []>(count);
        MPI_Recv((void *)buff.get(), (int)count, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, (MPI_Comm)MPI_COMM_WORLD, &status);

        for (size_t i = 0; i < count; i++) {

#ifdef USE_GET_COUNT
        printf("Use GetCount: Elem %u\t : idx %lu\t on process %u from %u process, %s\n",
#else
        printf("Use TAG-size: Elem %u\t : idx %lu\t on process %u from %u process, %s\n",
#endif
            buff.get()[i], i, ProcRank, status.MPI_SOURCE, status.MPI_ERROR ? "no error":"error");
        }
    }

    MPI_Finalize();
}
