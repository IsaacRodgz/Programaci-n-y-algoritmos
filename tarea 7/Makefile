all:

	gcc -c rbtree.c -Wall -pedantic-errors -Werror -g
	gcc -c printTree.c -Wall -pedantic-errors -Werror -g
	gcc -c test.c -Wall -pedantic -g
	gcc -o runTest printTree.o rbtree.o test.o -g

clean:

	rm -f runTest *.o
