//este programa imprime na tela hello world
//lamboot -v
//mpicc hello.c -o hello
//mpirun -np 5 ./hello

#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    printf("sexo!\n");
    MPI_Finalize();

    return 0;
}