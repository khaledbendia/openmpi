//hcc pi_par.c -o test -lm
//mpirun -np 2 ./test
#include <stdio.h>
#include <mpi.h>
#include <math.h>

double calcul_pi_part(float a,float b)
{
   double x= 4*atan(a);
   double y= 4*atan(b);
   return (y-x);
}

int main (int argc, char* argv[]) {

int nbProc, myRank;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &nbProc);
MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

float a,b;
a= myRank*(1.0/nbProc);
b= myRank*(1.0/nbProc)+(1.0/nbProc);
double pi_part=calcul_pi_part(a,b);

double pi=pi_part;
if (myRank == 0) {

    double startwtime, endwtime;
    startwtime = MPI_Wtime();
    for(int i=1;i<nbProc;i++)
    {
       MPI_Recv(&pi_part, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
       pi+=pi_part;
    }
    printf("PI = %f\n",pi); 
    endwtime = MPI_Wtime();
    printf ( "Wall clock time = %f \n", endwtime-startwtime );  
} 
else{
    MPI_Send(&pi_part, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); 
}
MPI_Finalize();
}
