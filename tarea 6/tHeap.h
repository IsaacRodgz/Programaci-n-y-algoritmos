#ifndef _tHeap_h
#define _tHeap_h

// Array-based  ternary heap structure

typedef struct ternary_heap{

    int capacity;
    int size;
    int* data;

} tHeap;

tHeap* createTHeap(int capacity);

int insert(tHeap* h, int value);

void bottomUpHeapify(int* array, int k);

void swap(int* arr, int i, int j);

int removeMax(tHeap* h);

void topDownHeapify(int* arr, int k, int n);

int maxIndex(int* arr, int i);

void printHeap(tHeap* h);

#endif
