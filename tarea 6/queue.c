#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

Queue* createQueue(int capacity){

    Queue* q = malloc(sizeof *q);

    if ( q == NULL ) return q;

    q->s1 = malloc(sizeof *q->s1);
    q->s1->capacity = capacity;
    q->s1->top = -1;
    q->s1->data = malloc( q->s1->capacity * sizeof(int) );

    q->s2 = malloc(sizeof *q->s2);
    q->s2->capacity = capacity;
    q->s2->top = -1;
    q->s2->data = malloc( q->s2->capacity * sizeof(int) );

    return q;
}

void enqueue(Queue* q, int data){

    push(q->s1, data);
}

int dequeue(Queue* q){

    if ( isEmpty(q->s2) ){

        while ( !isEmpty(q->s1) ) {
            push( q->s2, pop(q->s1) );
        }
    }

    return pop(q->s2);
}

int rear(Queue* q){

    return top(q->s1);
}

int front(Queue* q){

    return top(q->s2);
}

int isEmptyQ(Queue* q){

    return isEmpty(q->s1) && isEmpty(q->s2);
}

int sizeQ(Queue* q){

    return size(q->s1) + size(q->s2);
}
