#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int x, val, rank, size, origem, tag=10;
    MPI_Status status;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size!=2){
        fprintf(stderr,"Este programa deve ser executado com apenas duas máquinas %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    x=99999;
    if(rank==0){
        printf("Máquina %d enviando %d para máquina 1\n", rank, x);
        MPI_Ssend(&x, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        printf("Máquina %d recebendo da máquina 1\n", rank);
        MPI_Recv(&val, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
        printf("Máquina %d recebeu %d\n", rank, val);
    }else{
        MPI_Recv(&val, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        val+=1;
        MPI_Ssend(&val, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}