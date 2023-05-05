#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define tamanho 10 

int vet[] = {1,2,3,4,5,6,7,8,9,10};
int vetaux[1000];

int main(int argc, char** argv){
    int rank, size, elempp, elemrec, ind, i, elemesq, soma, temp, origem, somap;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        elempp = tamanho/size;
        if(size>1){
            for(i=1;i<size;i++){
                ind = i*elempp;
                MPI_Send(&elempp, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&vet[ind], elempp, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            ind = i*elempp;
            elemesq = tamanho - ind;
            MPI_Send(&elemesq, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&vet[ind], elemesq, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        soma=0;
        for(i=0;i<elempp;i++){
            soma+=vet[i];
        }
        for(i=0;i<elempp;i++){
            MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            origem=status.MPI_SOURCE;
            soma+=temp;
        }
        printf("A soma do vetor eh: %d\n", soma);
    }else{
        MPI_Recv(&elemrec, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&vetaux, elemrec, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        somap=0;
        for(i=0;i<elemrec;i++){
            somap+=vetaux[i];
        }
        MPI_Send(&somap,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}