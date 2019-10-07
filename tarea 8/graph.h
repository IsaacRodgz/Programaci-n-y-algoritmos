#ifndef _graph_h
#define _graph_h
#include "graph.h"

typedef struct StructGraph{

    int** adj_matrix;
    int num_vertex;
    int num_edges;

} Graph;

typedef struct StructStack{

    int* data;
    int top;
    int size;

} Stack;

Graph* read_graph(const char* file_name);

void print_graph(Graph* G);

char* strly_conn_compnts(Graph G);

void dfs_traverse(Graph G, int init_node, int* visited ,Stack* traverse_stack);

#endif
