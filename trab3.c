#include <stdio.h>
#include <mpi.h>
#include "unistd.h"
#include <stdlib.h>

    
main(int argc, char*argv[]){

	int nProc, id, i, j, qtdProc;  
    int total = 0;
    int pares = 0;
    int parcial = 0;

    int tvetor = atoi(argv [1]);	
    int vet[tvetor];

    for(i=0;i<tvetor;i++){//for para preencher vetor
		vet[i]=i;
	}

 	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	// printf("Id = %d\n" ,id);

   if(id == 0){
		int parcial2 = 0;
		int total = 0;
		int y;
		MPI_Status st;        
		for(y = 1; y < nProc; y++){
			MPI_Recv(&parcial2, sizeof(int), MPI_INT, y, 0, MPI_COMM_WORLD, &st);
			total += parcial2;       
		}

		for(j = 0; j < tvetor/(nProc-1); j++){
            if(vet[j]%2==0){
				total ++; 
			}
		}

		printf("soma total de pares:%d\n", total);
	} else{
     	qtdProc = tvetor/(nProc-1);

		for(j = id*qtdProc; j < ((id != (nProc-1)) ? ((id + 1) * qtdProc) : tvetor); j++){
            if(vet[j]%2==0){
				parcial = parcial +1; 
			}
			// printf("parcial:%d\n processo:%d\n", parcial, id);  
		}

       MPI_Send(&parcial, sizeof(int), MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
