#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dyn_prog.h"

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

        if(i < N-1)
            swap( &prev, &current );
    }

    printf("\nMax weight: %d\n\n", current[W]);

}

void max_palindrom( const char* file_name ){

    char* word = "programarenc";

    int len = strlen(word);

    char** palin = malloc( len * sizeof *palin );
    palin[0] = calloc( len*len, sizeof **palin );
    for (int i = 1; i < len; i++) {
        palin[i] = palin[i-1] + len;
    }

    // Initialize palin matrix where index (i, j) represents substring from char at index i to j

    for (int i = 0; i < len; i++) {

        for (int j = 0; j < len; j++) {

            // words of length 1 are palindroms

            if ( i == j ) {

                palin[i][j] = 1;
            }

            // words of length 2 are palindroms if both characters are equal

            else if ( i-j == 1 || j-i == 1 ) {

                if ( word[i] == word[j] ) {

                    palin[i][j] = 1;
                }
            }

            // string has not been verified yet

            else {
                palin[i][j] = -1;
            }
        }
    }

    // Compute remaining cases

    for (int i = 0; i < len; i++) {

        for (int j = 0; j < len; j++) {

            if ( palin[i][j] == -1 && i < j) {

                if ( palin[i+1][j-1] == 1 && word[i] == word[j] ) {
                    palin[i][j] = 1;
                }
                else{
                    palin[i][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            printf("%2d ", palin[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

/* Helper Functions */

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
