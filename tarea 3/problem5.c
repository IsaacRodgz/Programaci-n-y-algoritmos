#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct structList {
    int value;
    struct structList *next;
} list;

list* addElement(int element, list* prev){

    list *newNode = malloc( sizeof(*newNode) );
    newNode->value = element;
    newNode->next = prev;

    return newNode;
}

void print(list* l){

    list nodeIterate;
    nodeIterate = *l;

    printf("\n");

    while(nodeIterate.next != NULL){

        printf("%d", nodeIterate.value);
        printf(" -> ");
        nodeIterate = *nodeIterate.next;
    }
    printf("%d", nodeIterate.value);

    printf("\n\n");
}

void liberate(list* l){

    list* curr;

    while ( (curr = l) != NULL ) {
        l = l->next;
        free (curr);
    }
}

int getKthValue(int k, list* l){

    list nodeIterate = *l;
    int kCurrent = 1;

    while ( nodeIterate.next != NULL ) {

        if( k == kCurrent )
            return nodeIterate.value;
        nodeIterate = *nodeIterate.next;
        kCurrent++;
    }

    if( k == kCurrent )
        return nodeIterate.value;
    else{
        fprintf(stderr, "[Error]: List index out of bounds\n\n");
        exit(-1);
    }
}

int isEqual(list* la, list* lb){

    list iterA = *la;
    list iterB = *lb;

    while ( iterA.next != NULL && iterB.next != NULL ) {

        if ( iterA.value != iterB.value )
            return FALSE;

        iterA = *iterA.next;
        iterB = *iterB.next;
    }

    if ( iterA.value != iterB.value )
        return FALSE;

    if( (iterA.next != NULL && iterB.next == NULL) || (iterA.next == NULL && iterB.next != NULL) )
        return FALSE;

    return TRUE;
}

int main(){

    // Create and initialize listA
    list *listA = malloc( sizeof(*listA) );
    listA->value = 0;
    listA->next = NULL;

    for (int i = 1; i < 100; i++) {
        listA = addElement(i, listA);
    }

    print(listA);

    // Create and initialize listB
    list *listB = malloc( sizeof(*listB) );
    listB->value = 0;
    listB->next = NULL;

    for (int i = 1; i < 100; i++) {
        listB = addElement(i, listB);
    }

    print(listB);

    printf("Equal? %s\n\n", isEqual(listA, listB)==TRUE? "YES" : "NO");

    printf("listA[%d]: %d", 1, getKthValue(1, listA));
    printf("\nlistB[%d]: %d\n\n", 100, getKthValue(100, listB));

    liberate(listA);
    liberate(listB);

    return 0;
}
