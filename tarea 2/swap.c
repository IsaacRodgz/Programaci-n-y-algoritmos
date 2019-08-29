#include<stdio.h>
#define SWAP(x, y) x=x^y;y=x^y;x=x^y;

void bin(unsigned n) 
{ 
    unsigned i; 
    for (i = 1 << 31; i > 0; i = i / 2) 
        (n & i)? printf("1"): printf("0"); 
} 

int main(){
/*
    for(int i =0; i <100; i +=2) {
        if(i%7==0)
            continue ;
        printf("%d\n", ++i);
    }

--------------------------------------------

    int i = 0;

    do{

        if(i%7==0){
            i+=2;
            continue;
        }
        printf("%d\n", ++i);
        i+=2;

    }while(i<100);
*/

    float f;

    scanf("%f", &f);

    unsigned int mask = (1 << 8) - 1;
    unsigned int exp = *(unsigned int *)&f;
    exp = exp >> 23;
    exp = (mask & exp) - 127;

    printf("\n%d\n\n", exp);

    return 0;
}
