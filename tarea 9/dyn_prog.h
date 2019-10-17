#ifndef _dyn_prog_h
#define _dyn_prog_h
#include "dyn_prog.h"

void knapsack( const char* file_name );

int max_palindrom_hard( const char* word );

double winning_prob( int p, int a, int n );

/* Bonus */

void max_palindrom( const char* file_name );

/* Helper Functions */

void print(int* a, int n);

void swap(int** a, int** b);

int max(int a, int b);

int min(int a, int b);

void knapsack_read( const char* file_name, int* W, int* N, int** ws, int** vs );

#endif
