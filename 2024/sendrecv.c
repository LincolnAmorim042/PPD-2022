/*
lamboot -v
mpicc sendrecv.c -o sendrecv
mpirun -np 2 ./sendrecv
lamhalt
*/
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
    int size, rank, buffer, tag, origem, destino, nelem;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    MPI_Comm_size( MPI_COMM_WORLD, &size);
    MPI_Status status;

    tag = 10;
    origem = 0;
    destino = 1;
    nelem = 1;

    if(rank == origem){
        buffer = 12;
        MPI_Send( &buffer, nelem, MPI_INT, destino, tag, MPI_COMM_WORLD);
        printf("Maquina %d enviou %d\n", rank, buffer);
        printf("Maquina %d em espera\n", rank);
        MPI_Recv( &buffer, nelem, MPI_INT, destino, tag, MPI_COMM_WORLD , &status);
        printf("Maquina %d recebeu %d\n", rank, buffer);
    }
    if(rank==destino){
        printf("Maquina %d em espera\n", rank);
        MPI_Recv( &buffer, nelem, MPI_INT, origem, tag, MPI_COMM_WORLD , &status);
        printf("Maquina %d recebeu %d\n", rank, buffer);
        buffer = buffer*2;
        MPI_Send( &buffer, nelem, MPI_INT , origem, tag, MPI_COMM_WORLD);
        printf("Maquina %d enviou %d\n", rank, buffer);
    }

    for(int i = 0; i<=10; i++){
        printf("Iteracao %d\n", i);
        if(rank==origem){
            buffer = buffer+2;
            MPI_Send( &buffer, nelem, MPI_INT, destino, tag, MPI_COMM_WORLD);
            printf("Maquina %d enviou %d\n", rank, buffer);
            MPI_Recv( &buffer, nelem, MPI_INT, destino, tag, MPI_COMM_WORLD , &status);
            printf("Maquina %d recebeu %d\n", rank, buffer);
        }
        if(rank==destino){
            MPI_Recv( &buffer, nelem, MPI_INT, origem, tag, MPI_COMM_WORLD , &status);
            printf("Maquina %d recebeu %d\n", rank, buffer);
            buffer = buffer+2;
            MPI_Send( &buffer, nelem, MPI_INT , origem, tag, MPI_COMM_WORLD);
            printf("Maquina %d enviou %d\n", rank, buffer);
        }
    }
    MPI_Finalize();
    return 0;    
}