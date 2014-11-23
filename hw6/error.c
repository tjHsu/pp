#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
   double data, res;
   int i, num_procs, my_rank, root=0, tag=3;
   //add MPI_Init(&argc, &argv)
   MPI_Init(&argc, &argv);
   MPI_Status status;
   //add MPI_Comm_size
   //change communicator from MPI_COMM_SELF into MPI_COMM_WORLD
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   if (my_rank == root) {
      data = 1.73205;
      MPI_Bcast(&data, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);
   }

   res = data * (double)my_rank;
   if (my_rank == root) {
      for (i = 1; i < num_procs; i++) {
         MPI_Recv(&data, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status);
         res += data;
      }
      printf("result is %.2f\n", res);
   }
   else {
      MPI_Send(&res, 1, MPI_INT, root, tag, MPI_COMM_WORLD);
   }

   MPI_Finalize();
   return 0;
}
