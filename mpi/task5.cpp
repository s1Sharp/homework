#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector> 
#include "control_codes.h"
#include "vector_util.h"

using namespace std;

//------------
// CONSTANTS
//------------

#define GENERAL_PROCESS 0

const int N = 11;
const int M = 5;

//------------
// MAIN
//------------

int main(int argc, char** argv) {

    //common vars
    int controlCode = CONTINUE;
    int diagonalElement;
    int ProcRank;
    int ProcNum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    // PROCCESS 0
    if (ProcRank == GENERAL_PROCESS) {

        int minRand = 0;
        int maxRand = 100;
        int** matrix = allocateMatrix2d(N, M);
        vector<int> result;

        // init
        ProcessLog("Init matrix", ProcRank);
        initRandMatrix(matrix, minRand, maxRand, N, M);
        showMatrix(matrix, N, M);

        // main loop
        ProcessLog("Start calculating diagonal", ProcRank);
        for (int i = 0; i < N && controlCode != NOTEXIST; i += ProcNum-1) {

            // sending each proc one row
            for (int id = 1; id < ProcNum; id++) {

                // break if no rows
                int rowI = i + id-1;
                if (rowI >= N) {
                    break;
                }

                // send control code to continue
                MPI_Send(&control_codes_data[CONTINUE], 1, MPI_INT, id, CONTROL, MPI_COMM_WORLD);

                // send row & index of row 
                MPI_Send(matrix[rowI], M, MPI_INT, id, DATA, MPI_COMM_WORLD);
                MPI_Send(&rowI, 1, MPI_INT, id, DATA, MPI_COMM_WORLD);
            }

            // receiving results of all proc
            for (int id = 1; id < ProcNum; id++) {

                // break if no procs
                int rowI = i + id-1;
                if (rowI >= N) {
                    break;
                }

                // break if diagonal end
                MPI_Recv(&controlCode, 1, MPI_INT, id, CONTROL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (controlCode == NOTEXIST) {
                    break;
                }

                // recv deagonal item
                MPI_Recv(&diagonalElement, 1, MPI_INT, id, DATA, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                result.push_back(diagonalElement);
            }
        };
        ProcessLog("Finish calculating diagonal", ProcRank);

        // send control code to end
        for (int id = 1; id < ProcNum; id++) {
            MPI_Send(&control_codes_data[END], 1, MPI_INT, id, CONTROL, MPI_COMM_WORLD);
        };

        showVector(result);
    }

    // PROCCESS 1..N
    else {

        int procControlCode;
        int row[M];
        int rowI;

        while (true) {

            // recv control code
            MPI_Recv(&procControlCode, M, MPI_INT, GENERAL_PROCESS, CONTROL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if (procControlCode == END) {
                break;
            }

            // recv row
            MPI_Recv(row, M, MPI_INT, GENERAL_PROCESS, DATA, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // recv index of row
            MPI_Recv(&rowI, 1, MPI_INT, GENERAL_PROCESS, DATA, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            ProcessLog("Get row", ProcRank);
            showArray(row, M);

            // if diagonal item exists
            if (rowI < M) {
                diagonalElement = row[rowI];
                MPI_Send(&control_codes_data[EXIST], 1, MPI_INT, GENERAL_PROCESS, CONTROL, MPI_COMM_WORLD);
                MPI_Send(&diagonalElement, 1, MPI_INT, GENERAL_PROCESS, DATA, MPI_COMM_WORLD);

                ProcessLog("Send diagonal item to general", ProcRank);
                printf("%d\n", diagonalElement);
            }
            else {
                ProcessLog("No diagonal item", ProcRank);
                MPI_Send(&control_codes_data[NOTEXIST], 1, MPI_INT, GENERAL_PROCESS, CONTROL, MPI_COMM_WORLD);
            }
        };

    }

    return MPI_Finalize();
}
