#basic makefile for the project

all: test

test: main.o do_computations.o
	gcc -Wall -fopenmp -o test main.o do_computations.o

main.o: main.c
	gcc -Wall -fopenmp -c -o main.o main.c 

do_computations.o: do_computations.c
	gcc -Wall -fopenmp -O3 -c -o do_computations.o do_computations.c 

clean:
	rm -rf *o test


