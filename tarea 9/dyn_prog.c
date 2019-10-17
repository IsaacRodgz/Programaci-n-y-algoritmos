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

/* Function to calculate max lenght palindrom subsequence */

int max_palindrom_hard( const char* word ){

    int len = strlen(word);

    char** palin = malloc( len * sizeof *palin );
    palin[0] = calloc( len*len, sizeof **palin );
    for (int i = 1; i < len; i++) {
        palin[i] = palin[i-1] + len;
    }

    // subsequences of lenght 1 are always palindroms

    for (int i = 0; i < len; i++) {

        palin[i][i] = 1;
    }

    // Iterate over subsequences of size sublen from 2 to word_lenght

    for (int sublen = 2; sublen <= len; sublen++) {

        // Check subsequence(i, j) of size sublen

        for (int i = 0; i <= len-sublen; i++) {

            int j = i + sublen - 1;

            // subsequences of size 2 are palindroms if both characters are equal

            if ( word[i] == word[j] && sublen == 2 ) {

                palin[i][j] = 2;
            }

            // if extremes are equal, subsequence(i, j) is a palindrom two chars larger than subsequence(i+1, j-1)

            else if ( word[i] == word[j] ) {

                palin[i][j] = palin[i+1][j-1] + 2;
            }

            // otherwise the longest subsequence(i,j) palindrom
            // is either the longest of subsequence(i,j-1) or subsequence(i+1,j)

            else{

                palin[i][j] = max( palin[i][j-1], palin[i+1][j] );
            }
        }
    }

    return palin[0][len-1];
}

double winning_prob( int p, int a, int n ){

    double** probs = malloc( n * sizeof *probs );
    probs[0] = calloc( n*n, sizeof **probs );
    for (int i = 1; i < n; i++) {
        probs[i] = probs[i-1] + n;
    }

    // p(i, j) = probability of pumas winning the series
    // given pumas has won i games and america has won j games

    // p(n, j) = 1 for j = a, a+1, ..., n-1. Pumas have already won the series.

    for (int j = a; j < n-1; j++) {

        probs[n-1][j] = 1.0;
    }

    // p(i, n) = 0 for j = p, p+1, ..., n-1. America has already won the series.

    for (int i = p; i < n-1; i++) {

        probs[i][n-1] = 0.0;
    }

    // p(i, j) = 0.5 * p(i+1, j) + 0.5 * p(i, j+1). The two cases from which pumas can still win.

    for (int iter = n-2; iter >= max(p, a); iter--) {

        for (int i = iter; i >= a; i--) {

            printf("[%d][%d]\n", iter, i);

            if( i == iter )
                probs[iter][i] = 0.5;
            else
                probs[iter][i] = 0.5 * probs[iter+1][i] + 0.5 * probs[iter][i+1];
        }

        for (int j = iter-1; j >= p; j--) {

            probs[j][iter] = 0.5 * probs[j+1][iter] + 0.5 * probs[j][iter+1];
        }
    }

    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%6lf ", probs[i][j]);
        }
        printf("\n");
    }

    return probs[p][a];
}

void max_palindrom( const char* file_name ){

    char* word = "programarencradar";

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
                palin[i][j] = 0;
            }
        }
    }

    // Compute remaining cases

    int pad = 2;

    for (int i = 0; i < len-1; i++) {

        for (int j = 0; j < len-1-i; j++) {

            palin[j][j+pad] = palin[j+1][j+pad-1] == 1 && word[j] == word[j+pad];
        }

        pad+=1;
    }

    // Read from matrix the maximum lenght palindroms found

    pad = len-1;
    int found = 0;

    for (int i = 0; i < len; i++) {

        for (int j = 0; j < i+1; j++) {

            if ( palin[j][j+pad] == 1 ) {

                //printf("\nMax length of palindrom found is %d.\nWith the following substrings:\n\n", pad+1);

                printf("\n");
                for (int k = j; k < j+pad+1; k++) {
                    printf("%c", word[k]);
                }

                found = 1;
            }
        }

        if ( found == 1 )
            break;

        pad-=1;
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

int min(int a, int b){

    return a > b ? b : a;
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
