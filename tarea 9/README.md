# Tarea 8

* Program that finds strongly connected components of a directed graph.
* Reads file of directed graph where first contains number of vertices and number of edges
 respectively, separated by space. The next lines define the edges of the graph, one edge per line.
 If there is an edge from vertex a to b, the line will have elements "a b".
 * Vertices are identified from 0 to n-1, where n is the total number of vertices of the graph.

## Ejecución

* make
* ./runTest graph.txt
* make clean

## Output

* Array strly_conn_comp_index of size n-1 where the index represents the vertex number.
* For vertex i, strly_conn_comp_index[i] indicates the strongly connected component it belongs to.
* Strongly connected components are tagged from 1 to k, where k is the total number of strongly
connected components of the graph.

## Example

> make && ./runTest graph.txt

> strly_conn_comp_index = { 3, 3, 3, 4, 4, 4, 1, 1, 1, 1, 2 }

* Vertices 0 to 2 belong to strongly connected component "3"
* Vertices 3 to 5 belong to strongly connected component "4"
* Vertices 6 to 9 belong to strongly connected component "1"
* Vertex 10 belongs to strongly connected component "2"

## Compilado con

* gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
