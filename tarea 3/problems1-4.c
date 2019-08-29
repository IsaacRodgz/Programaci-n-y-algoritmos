#include<stdio.h>
#include<stdlib.h>

struct myStruct
{
    char *b;
    char a;
    char c;
};

void problema1(){

    printf("\nNumber of bytes: %d\n\n", (int)sizeof(struct myStruct));

/*
    2. Una variable tipo apuntador, en una arquitectur de 64 bits, tiene un tamaño de 8 bytes. Por lo que al reservar memoria para
    la variable "c" de tipo char, le faltan 7 bytes para completar la lectura, por lo que los agrega debajo de la variable "c".
    Después lee los 8 bytes del apuntador a char, "b", y finalmente leerá a la variable char "a" con 8 bytes,
    añadiendo un padding de 7 bytes extra.

    3. EL tamaño mínimo al que se podría llegar es de 16 bytes, ya que para leer al apuntador se requieren 8 bytes, si juntamos
    a las variables "a" y "c", sólo se tendrá que añadir un padding de 6 bytes para completar los 8 bytes a leer, es decir,
    leerá a "a" y "c" con 8 bytes y después a "b" con otros 8 bytes

*/

}

void problema2(){

    float a, b, *ptr_a, *ptr_b, **dptr_a, **dptr_b;

    a = -1.0;

    b = 5.0;

/*
    Se inicializa el apuntador ptr_a para que haga referencia al valor de la variable a, a través de su dirección de memoria
    (obtenida con el operador &)

    >> ptr_a -> a
    >> a = -1.0
    >> ptr_a = "Dirección de memoria de a"
*/
    ptr_a = &a;

/*
    Se inicializa el doble apuntador dptr_a para que haga referencia al valor del apuntador ptr_a, a través de su dirección de memoria

    >> dptr_a -> ptr_b
    >> dptr_a = "dirección de memoria de ptr_b"
    >> ptr_b -> "basura"
*/
    dptr_a = &ptr_b;

/*
    Se inicializa el doble apuntador dptr_b, con el contenido de dptr_a, que es la dirección de memoria del apuntador ptr_b

    >> dptr_b = "contenido de dptr_a" = "dirección de memoria de ptr_b"
    >> dptr_a -> ptr_b
    >> dptr_a = "dirección de memoria de ptr_b"
*/
    dptr_b = dptr_a;

/*
    Se "desreferencia" el doble apuntador dptr_b, para que en la dirección a la que apunta guarde el valor de ptr_a. Y como dptr_b
    hace referencia al apuntador ptr_b, ahora ptr_b guardará la dirección a la que hace referencia ptr_a, es decir ptr_b hará
    referencia a la variable a

    >> ptr_b = "contenido de ptr_a" = "Dirección de memoria de a"
    >> ptr_b -> a
    >> ptr_a -> a
    >> ptr_a = "Dirección de memoria de a"
    >> a = -1.0
*/
    *dptr_b = ptr_a;

/*
    Se "desreferencia" el doble apuntador dptr_a 2 veces, como dptr_a hace referencia al apuntador ptr_b, se obtiene la dirección
    de memoria que guarda ptr_b, y como ptr_b hace referencia a la variable "a", con el segundo operador de "desreferencia",
    se accede a la dirección de memoria de "a" y ahí se guarda el valor de -3.0

    >> dptr_a -> ptr_b
    >> dptr_a = "dirección de memoria de ptr_b"
    >> ptr_b = "contenido de ptr_a" = "Dirección de memoria de a"
    >> ptr_b -> a
    >> a = -3.0
*/
    (**dptr_a) = -3.0;
}

void problema3(){

/*
    Se hace un casteo a la dirección de memoria de z, a tipo apuntador entero sin signo, para que pueda ser leido/interpretado
    como un entero sin signo, sin modificar los bits de z.
*/
    float z = 1.5;
    unsigned int iz = *(unsigned int*)&z;
    fprintf(stderr, "Diff inv : %x \n", iz);

/*
    En el caso de un double, como es de 8 bytes (siguiendo el formato IEEE 754), necesitamos un entero que también pueda leer 8 bytes.
    Para este caso, el tipo unsigned long int también tiene 8 bytes. También cambiamos el formato de impresión a %lx, para ajustarlo a un long.
*/

    unsigned long int izl = *(unsigned long int*)&z;
    fprintf(stderr, "Diff inv : %lx \n", izl);
}

int ** problema4(int n){

    // Dynamic structure used

    // coef[0] -> [1]
    // coef[1] -> [1, 1]
    // coef[2] -> [1, 2, 1]
    // coef[3] -> [1, 3, 3, 1]
    // ...

    int **coef = malloc( (n+1) * sizeof *coef);
    for(int i = 0; i <= n; i++ )
        coef[i] = malloc( (i+1) * sizeof *coef );

    // Trivial cases, n = 0 or n = 1

    coef[0][0] = 1;
    if(n == 0){

        return coef;
    }

    coef[1][0] = 1;
    coef[1][1] = 1;
    if(n == 1){

        return coef;
    }

    // Generate Pascal's triangle coefficients from 2 to n

    for(int i = 2; i <= n; i++){

        coef[i][0] = 1;
        coef[i][i] = 1;

        for(int j = 1; j < i; j++){

            coef[i][j] = coef[i-1][j-1] + coef[i-1][j];
        }
    }

    // Print Pascal's triangle coefficients

    printf("\n\n");
    int padding = n;
    for(int i = 0; i <= n; i++){

        for(int j = 0; j <= padding; j++){
            printf(" ");
        }

        for(int j = 0; j <= i; j++){
            printf("%d ", coef[i][j]);
        }

        padding -= 1;

        printf("\n");

    }
    printf("\n\n");

    return coef;
}

int main(){

    //problema1();

    //problema2();

    //problema3();

    //problema4(7);

    return 0;
}
