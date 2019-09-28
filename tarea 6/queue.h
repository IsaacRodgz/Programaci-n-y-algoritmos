#ifndef _queue_h
#define _queue_h
#include "stack.h"

typedef struct QueueStruct{

    Stack* s1;
    Stack* s2;

} Queue;

Queue* createQueue(int capacity);

void enqueue(Queue* q, int data);

int dequeue(Queue* q);

int rear(Queue* q);

int front(Queue* q);

int isEmptyQ(Queue* q);

int sizeQ(Queue* q);

#endif
