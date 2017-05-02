#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>


int main(int argc, char *argv[]){
   int ntasks, taskid, number;
   MPI_Status stat;
 
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&ntasks);
   MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
   if (taskid != 0) {
   		MPI_Recv(&number, 1, MPI_INT, taskid - 1, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(taskid == ntasks-1){
			printf("Process %d received %d from process %d\n", taskid, number, taskid - 1);
		}
   } else {
    //Processo que inicia, poe 0 no numero
    number = atoi(argv[1]);
   }

   number += 1;
   MPI_Send(&number, 1, MPI_INT, (taskid + 1) % ntasks, 0, MPI_COMM_WORLD);

   // Libera o processo 0 que estava esperando
   if (taskid == 0) {
   		MPI_Recv(&number, 1, MPI_INT, ntasks - 1, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   }

   
   MPI_Finalize();
  
}
