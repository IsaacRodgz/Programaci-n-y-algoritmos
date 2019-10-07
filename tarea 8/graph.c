#include<stdio.h>
#include<stdlib.h>
#include "graph.h"

Graph* read_graph(const char* file_name){

    FILE* fp;

    if ( ( fp = fopen(file_name, "r") ) == NULL ) {

        fprintf(stderr, "\n[Error]: while trying to open file %s\n\n", file_name);
        exit(-1);
    }

    int num_vertex;
    int num_edges;

    // first line: num_vertex num_edges
    fscanf(fp, "%d", &num_vertex);
    fscanf(fp, "%d", &num_edges);

    // Create adjacency matrix

    int** matrix = malloc(num_vertex * sizeof *matrix);
    matrix[0] = calloc(num_vertex*num_vertex, sizeof **matrix);

    for (int i = 1; i < num_vertex; i++) {
        matrix[i] = matrix[i-1] + num_vertex;
    }

    // Fill adjacency matrix

    int node1, node2;

    for (int i = 0; i < num_edges; i++) {

        fscanf(fp, "%d %d", &node1, &node2);

        matrix[node1][node2] = 1;
    }

    Graph* G = malloc(sizeof *G);
    G->adj_matrix = matrix;
    G->num_vertex = num_vertex;
    G->num_edges = num_edges;

    return G;
}

void print_graph(Graph* G){

    for (int i = 0; i < G->num_vertex; i++) {

        for (int j = 0; j < G->num_vertex; j++) {

            if (G->adj_matrix[i][j] == 1) {
                printf("%d -> %d\n", i, j);
            }
        }
    }
}

void dfs_traverse(Graph G, int init_node, int* visited, Stack* traverse_stack){

    visited[init_node] = 1;

    for (int i = 0; i < G.num_vertex; i++) {

        if ( !visited[i] && G.adj_matrix[init_node][i] == 1 ) {

            dfs_traverse(G, i, visited, traverse_stack);
        }
    }

    traverse_stack->data[++traverse_stack->top] = init_node;
}

char* strly_conn_compnts(Graph G){

    int num_vertex = G.num_vertex;

    // Array to identify the strongly connected component of each vertex
    char* strly_conn_comp_index = malloc(num_vertex * sizeof *strly_conn_comp_index);

    for (int i = 0; i < num_vertex; i++)
        strly_conn_comp_index[i] = -1;

    // Build transpose of graph G

    int** m = malloc(num_vertex * sizeof *m);
    m[0] = calloc(num_vertex*num_vertex, sizeof **m);

    for (int i = 1; i < num_vertex; i++) {
        m[i] = m[i-1] + num_vertex;
    }

    for (int i = 0; i < num_vertex; i++) {

        for (int j = 0; j < num_vertex; j++) {

            if ( G.adj_matrix[i][j] == 1 ) {

                m[j][i] = 1;
            }
        }
    }

    Graph G_t;
    G_t.adj_matrix = m;
    G_t.num_vertex = num_vertex;
    G_t.num_edges = G.num_edges;

    // Stack with traversal of all vertices of G

    Stack* stack = malloc(sizeof *stack);
    stack->data = calloc(num_vertex, sizeof(int));
    stack->top = -1;

    // Array to keep track of visited nodes

    int visited[num_vertex];

    for (int i = 0; i < num_vertex; i++)
        visited[i] = 0;

    // Start dfs until all nodes are visited

    for (int i = 0; i < num_vertex; i++) {

        if ( visited[i] == 0 ) {

            dfs_traverse(G, i, visited, stack);
        }
    }

    // reset visited elements

    for (int i = 0; i < num_vertex; i++)
        visited[i] = 0;

    // pop elements of stack and count strongly connected components

    int strly_conn_comp_count = 0;

    int current;

    // Stack for strongly connected component elements

    Stack* stack_t = malloc(sizeof *stack_t);
    stack_t->data = calloc(num_vertex, sizeof(int));
    stack_t->top = -1;

    // pop nodes from stack until empty

    while (stack->top >= 0) {

        // count new strongly connected component

        strly_conn_comp_count++;

        // pop node

        current = stack->data[stack->top--];

        // find elements of current strongly connected component

        dfs_traverse(G_t, current, visited, stack_t);

        // Assign traversed nodes to the same strongly connected component

        for (int i = 0; i <= stack_t->top; i++) {
            strly_conn_comp_index[ stack_t->data[i] ] = strly_conn_comp_count;
        }

        stack_t->top = -1;

        // If element in stack was already visited in dfs, pop

        while ( visited[ stack->data[stack->top] ] == 1 ) {
            stack->top--;
        }
    }

    return strly_conn_comp_index;
}
