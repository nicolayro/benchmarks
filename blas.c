#include <cblas.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define ALPHA 1.0
#define BETA  0.0

#define GIGA 1.0e-9

#define WALLTIME(t) ((double)(t).tv_sec + 1e-6 * (double)(t).tv_usec)

typedef int64_t int_t;

int_t N; // Size of square matrix
double *A, *B, *C; // Matrices

void usage()
{
    printf("Usage: ./blas <N>\n");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Missing argument\n");
        usage();
        exit(EXIT_FAILURE);
    }

    N = strtol(argv[1], NULL, 10);

    if (!N) {
        fprintf(stderr, "ERROR: Unable to parse argument N.\n");
        printf("Usage: ./blas <N>\n");
        exit(EXIT_FAILURE);
    }

    A = malloc(N * N * sizeof(double));
    B = malloc(N * N * sizeof(double));
    C = malloc(N * N * sizeof(double));

    if (!A || !B || !C) {
        fprintf(stderr, "ERROR: Not enough memory...\n");
        exit(EXIT_FAILURE);
    }

    for (int_t i = 0; i < N*N; i++) {
        A[i] = i%3-1;
        B[i] = i%3-1;
        C[i] = i%3-1;
    }

    double gflop = (2 * N * N * N - N * N) * GIGA;
    printf("N=%lld\n", N);
    printf("Gflop=%lf\n", gflop);

    struct timeval start, end;
    double elapsed;
    double gflop_tot = 0;
    for (int_t i = 0; i < 100; i++) {
        gettimeofday(&start, NULL);

        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans,
                N, N, N, 
                ALPHA, A, N, B, N,
                BETA, C, N);

        gettimeofday(&end, NULL);

        elapsed = WALLTIME(end) - WALLTIME(start);
        printf("%lf Gflop/s\n", gflop/elapsed);

        gflop_tot += gflop/elapsed;
    }

    printf("Avg Gflop/s: %lf\n", gflop_tot/100);

    return 0;
}
