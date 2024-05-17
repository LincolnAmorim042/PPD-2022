/*
lamboot -v
mpicc somavet.c -o somavet
mpirun -np 2 ./somavet
lamhalt
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define tam 10
int vet[] = {1,2,3,4,5,6,7,8,9,10};
int vetaux[1000];

int main(int argc, char** argv){
    int size, rank, elemp, ind, i, esq, soma, temp, elemr, somap, origem;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    MPI_Comm_size( MPI_COMM_WORLD, &size);
    
    if(rank == 0){
        elemp = tam / size;
        if(size > 1){
            for(i=0; i<size-1; i++){
                ind = i*elemp;
                MPI_Send(&elemp, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&vet[ind], elemp, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            ind = i*elemp;
            esq = tam - ind;
            MPI_Send(&esq, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&vet[ind], esq, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        soma = 0;
        for(i=0; i<elemp; i++){
            soma += vet[i];
        }
        temp = 0;
        for(i=1; i<elemp; i++){
            MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            origem = status.MPI_SOURCE;
            soma += temp;
        }
        printf("Soma = %d\n", soma);
    }else{
        MPI_Recv(&elemr, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&vetaux, elemr, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        somap = 0;
        for(i=0; i<elemr; i++){
            somap += vetaux[i];
        }
        MPI_Send(&somap, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}