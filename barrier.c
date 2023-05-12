#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv){
    int rank=0, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0){
        printf("\nRank 0 antes do Barrier\n");
        fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    for(int i = 1;  i<size; i++){
        if(rank==i){
            printf("\nRank %d depois do Barrier\n", rank);
            fflush(stdout);
        }
    }
    MPI_Finalize();
    return 0;
}