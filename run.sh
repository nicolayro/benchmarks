#!/bin/bash

SIZE=10000000

export OMP_NUM_THREADS=8
for t in `seq 1 30`; do
    echo "$t"
    ./stream $SIZE > "output/precision.txt"
done
