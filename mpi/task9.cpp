/*
9. В массиве вещественных чисел вычислить минимальное значение и глобальный
индекс минимального элемента. Использовать функции `MPI_Scatter` и `MPI_Reduce`
с операцией `MPI_MINLOC`.
*/

#include <cstdio>
#include <mpi.h>
#include <random>

using namespace std;

constexpr int GENERAL_PROCESS = 0;
constexpr int ARRAY_SIZE = 12;

struct array_elem_pair_t {
	int elem;
	int i;
};

void print_array(array_elem_pair_t *a, int size) {
	for (auto i = 0; i < size; i++) {
		printf("%d ", a[i].elem);
	}
	printf("\n");
}

void init_array(array_elem_pair_t *a, int size) {
	for (auto i = 0; i < size; i++) {
		// [-100..100]
		a[i].elem = rand() % 2001 - 1000;
		a[i].i = i;
	}
}

int main(int argc, char **argv) {

	MPI_Init(&argc, &argv);

	srand(time(0));

	int global_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);

	int global_size;
	MPI_Comm_size(MPI_COMM_WORLD, &global_size);

	if (global_size != 4) {
		if (global_rank == 0) {
			printf("Not enough processors! Need exactly 4\n");
		}

		MPI_Finalize();
		return 1;
	}

	array_elem_pair_t local_min_elem_pair;
	array_elem_pair_t *array;
	array_elem_pair_t *buf = new array_elem_pair_t[ARRAY_SIZE/global_size];

	if (global_rank == GENERAL_PROCESS) {
		// init array on master
		array = new array_elem_pair_t[ARRAY_SIZE];
		init_array(array, ARRAY_SIZE);
		print_array(array, ARRAY_SIZE);
	}
	MPI_Scatter(array, ARRAY_SIZE/global_size, MPI_2INT, buf, ARRAY_SIZE/global_size, MPI_2INT, 0, MPI_COMM_WORLD);

	local_min_elem_pair = *std::min_element(buf, buf + ARRAY_SIZE/global_size, [] (auto const lhs, auto const rhs) {
		return lhs.elem < rhs.elem;
	});
	printf("Local min element: %d at global rank %d\n", local_min_elem_pair.elem, global_rank);

	array_elem_pair_t min_result;
	MPI_Reduce(&local_min_elem_pair, &min_result, global_size, MPI_2INT, MPI_MINLOC, 0, MPI_COMM_WORLD);

	if (global_rank == GENERAL_PROCESS) {
		printf("Min element: %d at index %d\n", min_result.elem, min_result.i);
		delete[] array;
	}

	delete []buf;
	MPI_Finalize();
	return 0;
}
