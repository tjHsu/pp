#include <stdio.h>
#include <stdlib.h>
#include <mpi/mpi.h>
#include <string.h>

#define TAG_SIZE 1  //tag for sending/receiving size of the string
#define TAG_STR 2   //tag for sending/receiving the string

/*function to send string using MPI
input: drank: rank of destination
       str: string to be send*/
void send_string(int drank, char *str){
    //get the string length, +1 to condisder null terminator
    int N=strlen(str)+1;
    //send size of string
    MPI_Send(&N, 1,MPI_INT,drank,TAG_SIZE,MPI_COMM_WORLD);
    //send string
    MPI_Send(str,N,MPI_CHAR,drank,TAG_STR,MPI_COMM_WORLD);
}

/*function to receive string, input: source from data are to be received*/
char* recv_string(int source){
    int N;              //string size
    char* str;          //string to be received
    MPI_Status status_size,status_str; //stati for receiption

    //receive size of string
    MPI_Recv(&N,1,MPI_INT,source,TAG_SIZE,MPI_COMM_WORLD,&status_size);
    //allocate memory according to exepected string size
    str=malloc(N*sizeof(char));
    //receive string
    MPI_Recv(str,N,MPI_CHAR,source,TAG_STR,MPI_COMM_WORLD,&status_str);

    return str;
}

int main(int args,char *argv[])
{
    int me,np;  //process id, number of processes
    MPI_Init(&args,&argv);              //init MPI session
    MPI_Comm_rank(MPI_COMM_WORLD,&me);  //get own id
    MPI_Comm_size(MPI_COMM_WORLD,&np);  // get np

    if (me!=0){ //if own id is not of rank 0
        char str[MPI_MAX_PROCESSOR_NAME]; //string to be send
        int len;                          //string length
        //get processor name (includes null terminator, length
        //of returned value doesn't account for it
        MPI_Get_processor_name(str,&len);
        //send string to process 0
        send_string(0,str);
    }
    else{
        int k=0, len; //k: counter of processes, len: length of processor name
        char str[MPI_MAX_PROCESSOR_NAME]; //processor name
        //get null terminated processor name
        MPI_Get_processor_name(str,&len);
        //print result for process zero
        printf("Process %i of %i is running on %s\n",k,np,str);
        for (k=1;k<np;k++){
            //receive processor name from every process
            char *str=recv_string(k);
            printf("Process %i of %i is running on %s\n",k,np,str);
            free(str); //free alloocated memory
        }
    }

    MPI_Finalize(); //terminate MPI session
    return 0;
}
