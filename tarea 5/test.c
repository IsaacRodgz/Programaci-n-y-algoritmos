#include<stdlib.h>
#include<stdio.h>
#include "dic.h"
#define W 100

void test_dict(const char* file_name, int n){

    char words[n][W];

    if ( read(n, W, words, file_name) != 0 ) {
        printf("\nError while reading file %s\n\n", file_name);
    }

    printf("\n\nWords found:\n\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s\n", i+1, words[i]);
    }
    printf("\n\n");

    sort_words(n, W, words);

    printf("Sorted words:\n\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s\n", i+1, words[i]);
    }
    printf("\n\n");

    int unique_count;
    char** words_dict = unique_words(n, W, words, &unique_count);

    printf("Unique words filtered:\n\n");
    for (int i = 0; i < unique_count; i++) {
        printf("[%d] %s\n", i+1, words_dict[i]);
    }
    printf("\n\n");

    char* w2search = "Quijote";
    printf("%s in dictionary? %s\n\n", w2search, (word_search(unique_count, W, words_dict, w2search) == 1 )? "Yes" : "No" );

}

int main(int argc, char const *argv[]) {

    if ( argc == 1 ) {
        fprintf(stderr, "\nError: Two arguments missing: textFilePath numWords\n\n");
        exit(-1);
    } else if ( argc == 2 ) {
        fprintf(stderr, "\nError: One argument missing: numWords\n\n");
        exit(-1);
    } else
        test_dict( argv[1], atoi(argv[2]) );

    return 0;
}
