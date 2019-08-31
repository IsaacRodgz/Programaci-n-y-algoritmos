#include<stdio.h>
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

void skipComments(FILE* fp){

    int c;

    fscanf(fp, " ");

    while ( ( c = fgetc(fp) ) == '#'){

        while ( ( c = fgetc(fp) ) != '\n'  &&  c != EOF);
        fscanf(fp, " ");
    }

    ungetc(c, fp);
}

pgmImage* openPgmImage(const char* filename){

    FILE* pgmFile;

    if ( ( pgmFile = fopen(filename, "r") ) == NULL ) {

        fprintf(stderr, "\n[Error]: while trying to open file %s\n\n", filename);
        exit(-1);
    }

    // Validate magic number 'P2' for raw format
    if( fgetc(pgmFile) != 'P' || fgetc(pgmFile) != '2' ){

        fprintf(stderr, "\n[Error]: pgm image %s not in raw format\n\n", filename);
        exit(-1);
    }

    // Read width, height and maximum grayscale value
    int width;
    int height;
    int maxVal;

    int readWidthFlag = 0;
    int readHeightFlag = 0;
    int readmaxValFlag = 0;

    skipComments(pgmFile);
    readWidthFlag = fscanf(pgmFile, "%d", &width);

    skipComments(pgmFile);
    readHeightFlag = fscanf(pgmFile, "%d", &height);

    skipComments(pgmFile);
    readmaxValFlag = fscanf(pgmFile, "%d", &maxVal);

    printf("\n%d %d %d\n\n", width, height, maxVal);

    if( readWidthFlag != 1 || readHeightFlag != 1 || readmaxValFlag != 1 ){

        fprintf(stderr, "\n[Error]: Could not read width, height or maximum grayscale value from file\n\n");
        exit(-1);
    }

    pgmImage* image = createPgmImage(width, height, maxVal);

    int valsRead;
    int value;

    int i;
    int j;
    int count = 0;

    while ( ( valsRead = fscanf(pgmFile, "%d", &value) ) != EOF && valsRead == 1) {
        
        i = count/640;
        j = count%640;

        image->data[i][j] = value;

        count++;
    }

    fclose(pgmFile);

    return image;
}
