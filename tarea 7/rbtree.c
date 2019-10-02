#include<stdio.h>
#include<stdlib.h>
#include "rbtree.h"
#include "printTree.h"
#define RED 1
#define BLACK 0

void rotateLeft(Node** r, Node* x){

    Node* y = x->right;

    // Adjust y->left to x->right

    x->right = y->left;

    if ( y->left == NULL )
        y->left->parent = x;

    // Adjust y->parent to x->parent

    y->parent = x->parent;

    // If x is the root, make y the new root

    if ( x->parent == NULL )
        (*r) = y;

    // If x is left child

    else if (x->parent->right == x)
        x->parent->right = y;

    // If x is right child

    else
        x->parent->left = y;

    y->left = x;
    x->parent = y;

}

void rotateRight(Node** r, Node* x){

    Node* y = x->left;

    // Adjust y->right to x->left

    x->left = y->right;

    if ( y->right == NULL )
        y->right->parent = x;

    // Adjust y->parent to x->parent

    y->parent = x->parent;

    // If x is the root, make y the new root

    if ( x->parent == NULL )
        (*r) = y;

    // If x is left child

    else if (x->parent->right == x)
        x->parent->right = y;

    // If x is right child

    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;

}

void insertFixUp(Node** r, Node* x){

    while ( x != *r && x->parent->color == RED ) {

        Node* y;

        if ( x->parent == x->parent->parent->left )
            y = x->parent->parent->right;
        else
            y = x->parent->parent->left;

        // Uncle is red

        if ( y->color == RED ) {

            x->parent->color = BLACK;
            y->color = BLACK;
            x->parent->parent->color = RED;
            x = x->parent->parent;
        }

        // Uncle is black: 4 cases (LL, LR, RL, RR)

        else{

            // Case 1: grandparent -> left == parent AND parent->left == x

            if ( x->parent->parent->left == x->parent && x->parent->left == x ) {

                // swap colors of parent and grandparent

                int temp = x->parent->color;
                x->parent->color = x->parent->parent->color;
                x->parent->parent->color = temp;

                // rotate grandparent right

                rotateRight(r, x->parent->parent);
            }

            // Case 2: grandparent -> left == parent AND parent->right == x

            else if ( x->parent->parent->left == x->parent && x->parent->right == x ) {

                // swap colors of x and grandparent

                int temp = x->color;
                x->color = x->parent->parent->color;
                x->parent->parent->color = temp;

                // rotate parent left

                rotateLeft(r, x->parent);

                // rotate x right

                rotateRight(r, x->parent);
            }

            // Case 3: grandparent -> right == parent AND parent->left == x

            else if ( x->parent->parent->right == x->parent && x->parent->left == x ) {

                // swap colors of x and grandparent

                int temp = x->color;
                x->color = x->parent->parent->color;
                x->parent->parent->color = temp;

                // rotate parent left

                rotateRight(r, x->parent);

                // rotate x right

                rotateLeft(r, x->parent);
            }

            // Case 1: grandparent -> left == parent AND parent->left == x

            else if ( x->parent->parent->right == x->parent && x->parent->right == x ) {

                // swap colors of parent and grandparent

                int temp = x->parent->color;
                x->parent->color = x->parent->parent->color;
                x->parent->parent->color = temp;

                // rotate grandparent right

                rotateLeft(r, x->parent->parent);
            }
        }
    }

    (*r)->color = BLACK;
}

void insert(Node** root, int val){

    Node* x = malloc(sizeof *x);
    x->data = val;
    x->left = x->right = x->parent = NULL;

     // If first insert, paint black and return

    if ( (*root) == NULL){

        x->color = BLACK;
        (*root) = x;
    }

    else{

        x->color = RED;

        Node* a;
        Node* b = (*root);

        while ( b != NULL ) {

            a = b;

            if ( x->data < b->data )
                b = b->left;
            else
                b = b->right;
        }

        x->parent = a;

        if ( x->data < a->data )
            a->left = x;
        else
            a->right = x;
    }

    insertFixUp(root, x);

}
