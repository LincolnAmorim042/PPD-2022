//imprime a frase com a id e o total de processos envolvidos na exe
//lamboot -v
//mpicc hello.c -o hello
//mpirun -np 5 ./hello

#include <stdio.h>
#include <mpi.h>

int rank, size;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("processador %d de %d processadores\n", rank, size);
    MPI_Finalize();
}