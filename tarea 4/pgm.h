#ifndef _pgm_h
#define _pgm_h

#include "pgm.h"

typedef struct pgmStruct {

    int maxVal;
    int width;
    int height;
    int** data;

} pgmImage ;

pgmImage* createPgmImage(int width, int height, int maxVal);

#endif
