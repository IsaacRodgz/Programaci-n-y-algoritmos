#include<stdio.h>
#include<stdlib.h>
#include "tHeap.h"

tHeap* createTHeap(int capacity){

    tHeap* h = malloc( sizeof *h );

    h->capacity = capacity+1;
    h->size = 0;
    h->data = malloc( h->capacity * sizeof(int) );
}

int insert(tHeap* h, int value){

    // Error, heap is full
    if (h->size == h->capacity - 1) {
        return -1;
    }

    // Add new element at the end
    h->data[++h->size] = value;

    // Adjust heap structure
    bottomUpHeapify(h->data, h->size);

    return 0;
}

void swap(int* arr, int i, int j){

    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;

}

void bottomUpHeapify(int* arr, int k){

    while( k > 1 && arr[(k+1)/3] < arr[k] ){
        swap(arr, k , (k+1)/3);
        k = (k+1)/3;
    }
}

int removeMax(tHeap* h){

    if ( h->size == 0 ) {

        return -1;
    }

    int top = h->data[1];

    h->data[1] = h->data[h->size--];

    topDownHeapify(h->data, 1, h->size);

    return top;
}

void topDownHeapify(int* arr, int k, int n){

    while ( 3*k <= n ) {

        int j = maxIndex(arr, 3*k);

        if( arr[k] >= arr[j] ) break;

        swap(arr, k, j);

        k = j;
    }
}

int maxIndex(int* arr, int i){

    int t = arr[i-1] > arr[i] ? arr[i-1] : arr[i];
    int maxVal = t > arr[i+1] ? t : arr[i+1];

    int maxInd;

    for (int j = -1; j < 2; j++) {
        if(maxVal == arr[i-j]){
            maxInd = i-j;
            break;
        }
    }

    return maxInd;
}

void printHeap(tHeap* h){

    for (int i = 1; i <= h->size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}
