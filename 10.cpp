// lab10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 16
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

int main(int argc, char* argv[])
{
    int numtasks, rank, source, dest, outbuf, i, tag = 1,
        inbuf[4] = { MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL, },
        nbrs[4], dims[2] = { 4,4 },
        periods[2] = { 0,0 }, reorder = 0, coords[2];

    MPI_Request reqs[8];
    MPI_Status stats[8];
    MPI_Comm cartcomm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks == SIZE) {
        MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
        MPI_Comm_rank(cartcomm, &rank);
        MPI_Cart_coords(cartcomm, rank, 2, coords);
        MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
        MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);

        printf("rank= %d coords= %d %d  neighbors(u,d,l,r)= %d %d %d %d\n",
            rank, coords[0], coords[1], nbrs[UP], nbrs[DOWN], nbrs[LEFT],
            nbrs[RIGHT]);

        outbuf = rank;

        for (i = 0; i < 4; i++) {
            dest = nbrs[i];
            source = nbrs[i];
            MPI_Isend(&outbuf, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &reqs[i]);
            MPI_Irecv(&inbuf[i], 1, MPI_INT, source, tag, MPI_COMM_WORLD, &reqs[i + 4]);
        }

        MPI_Waitall(8, reqs, stats);

        printf("rank= %d                  inbuf(u,d,l,r)= %d %d %d %d\n",
            rank, inbuf[UP], inbuf[DOWN], inbuf[LEFT], inbuf[RIGHT]);
    }
    else
        printf("Must specify %d tasks. Terminating.\n", SIZE);

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
