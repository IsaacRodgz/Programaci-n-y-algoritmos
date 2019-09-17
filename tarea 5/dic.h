#ifndef _dic_h
#define _dic_h

int read(int n, int W, char words[n][W], const char* file_name);

void swap(char w1[], char w2[], int size);

void sort_words(int n, int W, char words[n][W]);

char** unique_words(int n, int W, char words[n][W], int* unique_count);

int word_search(int n, int W, char** words, char* w2search);

#endif
