#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector> 


using namespace std;

//------------
// CONSTANTS
//------------

const int N = 10;

// tags
const int DATA = 0;
const int CONTROL = 1;

// control codes
const int END = 0;
const int CONTINUE = 1;
const int EXIST = 2;
const int NOTEXIST = 3;


//------------
// UTILS
//------------

inline static void log(const char* msg, int procId) {
    printf("\nProc %d: %s\n", procId, msg);
}

inline static void initFirstRandArray(int* arr, int n, int N, int min, int max, int solt) {
    int delta = max - min;
    srand((unsigned)time(0) + solt);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % delta + min;
    }     
    for (int i = n; i < N; i++) {
        arr[i] = 0;
    }
}

inline static void initFirstArrayBy(int* arr, int n, int N, int val) {
    for (int i = 0; i < n; i++) {
        arr[i] = val;
    }    
    for (int i = n; i < N; i++) {
        arr[i] = 0;
    }
}

inline static void showArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

inline static void showVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

inline static void showInt(int x) {
    printf("%d\n", x);
}

inline static void showLine() {
    printf("\n");
}

int calcL1Norm(int* arr, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += abs(arr[i]);
    }
    return result;
}


//------------
// MAIN
//------------

int main(int argc, char** argv) {

    int procId;
    int procsNum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procId);
    MPI_Comm_size(MPI_COMM_WORLD, &procsNum);

    int elemsPerProc = N / procsNum + 1;
    int extaN = elemsPerProc * procsNum;
    
    int* arr = new int[extaN];
    int* chunk = new int [elemsPerProc];

    int chunkResult;
    int result;


    // init array 
    if (procId == 0) {
        log("Init array", procId);
        initFirstRandArray(arr, N, extaN, -10, 11, 1);
        showArray(arr, N);
    }


    // send array to all procs
    MPI_Scatter(
        arr, elemsPerProc, MPI_INT,
        chunk, elemsPerProc, MPI_INT, 
        0, MPI_COMM_WORLD);

    // calc chunk results
    chunkResult = calcL1Norm(chunk, elemsPerProc);
    log("Get l1 norm of chunk", procId);
    showArray(chunk, elemsPerProc);
    showInt(chunkResult);


    // sum of chunk results
    MPI_Reduce(&chunkResult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    // show result
    if (procId == 0) {
        log("Get l1 norm of array", procId);
        showInt(result);
        showLine();
    }

    delete [] chunk;
    delete [] arr;    

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}
