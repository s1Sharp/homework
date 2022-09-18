#include "mpi.h"
#include <iostream>
#include <limits>
#include <array>
#include "stdlib.h"
#include "math.h"

#include "randvector.h"
#include "enumerate.h"

#define MAS_SIZE 10
#define GENERAL_PROCESS 0
#define SIDE_PROCESS 1
#define SEND_ANY_TAG 0

int main(int argc, char *argv[]){   

	srand(time(0));

    int ProcNum;
    int ProcRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == GENERAL_PROCESS)
    {
        std::array<int, MAS_SIZE> a;
	    rand_vec(a.data(), MAS_SIZE);
        MPI_Send((void *)a.data(), (int)a.size(), MPI_INT, SIDE_PROCESS, SEND_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD);
    }

    //print result
    if (ProcRank == SIDE_PROCESS) {
        MPI_Status status;
        std::array<int, MAS_SIZE> a;

        MPI_Recv((void *)a.data(), (int)a.size(), MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD, &status);

        for (auto&& [idx, elem]: enumerate(a)) {
            printf("Elem %u\t : idx %lu\t from %u process, %s\n", elem, idx, status.MPI_SOURCE, status.MPI_ERROR ? "no error":"error");
        }
    }

    MPI_Finalize();
}
