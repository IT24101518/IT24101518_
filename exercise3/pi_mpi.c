
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long total_points = 10000000LL;
    long long local_inside = 0;
    long long total_inside = 0;

    unsigned int seed =
        (unsigned int)time(NULL) ^ (unsigned int)(rank + 1) * 1234567U;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    for (long long i = rank; i < total_points; i += size) {
        double x = (double)rand_r(&seed) / ((double)RAND_MAX + 1.0);
        double y = (double)rand_r(&seed) / ((double)RAND_MAX + 1.0);

        if (x * x + y * y <= 1.0) {
            local_inside++;
        }
    }

    MPI_Reduce(&local_inside, &total_inside, 1,
               MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double local_time = MPI_Wtime() - start_time;
    double elapsed_time = 0.0;

    MPI_Reduce(&local_time, &elapsed_time, 1,
               MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = 4.0 * (double)total_inside / total_points;

        printf("Number of processes: %d\n", size);
        printf("Total points: %lld\n", total_points);
        printf("Points inside circle: %lld\n", total_inside);
        printf("Estimated Pi: %.10f\n", pi);
        printf("Execution time: %.6f seconds\n", elapsed_time);
    }

    MPI_Finalize();
    return 0;
}
