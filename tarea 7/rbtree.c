#include<stdio.h>
#include<stdlib.h>
#include "rbtree.h"
#define RED 1
#define BLACK 0

void insertFixUp(Node** r, Node* x){


}

void insert(Node** root, int val){

    Node* x = malloc(sizeof *x);
    x->data = val;
    x->left = x->right = x->parent = NULL;

     // If first insert, paint black and return

    if (*root == NULL){

        x->color = BLACK;
        (*root) = x;
    }

    else{

        x->color = RED;

        Node* a;
        Node* b = (*root);

        while ( b != NULL ) {

            a = b;

            if ( r->val < b->val )
                b = b->left;
            else
                b = b->right;
        }
    }

    x->parent = a;

    if ( x->val < a->val )
        a->left = x;
    else
        a->right = x;

    insertFixUp(root, x);
    
}
