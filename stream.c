#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

typedef int64_t int_t;

double now();
void copy();
void scale();
void add();
void triad();

#define GIGA 1e-9

int_t N;
double *a, *b, *c;
int scalar;

int main()
{
    N = 1e+6;
    scalar = 2;

    a = malloc(N * sizeof(double));
    b = malloc(N * sizeof(double));
    c = malloc(N * sizeof(double));

    #pragma omp parallel for
    for (int_t i = 0; i < N; i++) {
        a[i] = 1.0;
        b[i] = -1.0;
        c[i] = 0.0;
    }

    double mem_op_bytes;
    double start, end;
    double copy_time, scale_time, add_time, triad_time;

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

    mem_op_bytes = GIGA * N * sizeof(double);

    printf("N=%lld\n", N);
    printf("GB:   %6lf\n", mem_op_bytes);
    printf("Copy    Scale   Add     Triad\n");
    printf("%.2lf   ", mem_op_bytes/copy_time);
    printf("%.2lf   ", 2*mem_op_bytes/scale_time);
    printf("%.2lf   ", 2*mem_op_bytes/add_time);
    printf("%.2lf   ", 3*mem_op_bytes/triad_time);
    printf("\n");

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
        b[i] = a[i];
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

