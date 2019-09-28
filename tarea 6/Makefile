all:

	gcc -c tHeap.c
	gcc -c stack.c
	gcc -c queue.c
	gcc -c test.c -Wall -pedantic
	gcc -o runTest tHeap.o stack.o queue.o test.o

clean:

	rm -f runTest *.o
