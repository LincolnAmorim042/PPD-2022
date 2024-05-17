/*
lamboot -v
mpicc hello.c -o hello
mpirun -np 2 ./hello
lamhalt
*/
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    MPI_Init(&argc , &argv);
    printf("Oi mundo!\n");
    MPI_Finalize();
    return 0;
}