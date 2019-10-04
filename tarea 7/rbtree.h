#ifndef _rbtree_h
#define _rbtree_h
#include "rbtree.h"

typedef struct StructNode{

    int data;
    int color;
    struct StructNode *left, *right, *parent;

} Node;

void rotateLeft(Node** r, Node* x);

void rotateRight(Node** r, Node* x);

void insertFixUp(Node** r, Node* x);

void insert(Node** root, int val);

int searchKey(Node* r, int val);

#endif
