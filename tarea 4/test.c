#include<stdlib.h>
#include<stdio.h>
#include "pgm.h"

int main(int argc, char const *argv[]) {

    if ( argc == 1 ) {
        fprintf(stderr, "\nError: Falta la ruta de la imagen\n\n");
        exit(-1);
    }

    int width = 10;
    int height = 10;
    int maxVal = 255;

    pgmImage* image;

    image = readPgmImage(argv[1]);

    writePgmImage(image, "copyImage.pgm");

    return 0;
}
