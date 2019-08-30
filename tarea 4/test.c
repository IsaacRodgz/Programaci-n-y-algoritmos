#include<stdlib.h>
#include<stdio.h>
#include "pgm.h"

int main(int argc, char const *argv[]) {

    int width = 10;
    int height = 10;
    int maxVal = 255;

    pgmImage* image;

    image = createPgmImage(width, height, maxVal);

    printf("\n%d\n\n", image->data[0][0]);

    return 0;
}
