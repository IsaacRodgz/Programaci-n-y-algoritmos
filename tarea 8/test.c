#include<stdlib.h>
#include<stdio.h>
#include "graph.h"

void test_graph(const char* file_name){

    Graph* G = read_graph(file_name);

    printf("\nGraph read:\n\n");
    print_graph(G);
    printf("\n");

    // Find strongly connected components

    char* strly_conn_comp_groups = strly_conn_compnts(*G);

    // Calculate number of strongly connected components found

    int max = 0;

    for (int i = 0; i < G->num_vertex; i++)
        if ( strly_conn_comp_groups[i] > max )
            max = strly_conn_comp_groups[i];

    // print vertices per strongly connected component

    printf("-----------------------------------------");
    printf("\nThere are %d strongly connected components\n", max);
    printf("-----------------------------------------\n");

    for (int i = 1; i <= max; i++) {

        printf("\nVertices of strongly connected components %d:\n\n", i);

        for (int j = 0; j < G->num_vertex; j++) {

            if ( strly_conn_comp_groups[j] == i ) {

                printf("%d ", j);
            }
        }

        printf("\n");
    }

    printf("\n");

}

int main(int argc, char const *argv[]) {

    if ( argc == 1 )
        printf("Error: Missing parameter: file_name\n");

    else
        test_graph(argv[1]);

    return 0;
}
