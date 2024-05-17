#include <mpi.h>
#include <stdio.h>

#define RAIZ 0

int main (int argc, char** argv){
    int rank, val, reduced = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    val = rank+1;

    MPI_Reduce((void *)&val, (void *)&reduced, 1, MPI_INT, MPI_SUM, RAIZ, MPI_COMM_WORLD);

    printf("[%d] op reduce = %d\n", rank, reduced);
    MPI_Finalize();
    return 0;
}