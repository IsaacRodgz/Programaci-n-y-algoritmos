#include<stdlib.h>
#include<stdio.h>
#include "pgm.h"

int main(int argc, char const *argv[]) {

    int width = 10;
    int height = 10;
    int maxVal = 255;

    pgmImage* image;

    image = readPgmImage("balloons.ascii.pgm");

    writePgmImage(image, "balloonsWrite.ascii.pgm");

    return 0;
}
