//send e receive

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
    int rank, size, tag, origem, destino, qtelement;
    char* buffer = "sexo";
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    tag = 10;
    origem = 0;
    destino = 1;
    qtelement = 1;

    if(rank==origem){
        MPI_Send(&buffer, qtelement, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
        printf("A maquina %d enviou o valor %s\n", rank, buffer);
    }
    if(rank==destino){
        MPI_Recv(&buffer, qtelement, MPI_CHAR, origem, tag, MPI_COMM_WORLD, &status);
        printf("A maquina %d recebeu %s\n", rank, buffer);
    }
    MPI_Finalize();
    return 0;
}