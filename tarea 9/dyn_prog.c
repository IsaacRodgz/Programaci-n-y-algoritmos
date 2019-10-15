#include<stdio.h>
#include<stdlib.h>
#include "dyn_prog.h"

void print(int* a, int n){

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

}

void swap(int** a, int** b){

    int* temp = *a;
    *a = *b;
    *b = temp;
}

int max(int a, int b){

    return a > b ? a : b;
}

void knapsack_read( const char* file_name, int* W, int* N, int** ws, int** vs ){

    FILE* fp;

    if ( ( fp = fopen(file_name, "r") ) == NULL ) {

        fprintf(stderr, "\n[Error]: while trying to open file %s\n\n", file_name);
        exit(-1);
    }

    // first line: weight_capacity num_items
    fscanf(fp, "%d", W);
    fscanf(fp, "%d", N);

    printf("\nWeight capacity: %d\n", *W);
    printf("Number of items: %d\n\n", *N);

    // Create arrays of item weights and values

    *ws = malloc(*N * sizeof **ws);
    *vs = malloc(*N * sizeof **vs);

    for (int i = 0; i < *N; i++) {

        fscanf(fp, "%d %d", &(*ws)[i], &(*vs)[i]);

    }
}

void knapsack( const char* file_name ){

    // Read data

    // total weight capacity
    int W;

    // number of items
    int N;

    // items weight
    int* ws;

    // items values
    int* vs;

    knapsack_read(file_name, &W, &N, &ws, &vs);

    // helper arrays for subproblem solutions

    int* prev = calloc(W+1, sizeof(int));
    int* current = calloc(W+1, sizeof(int));

    // begin iteration

    for (int i = 0; i < N; i++) {

        for (int w = 0; w <= W; w++) {

            if ( ws[i] <= w ) {
                current[w] = max( prev[w], vs[i] + prev[w-ws[i]] );
            }
            else{
                current[w] = prev[w];
            }
        }

        printf("Current: \n\n");
        print(current, W+1);
        printf("\n");

        swap( &prev, &current );
    }

    printf("\nMax weight: %d\n\n", prev[W]);

}
