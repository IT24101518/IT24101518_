#include <cstdio>
#include <cstdlib>
#include <mpi.h>

int main(void)
{
    int rank;
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char name[MPI_MAX_PROCESSOR_NAME];
    int len;
    MPI_Get_processor_name(name, &len);

    int x[10], y[10];

    if (rank == 1) {
        for (int r = 0; r < 10; r++)
            x[r] = 10 * r;

        printf("Sending message to computer 3 from computer 1\n");

        MPI_Ssend(x, 10, MPI_INT, 3, 0, MPI_COMM_WORLD);
    }
    else if (rank == 3) {
        MPI_Recv(y, 10, MPI_INT, MPI_ANY_SOURCE, 0,
                 MPI_COMM_WORLD, &status);

        printf("Computer 3 received the message from rank %d\n",
               status.MPI_SOURCE);

        printf("The value of y is:\n");

        for (int r = 0; r < 10; r++)
            printf(" %d", y[r]);

        printf("\n");
        fflush(stdout);
    }
    else {
        printf("Just a normal process From rank %d machine %s\n",
               rank, name);
    }

    MPI_Finalize();
    return 0;
}
