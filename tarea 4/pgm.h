#ifndef _pgm_h
#define _pgm_h

typedef struct pgmStruct {

    int maxVal;
    int width;
    int height;
    int** data;

} pgmImage ;

pgmImage* createPgmImage(int width, int height, int maxVal);

void skipComments(FILE* fp);

pgmImage* readPgmImage(const char* filename);

void writePgmImage(pgmImage* image, const char* filename);

#endif
