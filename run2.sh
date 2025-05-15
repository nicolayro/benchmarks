#!/bin/bash

SIZE=1000

mkdir output/blas
for t in `seq 1 10`; do
    export OMP_NUM_THREADS=1
    export GOMP_CPU_AFFINITY=$t
    ./blas $SIZE > output/blas/$t.dat
done
