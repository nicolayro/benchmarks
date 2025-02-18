CC:=gcc-14
CFLAGS+= -std=c11 -Wall -Wextra -pedantic -Werror -O2

BLAS= -I/opt/homebrew/Cellar/openblas/0.3.29/include/ \
-L/opt/homebrew/Cellar/openblas/0.3.29/lib \
-lopenblas

stream: stream.c
	$(CC) $(CFLAGS) -fopenmp -o stream stream.c

blas: blas.c
	$(CC) $(CFLAGS) $(BLAS) -o blas blas.c

clean:
	rm blas && rm stream

plot_blas:
	.venv/bin/python plot_blas.py

plot_stream:
	.venv/bin/python plot_stream.py
