
#include <stdio.h>

void printBits(size_t const size, void const * const ptr);

int main(){
    /*

    real = sign * M * 2^e

    With n bits:    

        binaryNumber = | 1 bit sign | q bits exp | p bits fraction |

        n = 1 + q + p

    If n = 64 -> q = 11 and p = 52

    double -> 64 bits -> 16 hexadecimal numbers

    myDouble = | 1 bit sign | 11 bits exp | 52 bits fraction |

    myDouble = |     s      |       k     |         m        |

    exp = k - 2^(10) - 1
    exp = k - 1023

    myDouble = (1-2*s) * M             * 2^e
    myDouble = (1-2*s) * (1 + f)       * 2^e
    myDouble = (1-2*s) * (1 + m*2^-p)  * 2^e
    myDouble = (1-2*s) * (1 + m*2^-52) * 2^e

    if m = 0 (52 bits fraction = 0)
        -> f = 0
        -> M = 1

    if m = 2^p - 1 = 2^52 - 1 ((52 bits fraction = 1))
        -> f = (2^52 - 1)*2^-52 = 1 - 2^-52 = 0.9999999999999998
        -> M = 2 - 2^-52 = 1.9999999999999998

    Therefore 1 <= M <= 1.9999999999999998 < 2

    epsilon -> Lowest number
    epsilon = 2 - 1.9999999999999998
    epsilon = 2.220446049250313e-16

    1)
        If:        
        
            k = 2^q - 1 = 2^11 - 1 = 2047 (exp = 1024) -> 11 bits exp  = 1
            m = 0 -> 52 bits frac = 0

                Then, myDouble = +Inf
                      myDouble = 0xEFF000000000000

                or,   myDouble = -Inf
                      myDouble = 0xFFF0000000000000

    2)
        If:        
        
            k = 2^q - 1 = 2^11 - 1 = 2047 (exp = 1024) -> 11 bits exp  = 1
            m != 0 -> at least 1 bit frac = 1

                Then, myDouble = NaN
                      0xEFF000000000001 <= myDouble <= 0xFFFFFFFFFFFFFFFF

    3)
        If:        
        
            k = 0 (exp = -1023) -> 11 bits exp  = 0
            m = 0 -> 52 bits frac = 0

                Then, myDouble = +0
                      myDouble = 0x0000000000000000

                or,   myDouble = -0
                      myDouble = 0x8000000000000000

    4)
        If:        
        
            k = 0 (exp = -1023) -> 11 bits exp  = 0
            m != 0 -> at least 1 bit frac = 1

                Then, myDouble = +/- 0.f * 2^-1022
                      myDouble = +/- m * 2^-1022                       

                      0x800FFFFFFFFFFFFF <= myDouble <= 0x000FFFFFFFFFFFFF
                      -1.0020841800044862e-292 <= myDouble <= 1.0020841800044862e-292

                       epsilon = 
            

    */
    
    double myDouble;

    // myInt = -1.0020841800044862e-292 -> lowest fraction (-0.x)
    myDouble = 0xFFFFFFFFFFFFFFF;
    printf("Decimal: %f\n", myDouble);
    printBits(sizeof(myDouble), &myDouble);

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
