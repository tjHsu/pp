#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define TAG_Bcast_simple 1
#define TAG_Bcast_tree 2
#define TAG_Bcast_type 3
#define typeof __typeof__

//simple broadcast function
void Bcast_simple(void* buffer,int count, MPI_Datatype datatype,MPI_Comm comm){
    int i, NoP_comm, myID;
    MPI_Status status;

    MPI_Comm_size(comm,&NoP_comm);  //get comm size
    MPI_Comm_rank(comm,&myID);      //get own ID in comm

    if (myID==0){                   //only process zero is sender (i.e. 0 broadcasts)
        for (i=1;i<NoP_comm;i++){   //exclude 0 as it is the source
            //send to ith process
            MPI_Send(buffer,count,datatype,i,TAG_Bcast_simple,comm);
            printf("\nI am process %i and I sent to %i\n",myID,i);
        }
    }
    else{
        //reveivcer need to receive size first
        MPI_Probe(0,TAG_Bcast_simple,comm,&status);
        MPI_Get_count(&status,datatype,&count);
        MPI_Recv(buffer,count,datatype,0,TAG_Bcast_simple,comm,&status);
        }
}

int get_parent(int child, int num_nodes){
//compute parent node using the formula as shoow in the solution document
    if (child!=0){ //only rank zero node doesn't have a parent
        return (child-floor(child/((double) 2))-1);}
    else{
        return -1;}
}

int get_left_child(int parent,int num_nodes){
//compute left child node using the formula as shoow in the solution document
    int child_left;
    child_left=2*(parent+1)-1;

    if (child_left>num_nodes-1){ //return -1 if left child is greater than NoP
        return -1;}
    else {
        return child_left;}
}

int get_right_child(int parent,int num_nodes){
//compute right child node using the formula as shoow in the solution document
    int child_right;
    child_right=2*(parent+1);

    if (child_right>num_nodes-1){//return -1 if right child is greater than NoP
        return -1;}
    else {
        return child_right;}
}

void Bcast_tree(void* buffer,int count, MPI_Datatype datatype,MPI_Comm comm){
//function to broadcast a message using a tree structure for message propagation
    int myID,NoP, parent,child_left,child_right;
    MPI_Status status;

    MPI_Comm_rank(comm,&myID);          //get comm size
    MPI_Comm_size(MPI_COMM_WORLD, &NoP);//get own ID in comm

    parent=get_parent(myID,NoP);            //get corresponding parent element
    child_left=get_left_child(myID,NoP);    //get left child
    child_right=get_right_child(myID,NoP);  //get right child

    /*//just for checking purposes
    printf("\nparent of %d is %d",myID,parent);
    printf("\nleft child of %d is %d",myID,child_left);
    printf("\nright child of %d is %d",myID,child_right);*/

    if (parent!=-1){ //if parent is not -1, i.e. if myID!=0
        //probe first to get value
        MPI_Probe(parent,TAG_Bcast_tree,comm,&status);
        MPI_Get_count(&status,datatype,&count);
        MPI_Recv(buffer,count,datatype,parent,TAG_Bcast_tree,comm, &status);
        //printf("\n%d:recv from parent: %d\n",myID,parent);
    }

    if (child_left!=-1){

        MPI_Send(buffer,count,datatype,child_left,TAG_Bcast_tree,comm);
        //printf("\n%d:send to left child: %d\n",myID,child_left);
    }
    if (child_right!=-1){

        MPI_Send(buffer,count,datatype,child_right,TAG_Bcast_tree,comm);
        //printf("\n%d:send to right child: %d\n",myID,child_right);
    }

}

int main(int args, char *argv[])
{
    int myRank, NoP;
    MPI_Init(&args, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
    MPI_Comm_size(MPI_COMM_WORLD,&NoP);

    /*test value*/
    int N;
    N=3;
    int *sd;
    sd=malloc(N*sizeof(int));
    if (myRank==0){

        sd[0]=1;
        sd[1]=2;
        sd[2]=3;
        Bcast_tree(sd,N,MPI_INT,MPI_COMM_WORLD);
        //Bcast_simple(sd,N,MPI_INT,MPI_COMM_WORLD);
    }
    else{
        Bcast_tree(sd,N,MPI_INT,MPI_COMM_WORLD);
        //Bcast_simple(sd,N,MPI_INT,MPI_COMM_WORLD);
        printf("\nProcess %d: %d %d %d\n",myRank, sd[0], sd[1],sd[2]);
    }

    free(sd); //free test array

    MPI_Finalize();
    return 0;
}
