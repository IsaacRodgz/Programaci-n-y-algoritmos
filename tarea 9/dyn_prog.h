#ifndef _dyn_prog_h
#define _dyn_prog_h
#include "dyn_prog.h"

void print(int* a, int n);

void swap(int** a, int** b);

int max(int a, int b);

void knapsack_read( const char* file_name, int* W, int* N, int** ws, int** vs );

void knapsack( const char* file_name );

#endif
