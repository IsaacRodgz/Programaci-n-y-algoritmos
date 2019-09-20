all:

	gcc -c pgm.c -Wall -pedantic -std=c99 -O2
	gcc -c test.c -Wall -pedantic -std=c99 -O2
	gcc -o runTest pgm.o test.o

clean:

	rm -f runTest runTest pgm.o test.o
