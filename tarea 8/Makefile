all:

	gcc -c graph.c -Wall -pedantic-errors -g
	gcc -c test.c -Wall -pedantic -g
	gcc -o runTest graph.o test.o -g

clean:

	rm -f runTest *.o
