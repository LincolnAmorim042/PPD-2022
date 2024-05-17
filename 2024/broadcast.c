#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char** argv){
    int i, myid, nprocs, origem, cont, buff[4];
    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    origem=0;
    cont=4;
    if (myid==origem){
        for(i=0;i<cont;i++){
            buff[i]=i;
        }
    }
    MPI_Bcast(buff, cont, MPI_INT, origem, MPI_COMM_WORLD);
    for(i=0;i<cont;i++){
        printf("Maquina: %d - valor: %d --\n", myid, buff[i]);
    }
    MPI_Finalize();
    return 0;
    
}