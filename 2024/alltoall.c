#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int num_nos,meu_id,mpi_err;
void init_it(int  *argc, char ***argv);
void seed_random(int  id);
void random_number(float *z);
void init_it(int  *argc, char ***argv) {
	mpi_err = MPI_Init(argc,argv);
    mpi_err = MPI_Comm_size( MPI_COMM_WORLD, &num_nos );
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &meu_id);
}
int main(int argc,char *argv[]){
	int *contador_emissor, *contador_receptor;
	int i;
	float z;

	init_it(&argc,&argv);
	contador_emissor = (int*)malloc(sizeof(int)*num_nos);
	contador_receptor = (int*)malloc(sizeof(int)*num_nos);
//Gera randomicamente uma semente com valor diferente para cada cada processador
	seed_random(meu_id);
//encontra o dado para enviar
	for(i=0;i<num_nos;i++){
		random_number(&z);
		contador_emissor[i] = (int)(10.0*z)+1;
	}
	printf("meu_id = %d contador_emissor = ",meu_id);
	for(i=0;i<num_nos;i++)
		printf("%d ",contador_emissor[i]);
	printf("\n");
//  envia o dado
	mpi_err = MPI_Alltoall(	contador_emissor,1,MPI_INT,
						    contador_receptor,1,MPI_INT,
	                 	    MPI_COMM_WORLD);
	printf("meu_id = %d contador_receptor = ",meu_id);
	for(i=0;i<num_nos;i++)
		printf("%d ",contador_receptor[i]);
	printf("\n");
    mpi_err = MPI_Finalize();
}
void seed_random(int  id){
	srand((unsigned int)id);
}
void random_number(float *z){
	int i;
	i=rand();
	*z=(float)i/RAND_MAX;
}

/*
Cada processador envia/recebe um nÃºmero randÃ´mico diferente 
para/dÃª outros processadores.  
*/


/* SAIDA


meu_id = 1 contador_emissor = 9 4 8 8 
meu_id = 2 contador_emissor = 8 9 1 2 
meu_id = 3 contador_emissor = 6 3 4 5 
meu_id = 0 contador_emissor = 9 4 8 8 
meu_id = 1 contador_receptor = 4 4 9 3 
meu_id = 2 contador_receptor = 8 8 1 4 
meu_id = 0 contador_receptor = 9 9 8 6 
meu_id = 3 contador_receptor = 8 8 2 5 


*/