/*
criar um arquivo txt
hosts
gravá-lo na pasta com o .exe

com o nome e ip das máquinas

(o primeiro nome é o da máquina principal)
tanto o .exe quanto o hosts devem estar em todas as máquinas

para transferir os arquivos:
scp origem destino

fazer um script bash com esse comando

chamar o arquivo com 
lamboot hosts
ou
mpirun hosts

*/
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char** argv){
    const int limite = 10;
    MPI_Init(NULL,NULL);
    int rank, size, origem, i=0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size!=2){
        fprintf(stderr,"Este programa deve ser executado com apenas duas máquinas %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    origem = (rank+1)%size;
    while (i<limite){
        if(rank==i%size){
            i++;
            MPI_Send(&i, 1, MPI_INT, origem, 0, MPI_COMM_WORLD);
            printf("Máquina %d passou a bola para a máquina %d e incrementou o contador para %d\n", rank, origem, i);
        }else{
            MPI_Recv(&i, 1, MPI_INT, origem, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Máquina %d recebeu a bola da máquina %d com o contador %d\n", rank, origem, i);
        }
    }
    MPI_Finalize();
    return 0;
}