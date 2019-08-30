#include<stdlib.h>
#include "pgm.h"

pgmImage* createPgmImage(int width, int height, int maxVal){

    pgmImage* image = malloc( sizeof *image);
    image->width = width;
    image->height = height;
    image->maxVal = maxVal;
    image->data = malloc( height * sizeof *image->data );

    if ( image->data == NULL ) return NULL;

    image->data[0] = malloc( (width * height) * sizeof **image->data );
    for (int i = 1; i < height; i++)
        image->data[i] = image->data[i-1] + width;

    return image;
}

// TODO: READ AND WRITE FROM FILE
