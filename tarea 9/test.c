#include<stdlib.h>
#include<stdio.h>
#include "dyn_prog.h"

void test_knapsack(const char* file_name){

    knapsack(file_name);

}

int main(int argc, char const *argv[]) {

    if ( argc == 1 )
        printf("Error: Missing parameter: file_name\n");

    else
        test_knapsack(argv[1]);

    return 0;
}
