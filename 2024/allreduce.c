// Este programa calcula o desvio padrÃ£o de um vetor de elementos em 
// paralelo usando MPI_AllReduce.
// compilar com: mpicc allreduce2.c -o allreduce2 -lm (por conta da funÃ§Ã£o sqrt)
//rodar com: mpirun -np 4 ./allreduce2 5(nÃºmero de elementos por processador)
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <assert.h>
#include <time.h>
// Cria um vetor de nÃºmeros randÃ´micos. Cada nÃºmero possui valor entre 0 e 1
float *create_rand_nums(int num_elements) {
  float *rand_nums = (float *)malloc(sizeof(float) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = (rand() / (float)RAND_MAX);
  }
  return rand_nums;
}
int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usar: avg num_elements_por_proc\n");
    exit(1);
  }
  int num_elements_per_proc = atoi(argv[1]);
  int rank, size, i;
  float *rand_nums = NULL;
  float soma_global, global_sq_diff, media, desvio_padrao, soma_local = 0;
    MPI_Init(NULL, NULL); 
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // Cria um vetor de elementos randÃ´micos em todos os processadores
  srand(time(NULL)*rank); // Semente para o gerador de nÃºmeros aleatÃ³rios. 
  //Essa semente Ã© Ãºnica em cada processador  
  rand_nums = create_rand_nums(num_elements_per_proc);
  // Soma os nÃºmeros localmente
  for (i = 0; i < num_elements_per_proc; i++) {
    soma_local += rand_nums[i];
  }
  // Reduz todas as somas locais em uma soma global com o ojbetivo de calcular a mÃ©dia
    MPI_Allreduce(&soma_local, &soma_global, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
    media = soma_global / (num_elements_per_proc * size);
  // Calcula a soma local da diferenÃ§a dos quadrados da mÃ©dia
  float local_sq_diff = 0;
  for (i = 0; i < num_elements_per_proc; i++) {
    local_sq_diff += (rand_nums[i] - media) * (rand_nums[i] - media);
  }
  // Reduz a soma glogal da diferenÃ§a dos quadrados para o processador raiz  e imprime
 //  a resposta. O desvio padrÃ£o Ã© a raiz quadrada da mÃ©dia da diferenÃ§a dos quadrados
  if (rank == 0) {
    desvio_padrao = sqrt(global_sq_diff / (num_elements_per_proc * size));
    printf("media = %f e Desvio Padrao = %f\n", media, desvio_padrao);
  }
  // liberando memÃ³ria
  free(rand_nums);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}


/* SAIDA

mpirun -np 14 ./allreduce2 50
media = 0.503880 e Desvio Padrao = 0.281610

*/