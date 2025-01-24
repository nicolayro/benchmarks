CFLAGS+= -std=c11 -Wall -Wextra -pedantic -Werror -O2

BLAS= -I/opt/homebrew/Cellar/openblas/0.3.29/include/ \
-L/opt/homebrew/Cellar/openblas/0.3.29/lib \
-lopenblas

stream: stream.c
	gcc-14 $(CFLAGS) -fopenmp -o stream stream.c

blas: blas.c
	gcc-14 $(CFLAGS) $(BLAS) -o blas blas.c
