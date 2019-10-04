#include<stdlib.h>
#include<stdio.h>
#include "rbtree.h"
#include "printTree.h"

void test_rbtree(){

    Node* r = NULL;

    insert(&r, 11);
    insert(&r, 2);
    insert(&r, 14);
    insert(&r, 1);
    insert(&r, 7);
    insert(&r, 15);
    insert(&r, 5);
    insert(&r, 8);
    insert(&r, 4);

    printf("\n");
    print_ascii_tree(r);

    printf("\n");

    int n = 4;
    printf("%d in red-balck tree? %s\n", n, searchKey(r, n) ? "Yes" : "No" );

    n = 14;
    printf("\n%d in red-balck tree? %s\n", n, searchKey(r, n) ? "Yes" : "No" );

    n = 16;
    printf("\n%d in red-balck tree? %s\n\n", n, searchKey(r, n) ? "Yes" : "No" );

}

int main(int argc, char const *argv[]) {

    test_rbtree();

    return 0;
}
