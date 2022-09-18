#include "mpi.h"
#include <iostream>
#include <limits>
#include <array>
#include <memory>
#include <vector>
#include <utility>
#include "stdlib.h"
#include "math.h"

#include "randvector.h"
#include "enumerate.h"
#include "massivops.h"

#define MAS_SIZE 120
#define GENERAL_PROCESS 0
#define SIDE_PROCESS 1
#define SEND_ANY_TAG 0

#define X_ARRAY (0)
#define Y_ARRAY (1)

#define USE_SUM // USE_MULT

int main(int argc, char *argv[]){

    srand(time(0));
    int ProcNum;
    int ProcRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcNum < 2) {
        printf("Not enough processes! Need more than 1");
        MPI_Abort(MPI_COMM_WORLD, MPI_ERR_TOPOLOGY);
        return 1;
    }

    if (ProcRank == GENERAL_PROCESS)
    {
        std::array<int, MAS_SIZE> x;
        std::array<int, MAS_SIZE> y;
        std::array<int, MAS_SIZE> z;
        rand_vec(x.data(), MAS_SIZE);
        rand_vec(y.data(), MAS_SIZE);

        std::vector<std::pair<int, int>> partitionVector(ProcNum - 1, std::make_pair(0, 0));

        for (auto&& [idx, elem]: enumerate(partitionVector)) {
            int partition = (int) round((double) MAS_SIZE / (ProcNum - 1));
            // exclude main process
            int locIdx = idx;
            locIdx++;
            if (MAS_SIZE % ProcNum != 0 &&
                locIdx == ProcNum - 1) {
                partition = MAS_SIZE - (ProcNum - 1) * partition;
            }
            elem.first = locIdx;
            elem.second = partition;
        }

        for (auto&& [idx, elem]: enumerate(partitionVector)) {
            const int offset = idx * elem.second;
            const int procSendTo = elem.first;
            const int dataSize = elem.second;

            MPI_Send((void *)(y.data() + offset), dataSize, MPI_INT, (int)procSendTo, X_ARRAY, (MPI_Comm)MPI_COMM_WORLD);
            MPI_Send((void *)(x.data() + offset), dataSize, MPI_INT, (int)procSendTo, Y_ARRAY, (MPI_Comm)MPI_COMM_WORLD);
        }

        auto requests = std::make_unique<MPI_Request []>(ProcNum - 1);
        for (auto&& [idx, elem]: enumerate(partitionVector)) {
            const int offset = idx * elem.second;
            const int procRecvFrom = elem.first;
            const int dataSize = elem.second;
            MPI_Irecv((void *)(z.data() + offset), dataSize, MPI_INT, (int)procRecvFrom, MPI_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD, &requests[idx]);
        }
        for (size_t i = 0; i < ProcNum - 1; i++) {
            MPI_Status status;
            MPI_Wait(&requests[i], &status);
        }
        for (size_t i = 0; i < z.size(); i++) {
            printf("z[%u]=%u : x[%u]=%u : y[%u]=%u\n", i, z[i], i, x[i], i, y[i]);
        }
    }

    if (ProcRank != GENERAL_PROCESS) {
        MPI_Status status;
        int count;

        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);

        auto buffx = std::make_unique<int []>(count);
        auto buffy = std::make_unique<int []>(count);

        MPI_Recv((void *)buffx.get(), (int)count, MPI_INT, status.MPI_SOURCE, X_ARRAY, (MPI_Comm)MPI_COMM_WORLD, &status);
        MPI_Recv((void *)buffy.get(), (int)count, MPI_INT, status.MPI_SOURCE, Y_ARRAY, (MPI_Comm)MPI_COMM_WORLD, &status);

#ifdef USE_SUM
        sum_mass(buffx.get(), buffy.get(), (int)count);
#elif USE_MULT
        multiply_mass(buffx.get(), buffy.get(), (int)count);
#endif
        MPI_Send((void *)buffx.get(), count, MPI_INT, (int)GENERAL_PROCESS, SEND_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
