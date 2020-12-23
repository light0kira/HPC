// lab8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int iproc;
    int MyRank, Numprocs, Root = 0;
    int value, sum = 0;
    int	Source, Source_tag;
    int Destination, Destination_tag;
    MPI_Status status;


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

    if (MyRank == Root) {

        for (iproc = 1; iproc < Numprocs; iproc++) {
            Source = iproc;
            Source_tag = 0;

            MPI_Recv(&value, 1, MPI_INT, Source, Source_tag,
                MPI_COMM_WORLD, &status);
            sum = sum + value;
        }
        printf("MyRank = %d, SUM = %d\n", MyRank, sum);
    }
    else {
        Destination = 0;
        Destination_tag = 0;

        MPI_Send(&MyRank, 1, MPI_INT, Destination, Destination_tag,
            MPI_COMM_WORLD);
    }

    MPI_Finalize();

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
