#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

Stack* createStack(int capacity){

    Stack* s = malloc(sizeof *s);

    if ( s == NULL ) return s;

    s->capacity = capacity;
    s->top = -1;
    s->data = malloc( s->capacity * sizeof(int) );

    return s;
}

int isEmpty(const Stack* s){

    return s->top == -1;
}

int size(const Stack* s){

    return s->top+1;
}

void push(Stack* s, int data){

    if ( s->top == s->capacity-1 ) {
        return;
    }

    s->data[++s->top] = data;
}

int pop(Stack* s){

    if ( isEmpty(s) ) {
        return -1;
    }

    return s->data[s->top--];
}

int top(Stack* s){

    return s->data[s->top];
}
