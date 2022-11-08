/*
10. Написать программу умножения матрицы на вектор $`z = Ax`$. Распределить
матрицу `А` равномерно вдоль строк, вектор х передать всем процессам. После
выполнения операции умножения матрицы на вектор на каждом процессе необходимо
выполнить сбор полученных локальный частей результирующего вектора на один из
процессов. Использовать функцию `MPI_Bcast` для рассылки вектора `x`, для
распределения элементов матрицы использовать функцию `MPI_Scatter`, для сбора
локальных частей результирующего вектора в глобальный вектор использовать
функцию `MPI_Gather`.
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <mpi.h>

#define ANY_TAG_NUMBER 123
#define MASTER_PROCESS 4

constexpr int N = 8;
constexpr int M = 4;
constexpr int rowCount = N/M;

typedef struct {
    int mat[N][N];
} datarow_t;

int main(int argc, char **argv) {

	MPI_Init(&argc, &argv);

    int global_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);

	int global_size;
	MPI_Comm_size(MPI_COMM_WORLD, &global_size);

	if (global_size != 5) {
		if (global_rank == MASTER_PROCESS) {
			printf("Not enough processors! Need exactly %d\n", 5);
		}

		MPI_Finalize();
		return 1;
	}




    if (global_rank == MASTER_PROCESS) {

        MPI_Datatype types[rowCount] = { MPI_INT, MPI_INT };
        int blocklens[rowCount] = {N, N};
        MPI_Aint displs[rowCount] = { offsetof(datarow_t, mat[0]), offsetof(datarow_t, mat[M]) };

        MPI_Datatype parttype;
        MPI_Type_create_struct(rowCount, blocklens, displs, types, &parttype);
        MPI_Type_commit(&parttype);

        int a[N][N];
        printf("Init Matrix a\n");
        for (int i = 0; i < N; ++i) {
            printf("\t");
            for (int j = 0; j < N; ++j) {
                a[i][j] = i * N + j + 10;
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        MPI_Send(&(a[0][0]), 1, parttype, 0, ANY_TAG_NUMBER, MPI_COMM_WORLD);
        MPI_Send(&(a[1][0]), 1, parttype, 1, ANY_TAG_NUMBER, MPI_COMM_WORLD);
        MPI_Send(&(a[2][0]), 1, parttype, 2, ANY_TAG_NUMBER, MPI_COMM_WORLD);
        MPI_Send(&(a[3][0]), 1, parttype, 3, ANY_TAG_NUMBER, MPI_COMM_WORLD);

    } else if (global_rank != MASTER_PROCESS) {

    // rcv on another processes
    int c[rowCount][N];
    MPI_Recv(&(c[0][0]), rowCount * N, MPI_INT, MASTER_PROCESS, ANY_TAG_NUMBER, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::stringstream ss;
    ss << "Proc number " << global_rank << " recv rows:\n";
    for (int i = 0; i < rowCount; ++i) {
        ss << "\t";
        for (int j = 0; j < N; ++j) {
            ss << c[i][j] << " ";
        }
        ss << std::endl;
    }
    std::cout << ss.str();
    }
    MPI_Finalize();
    return 0;
}