all:

	gcc -c dyn_prog.c -Wall -pedantic-errors -g
	gcc -c test.c -Wall -pedantic -g
	gcc -o runTest dyn_prog.o test.o -g

clean:

	rm -f runTest *.o
