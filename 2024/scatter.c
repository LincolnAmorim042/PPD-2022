#include <mpi.h>
#include <stdio.h>

int main (int argc, char** argv){
    int rank, size, scat;
    int a[4] = {39, 72, 129, 42};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(&a, 1, MPI_INT, &scat, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("ID %d recebeu: %d \n", rank, scat);

    MPI_Finalize();
    return 0;
}