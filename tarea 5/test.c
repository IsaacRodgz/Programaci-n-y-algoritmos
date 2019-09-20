#include<stdlib.h>
#include<stdio.h>
#include "dic.h"

void test_dict(const char* file_name, int n, int W){

    // Array to store n words of max length W each
    char words[n][W];

    if ( read(n, W, words, file_name) != 0 ) {
        printf("\nError while reading file %s\n\n", file_name);
    }
    printf("\n%d words parsed successfully from file %s\n", n, file_name);

    sort_words(n, W, words);
    printf("\nWords sorted\n");

    int unique_count;
    char** words_dict = unique_words(n, W, words, &unique_count);
    printf("\n%d unique words filtered\n", unique_count);

    printf("\n");
    for (int i = 0; i < unique_count; i++) {
        printf("%s\n", words_dict[i]);
    }

    //char* w2search = "Quijote";
    //printf("\n[%s] in dictionary? %s\n\n", w2search, (word_search(unique_count, W, words_dict, w2search) == 1 )? "Yes" : "No" );

    for (int i = 0; i < unique_count; i++) {
        free(words_dict[i]);
    }
    free(words_dict);

}

int main(int argc, char const *argv[]) {

    if ( argc == 1 ) {
        fprintf(stderr, "\nError: Three arguments missing: textFilePath numWords wordLength\n\n");
        exit(-1);
    } else if ( argc == 2 ) {
        fprintf(stderr, "\nError: Two arguments missing: numWords wordLength\n\n");
        exit(-1);
    } else if ( argc == 3 ) {
        fprintf(stderr, "\nError: One argument missing: wordLength\n\n");
        exit(-1);
    } else
        test_dict( argv[1], atoi(argv[2]), atoi(argv[3]) );

    return 0;
}
