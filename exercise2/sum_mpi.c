
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long n = 10000000LL;
    long long chunk = n / size;
    long long start = rank * chunk + 1;
    long long end = (rank == size - 1) ? n : start + chunk - 1;

    long long local_sum = 0;

    double start_time = MPI_Wtime();

    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    long long total_sum = 0;

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG,
               MPI_SUM, 0, MPI_COMM_WORLD);

    double elapsed = MPI_Wtime() - start_time;
    double max_elapsed = 0.0;

    MPI_Reduce(&elapsed, &max_elapsed, 1, MPI_DOUBLE,
               MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Number of processes: %d\n", size);
        printf("Sum: %lld\n", total_sum);
        printf("Execution time: %.6f seconds\n", max_elapsed);
    }

    MPI_Finalize();
    return 0;
}
