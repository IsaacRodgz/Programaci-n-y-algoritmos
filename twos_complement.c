
#include <stdio.h>

void printBits(size_t const size, void const * const ptr);

int main(){
    /*

    int -> 32 bits -> 8 hexadecimal numbers

    positives in range: 1 - 2^(n-1) - 1
                      : 1 - 2,147,483,647
                      : 00000000000000000000000000000001 - 01111111111111111111111111111111
                      : 0x00000001 - 0x7FFFFFFF

    negatives in range: -2^(n-1) - -1
                      : -2,147,483,648 - -1
                      : 10000000000000000000000000000000 - 11111111111111111111111111111111
                      : 0x80000000 - 0xFFFFFFFF

    */
    
    int myInt;

    // myInt = 1
    myInt = 0x1;
    printf("Decimal: %d\n", myInt);
    printBits(sizeof(myInt), &myInt);

    printf("\n");

    // myInt = -1
    myInt = 0xFFFFFFFF;
    printf("Decimal: %d\n", myInt);
    printBits(sizeof(myInt), &myInt);

    printf("\n");

    // myInt = -2147483648 -> lowest number
    myInt = 0x80000000;
    printf("Decimal: %d\n", myInt);
    printBits(sizeof(myInt), &myInt);

    printf("\n");

    // myInt = 2147483647 -> largest number
    myInt = 0x7FFFFFFF;
    printf("Decimal: %d\n", myInt);
    printBits(sizeof(myInt), &myInt);
}


void printBits(size_t const size, void const * const ptr){

    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    printf("Binary: ");

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
