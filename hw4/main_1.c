#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>

int main(int argc,char *argv[]){

int me,nop;                        //me: process id
                                   // nop: number of processes
MPI_Init(&argc,&argv);             //Init MPI session
MPI_Comm_size(MPI_COMM_WORLD,&nop);//get number processes
MPI_Comm_rank(MPI_COMM_WORLD,&me); //get process ID

//print result
printf("Hello World, I am process %i of %i\n",me,nop);

MPI_Finalize();                   //terminate MPI session

return 0;
}
