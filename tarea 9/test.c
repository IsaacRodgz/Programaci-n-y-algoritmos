#include<stdlib.h>
#include<stdio.h>
#include "dyn_prog.h"

void test_winning_prob(int p, int a, int n){

    double prob = winning_prob(p, a, n);

    printf("\nProbability of pumas winning %d matches: %lf\n\n", n, prob);

}

void test_palindrom(const char* word){

    int max_len_palindrom = max_palindrom_hard(word);

    printf("\nMaximum lenght subsequence palindrom found : %d\n\n", max_len_palindrom);

}

void test_knapsack(const char* file_name){

    knapsack(file_name);

}

int main(int argc, char const *argv[]) {

    if ( argc == 1 )
        printf("\nError: Missing parameterse\n\n");

    switch ( atoi(argv[1]) ) {
        case 1:
            if ( argc == 2 )
                printf("Error: Missing parameter: filename\n\n");
            else
                test_knapsack(argv[2]);
            break;

        case 2:
            if ( argc == 2 )
                printf("\nError: Missing parameter: palindrom_string\n\n");
            else
                test_palindrom(argv[2]);
            break;

        case 3:
            if ( argc < 5 )
                printf("\nError: Missing parameters\n\n");
            else
                test_winning_prob(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
            break;
    }

    return 0;
}
