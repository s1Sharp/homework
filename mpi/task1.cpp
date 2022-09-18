#include "mpi.h"
#include <iostream>
#include "stdlib.h"
#include "math.h"


int main(int argc, char *argv[]){
    int ProcNum;
    int ProcRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    printf("Count of all processors: %u, Hello, World! from process %u:\n", ProcNum, ProcRank);

    MPI_Finalize();
}