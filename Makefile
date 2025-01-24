CFLAGS+= -std=c11 -Wall -Wextra -pedantic -Werror -O2

stream: stream.c
	gcc-14 $(CFLAGS) -fopenmp -o stream stream.c
