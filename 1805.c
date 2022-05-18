#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv){
    MPI_Init(NULL,NULL);
    int rank, size, token;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank!=0){
        MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("A máquina %d recebeu o token %d da máquina %d\n", rank, token, rank-1);

    }else{
        token = -1;
    }
    MPI_Send(&token, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);
    if(rank==0){
        MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("A máquina %d recebeu o token %d da máquina %d\n", rank, token, size-1);
    }
    MPI_Finalize();
    return 0;
}