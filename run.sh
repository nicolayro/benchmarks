#!/bin/bash


SIZE=10000000

for i in `seq 1 30`; do
    echo "$i"
    mkdir output/local/$i
    for t in `seq 1 10`; do
        export OMP_NUM_THREADS=1
        export GOMP_CPU_AFFINITY=$t
        ./stream $SIZE > output/speed/$i/$t.dat
    done
done
