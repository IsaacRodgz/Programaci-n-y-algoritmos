#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dic.h"

int read(int n, int W, char words[n][W], const char* file_name){

    FILE* file_text;

    if ( (file_text = fopen(file_name, "r")) == NULL ) {
        fprintf(stderr, "\nError while reading %s\n\n", file_name);
        return 1;
    }

    int c;
    int word_count = 0;
    int symbol_count = 0;
    char w[W];

    // Read n words

    while ( word_count < n ) {

        // Read word and check if char is in [a-z][A-Z] range or if it's a latin symbol from ISO-8859-1

        while ( (c = fgetc(file_text)) != EOF && ( (c > 64 && c < 91) || (c > 96 && c < 123) || c > 191 ) ) {

            if(symbol_count < W){

                if (c > 64 && c < 91) // Mayuscula a minuscula
                    c += 32;
                else if( c == 233 || c == 237 || c == 243 ) // e, i, o sin acento
                    c -= 132;
                else if( c == 225 ) // a sin acento
                    c -= 128;
                else if( c == 250 ) // u sin acento
                    c -= 133;
                else if( c == 241 ) // ñ -> n
                    c -= 131;
                else if( c == 193 ) // A sin acento
                    c -= 96;
                else if( c == 201 || c == 205 || c == 211 ) // E, I, O sin acento minuscula
                    c -= 100;
                else if( c == 218 ) // U sin acento
                    c -= 101;

                w[symbol_count++] = c;
            }
        }

        // Verify that word has length at most W and the word is not the '\n' character

        if ( symbol_count < W-1 && w[0] != 13 && symbol_count > 0 ) {

            strcpy(words[word_count], w);
            word_count++;
        }

        memset(w,0,sizeof(w));
        symbol_count = 0;
    }

    fclose(file_text);
    return 0;
}

void swap(char w1[], char w2[], int size){
    char temp[size];
    strcpy(temp, w1);
    strcpy(w1, w2);
    strcpy(w2, temp);
}

void sort_words(int n, int W, char words[n][W]){

    // Sort words by bubble sort

    for (int i = 0; i < n-1; i++){

        for (int j = 0; j < n-i-1; j++){

            if (strcmp(words[j], words[j+1]) > 0)
                swap(words[j], words[j+1], W);
        }
    }
}

char** unique_words(int n, int W, char words[n][W], int* unique_count){

    *unique_count = 0;

    // Count how many unique words the array has

    for (int i = 0; i < n-1; i++) {

        if ( strcmp(words[i], words[i+1]) != 0 ) {
            (*unique_count)++;
        }
    }
    (*unique_count)++;

    // Array to save unique words

    char** words_dict = malloc( (*unique_count) * sizeof *words_dict );
    for (int i = 0; i < (*unique_count); i++) {
        words_dict[i] = calloc( W, sizeof *words_dict[i] );
    }

    // Add unique words to new array

    int k = 0;
    int i = 0;
    for (i = 0; i < n-1; i++) {

        if ( strcmp(words[i], words[i+1]) != 0 ) {
            strcpy(words_dict[k++], words[i]);
        }
    }
    strcpy(words_dict[k++], words[i]);

    return words_dict;
}

int word_search(int n, int W, char** words, char* w2search){

    // Binary search of word w2search in words sorted array

    int k = 0;
    for (int mid = n/2; mid > 0; mid /= 2) {

        while ( k+mid < n && strcmp(words[k+mid], w2search) <= 0 )
            k += mid;
    }

    if ( strcmp(words[k], w2search) == 0 )
        return 1;
    else
        return 0;

}
