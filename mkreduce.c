#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv){
    MPI_Init(NULL,NULL);
    int origem,rank, size, val, i, *sum;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    origem = 0;
    val = rank+1;
    i=0;
    
    if(rank==origem){
        for(i=0; i<size;i++){
            MPI_Recv(&sum[i], 1, MPI_INT, origem, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            val+=sum[i];
        }
    }else{
        MPI_Send(&val, 1, MPI_INT, origem, 0, MPI_COMM_WORLD);
        val=0;
    }
    printf("[%d] op reduce = %d\n", rank, val);
    MPI_Finalize();
    return 0;
}
