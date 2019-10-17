#include<stdlib.h>
#include<stdio.h>
#include "dyn_prog.h"

void test_winning_prob(const char* file_name){

    double prob = winning_prob(3, 2, 10);

    printf("\nProbability of pumas winning n matches: %lf\n\n", prob);

}

void test_palindrom(const char* file_name){

    int max_len_palindrom = max_palindrom_hard(file_name);

    printf("\nMaximum lenght subsequence palindrom found : %d\n\n", max_len_palindrom);

}

void test_knapsack(const char* file_name){

    knapsack(file_name);

}

int main(int argc, char const *argv[]) {

    if ( argc == 1 )
        printf("Error: Missing parameter: file_name\n");

    else
        test_winning_prob(argv[1]);

    return 0;
}
