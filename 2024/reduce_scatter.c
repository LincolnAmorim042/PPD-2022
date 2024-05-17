#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int envia_buffer[size];
    int recebe_buffer;
    int recvcounts[size];

    for (int i = 0; i < size; i++)
        envia_buffer[i] = 1 + rank + size*i;

    printf("Proc %d enviando valores: ", rank);
    for (int i = 0; i < size; i++) 
        printf("%d ", envia_buffer[i]);
    printf("\n");

    for (int i = 0; i < size; i++)
        recvcounts[i] = 1;

    MPI_Reduce_scatter(envia_buffer, &recebe_buffer, recvcounts, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

    printf("Maior valor no Proc %d: %d\n", rank, recebe_buffer);

    MPI_Finalize();

    return 0;
}

/* SAIDA

mpirun -np 2 ./reduce_scatter
Proc 0 enviando valores: 1 3 
Proc 1 enviando valores: 2 4 
Maior valor no Proc 1: 4
Maior valor no Proc 0: 2

OBS.: como sÃ£o 2 processadores, 
o rank 0 cria o valor envia_rank[0]=1+0+2*0 = 1
o rank 0 cria o valor envia_rank[1]=1+0+2*1 = 3

o rank 1 cria o valor envia_rank[0]=1+1+2*0 = 2
o rank 1 cria o valor envia_rank[1]=1+1+2*1 = 4

a funÃ§Ã£o reduce_scatter distribui os valores entre os processos, isto Ã©, fica com um e manda o outro para outro processador.

o processador 0 fica com os valores 1 e 2 e seleciona o maior, no caso 2
o processador 1 fica com os valores 3 e 4 e seleciona o maior, no caso 4

*/