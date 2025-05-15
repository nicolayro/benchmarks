#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

typedef int64_t int_t;
typedef double real_t;

double now();
void copy();
void scale();
void add();
void triad();
#define GIGA 1e-9
#define ITERATIONS 30

int_t N;
real_t *a, *b, *c;
real_t scalar;

void usage()
{
    printf("USAGE: stream <N>\n");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "ERROR: Missing arguments\n");
        usage();
        exit(EXIT_FAILURE);
    }


    N = strtol(argv[1], NULL, 10);
    if (!N) {
        fprintf(stderr, "ERROR: Error while parsing argument '%s'.\n Expected number.\n", argv[1]);
        usage();
        exit(EXIT_FAILURE);
    }

    a = malloc(N * sizeof(double));
    b = malloc(N * sizeof(double));
    c = malloc(N * sizeof(double));

    if (!a || !b || !c) {
        fprintf(stderr, "ERROR: Not enough memory...\n");
        exit(EXIT_FAILURE);
    }

    scalar = 3.0;
    #pragma omp parallel for
    for (int_t i = 0; i < N; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
        c[i] = 3.0;
    }

    double gigabytes;
    double start, end;
    double copy_time, scale_time, add_time, triad_time;

    gigabytes = GIGA * N * sizeof(double);
    printf("N               %lld\n", N);
    printf("GB required     %.2lf\n", 3*gigabytes);
    printf("Threads         %d\n", omp_get_num_procs());
    printf("Copy    Scale   Add     Triad\n");
    for (int i = 0; i < ITERATIONS; i++) {
        start = now();
        copy();
        end = now();
        copy_time = end - start;

        start = now();
        scale();
        end = now();
        scale_time = end - start;

        start = now();
        add();
        end = now();
        add_time = end - start;

        start = now();
        triad();
        end = now();
        triad_time = end - start;

        printf("%.2lf   ", 2*gigabytes/copy_time);
        printf("%.2lf   ", 2*gigabytes/scale_time);
        printf("%.2lf   ", 3*gigabytes/add_time);
        printf("%.2lf   ", 3*gigabytes/triad_time);
        printf("\n");
    }

    free(a);
    free(b);
    free(c);

    return 0;
}

double now()
{
    struct timeval time;
    gettimeofday(&time, NULL);

    return ((double) time.tv_sec + (double) time.tv_usec * 1.e-6);
}

void copy()
{
    #pragma omp parallel for
    for (int_t i = 0; i < N; i++) {
        c[i] = a[i];
    }
}

void scale()
{
    #pragma omp parallel for
    for (int_t i = 0; i < N; i++) {
        c[i] = scalar * a[i];
    }
}

void add()
{
    #pragma omp parallel for
    for (int_t i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
}

void triad()
{
    #pragma omp parallel for
    for (int_t i = 0; i < N; i++) {
        c[i] = scalar * a[i] + b[i];
    }
}
