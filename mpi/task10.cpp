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
#include <mpi.h>

using namespace std;

// matrix size, N rows * M columns
constexpr int N = 10;
constexpr int M = 5;

void init_matrix(int min, int max, int *arr, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; j++) {
			arr[i * M + j] = rand() % (max - min) + min;
		}
	}
}

void init_array(int min, int max, int *a, int size) {
	for (auto i = 0; i < size; i++) {
		a[i] = rand() % (max - min) + min;
	}
}

void print_matrix(int *arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d\t", arr[i * M + j]);
		}
		printf("\n");
	}
}

void print_array(int *a, int size) {
	for (auto i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void dot_product(int *a, int *b, int size, int *result) {
	*result = 0;
	for (auto i = 0; i < size; i++) {
		*result += a[i] * b[i];
	}
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	srand(time(0));

	int global_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);

	int global_size;
	MPI_Comm_size(MPI_COMM_WORLD, &global_size);

	if (global_size != N) {
		if (global_rank == 0) {
			printf("Not enough processors! Need exactly %d\n", N);
		}

		MPI_Finalize();
		return 1;
	}

	int *matrix;
	int row[M], vec[N], result[N];

	if (global_rank == 0) {
		// alloate matrix on master
		matrix = new int[N * M];

		// init matrix and column vector on master
		init_matrix(-10, 10, matrix, N, M);
		init_array(-10, 10, vec, N);

		printf("Matrix A:\n");
		print_matrix(matrix, N, M);

		printf("Column vector x:\n");
		print_array(vec, N);
	}

	MPI_Bcast(vec, N, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(matrix, M, MPI_INT, row, M, MPI_INT, 0, MPI_COMM_WORLD);

	// multiply row by column
	int dot;
	dot_product(row, vec, M, &dot);

	MPI_Gather(&dot, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (global_rank == 0) {
		printf("Result row vector:\n");
		print_array(result, N);

		delete[] matrix;
	}

	MPI_Finalize();

	return 0;
}
