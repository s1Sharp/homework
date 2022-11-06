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

constexpr int N = 8;
constexpr int M = 4;

int main(int argc, char **argv) {

	MPI_Init(&argc, &argv);

    int global_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);

	int global_size;
	MPI_Comm_size(MPI_COMM_WORLD, &global_size);

	if (global_size != 3) {
		if (global_rank == 0) {
			printf("Not enough processors! Need exactly %d\n", 3);
		}

		MPI_Finalize();
		return 1;
	}

    if (global_rank == 0) {

        MPI_Datatype type;
        MPI_Datatype row;

        // Creates a contiguous datatype
        MPI_Type_contiguous(8, MPI_INT, &row);
        // Commits the datatype
        MPI_Type_commit(&row);

        // Creates a vector (strided) datatype:
        // count
        //      number of blocks (non-negative integer)
        // blocklength
        //      number of elements in each block (non-negative integer)
        // stride
        //      number of elements between start of each block (integer)
        // oldtype
        //      old datatype (handle)
        MPI_Type_vector(4, 1, 2, row, &type);
        // Commits the datatype
        MPI_Type_commit(&type);


        int a[N][N];
        printf("Init Matrix a\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = i * N + j + 10;
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        MPI_Send(&(a[0][0]), 1, type, 1, ANY_TAG_NUMBER, MPI_COMM_WORLD);
        MPI_Send(&(a[1][0]), 1, type, 2, ANY_TAG_NUMBER, MPI_COMM_WORLD);

    } else if (global_rank == 1) {
        int c[M][N];
        MPI_Recv(&(c[0][0]), M * N, MPI_INT, 0, ANY_TAG_NUMBER, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::stringstream ss;
        ss << "First:\n";
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                ss << c[i][j] << " ";
            }
            ss << std::endl;
        }
        std::cout << ss.str();
    } else if (global_rank == 2) {
        int c[M][N];
        MPI_Recv(&(c[0][0]), M * N, MPI_INT, 0, ANY_TAG_NUMBER, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::stringstream ss;
        ss << "Second:\n";
        for (int i = 0; i < M; ++i) {
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