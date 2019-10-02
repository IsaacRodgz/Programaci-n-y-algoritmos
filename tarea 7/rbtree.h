#ifndef _rbtree_h
#define _rbtree_h
#include "rbtree.h"

typedef struct StructNode{

    int key;
    int color;
    Node *left, *right, *parent;

} Node;

void insertFixUp(Node** r, Node* x);

void insert(Node** root, int val);

#endif
