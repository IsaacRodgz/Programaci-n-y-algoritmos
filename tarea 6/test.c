#include<stdlib.h>
#include<stdio.h>
#include "tHeap.h"
#include "stack.h"
#include "queue.h"

void test_queue(){

    Queue* q = createQueue(5);

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);

    printf("\n");
    printf("Initial size: %d\n", sizeQ(q));

    printf("\nDequeue: %d\n", dequeue(q));
    printf("Size: %d\n", sizeQ(q));

    printf("\n\nDequeue: %d\n", dequeue(q));
    printf("Size: %d\n", sizeQ(q));

    enqueue(q, 6);
    printf("\n\nEnqueue: %d\n", rear(q));
    printf("Size: %d\n", sizeQ(q));

    enqueue(q, 7);
    printf("\n\nEnqueue: %d\n", rear(q));
    printf("Size: %d\n", sizeQ(q));

    printf("\n\nDequeue: %d\n", dequeue(q));
    printf("Size: %d\n", sizeQ(q));

    printf("\n\nDequeue: %d\n", dequeue(q));
    printf("Size: %d\n", sizeQ(q));

    printf("\n\nDequeue: %d\n", dequeue(q));
    printf("Size: %d\n", sizeQ(q));

    printf("\n\nDequeue: %d\n", dequeue(q));
    printf("Size: %d\n", sizeQ(q));

    printf("\n\nDequeue: %d\n", dequeue(q));
    printf("Size: %d\n", sizeQ(q));
}

void test_heap(){

    tHeap* h = createTHeap(10);

    printf("\nInsert elements in ternary heap:\n\n");
    insert(h, 15);
    insert(h, 10);
    insert(h, 5);
    insert(h, 8);
    printHeap(h);
    insert(h, 11);
    printHeap(h);
    insert(h, 12);
    printHeap(h);
    insert(h, 2);
    insert(h, 3);
    insert(h, 4);
    if ( insert(h, 20) != 0 ) {
        printf("\nElement could not be inserted, heap is full\n");
    }

    printHeap(h);
    printf("\n");

    printf("Remove max: ");
    int maxVal = removeMax(h);
    printf("%d\n\n", maxVal);
    printHeap(h);
    printf("\n");

    printf("Remove max: ");
    maxVal = removeMax(h);
    printf("%d\n\n", maxVal);
    printHeap(h);
    printf("\n");
}

int main(int argc, char const *argv[]) {

    test_queue();

    return 0;
}
