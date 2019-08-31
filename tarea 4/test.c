#include<stdlib.h>
#include<stdio.h>
#include "pgm.h"

int main(int argc, char const *argv[]) {

    int width = 10;
    int height = 10;
    int maxVal = 255;

    pgmImage* image;

    image = openPgmImage("balloons.ascii.pgm");

    printf("\n%d\n\n", image->data[479][638]);

    return 0;
}
