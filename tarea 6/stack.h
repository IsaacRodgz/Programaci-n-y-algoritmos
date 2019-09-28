#ifndef _stack_h
#define _stack_h

typedef struct StackStruct{

    int capacity;
    int top;
    int* data;
} Stack;

Stack* createStack(int capacity);

int isEmpty(const Stack* s);

int size(const Stack* s);

void push(Stack* s, int data);

int pop(Stack* s);

int top(Stack* s);

#endif
