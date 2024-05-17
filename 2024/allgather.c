#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

      // inicializaÃ§Ã£o das variÃ¡veis

    MPI_Status status;    
    int n_size, Numprocs, meu_Rank;
    int i, scatter_size;
    int *entrada, *saida;
    char  str[4], filename[50] = "./arquivos/dados";
    FILE *fp;
      // InicializaÃ§Ã£o
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_Rank);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

      // NÃºmero de processos associados Ã  quantidade de arquivos em /arquivos/dados

        if(Numprocs>8)

        {
           printf("\nNumero de processadores deve ser menor que 8");
           MPI_Finalize();
           exit(-1);
        }

        //Leitura dos dados de entrada

        sprintf(str, "%d", meu_Rank);
        strcat(filename, str);
        if ((fp = fopen (filename, "r")) == NULL)
        {
           printf("\nNao pode abrir o arquivo de entrada");
           MPI_Finalize();
           exit(-1);
        }

        fscanf(fp, "%d", &n_size);    

        //aloca memÃ³ria e lÃª os dados dos arquivos de entrada

        entrada = (int *)malloc(n_size*sizeof(int));

        for(i=0; i< n_size; i++)
            fscanf(fp, "%d", &entrada[i]);    

        MPI_Barrier(MPI_COMM_WORLD);

        saida = (int *)malloc(n_size*Numprocs*sizeof(int));

        MPI_Allgather (entrada, n_size, MPI_INT, saida, n_size, MPI_INT, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);

        printf("\nResultado da coleta dos dados do processador %d: %d", meu_Rank, n_size*Numprocs);

        printf("\n-----------------------------------------------\n");

        for(i = 0; i < n_size*Numprocs; ++i)
        {
           if((i%10)==0) printf("\n");
           printf(" %d ", saida[i]);
        }
        
        printf("\n");

        fclose(fp);
        MPI_Finalize();
    }

/* SAIDA

Resultado da coleta dos dados do processador 0: 18
-----------------------------------------------

 21  18  54  24  33  69  7  8  27  43 
 73  25  2  10  3  4  23  14 

Resultado da coleta dos dados do processador 1: 18
-----------------------------------------------

 21  18  54  24  33  69  7  8  27  43 
 73  25  2  10  3  4  23  14 

Resultado da coleta dos dados do processador 2: 18
-----------------------------------------------

 21  18  54  24  33  69  7  8  27  43 
 73  25  2  10  3  4  23  14 

*/