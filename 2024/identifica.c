/*
lamboot -v
mpicc identifica.c -o identifica
mpirun -np 5 ./identifica
lamhalt
*/
#include <stdio.h>
#include <mpi.h>

int size, rank;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    MPI_Comm_size( MPI_COMM_WORLD, &size);
    printf("Processo %d de %d\n", rank, size);
    MPI_Finalize();
    return 0;
}