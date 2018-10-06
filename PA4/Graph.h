/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_4
 *
 * Graph.h
 */

/*
 * Header file for Graph.c
 *
 * @author Kevin Wang
 * @since 5.26.2018
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

#define INF -1
#define NIL 0

typedef struct GraphObj* Graph;

/************************* Constructors-Destructors *************************/
 
// Returns a Graph pointing to a newly created GraphObj representing a 
// graph having n vertices and no edges.
Graph newGraph(int n);

// Frees all dynamic memory associated with the Graph *pG, 
// then sets pointer to NULL.
void freeGraph(Graph* pG); 

/***************************** Access Functions *****************************/

// Returns the order (number of vertices) of G. 
int getOrder(Graph G);

// Returns the size (number of edges) of G.
int getSize(Graph G);

// Returns the source vertex most recently used in function BFS(), 
// or returns NIL if BFS() has not yet been called.
int getSource(Graph G);

// Returns the parent of vertex u in the BreadthFirst tree created by BFS(), 
// or returns NIL if BFS() has not yet been called.
// Pre: 0 < u < getOrder(G) + 1
int getParent(Graph G, int u);

// Returns the distance from the most recent BFS source to vertex u, 
// or returns INF if BFS() has not yet been called. 
// Pre: 0 < u < getOrder(G) + 1
int getDist(Graph G, int u);

// Appends to the List L the vertices of a shortest path in G from source to u, 
// or appends to L the value NIL if no such path exists. BFS() must have been 
// called before getPath().
// Pre: 0 < u < getOrder(G) + 1, getSource(G)!=NIL
void getPath(List L, Graph G, int u);

/************************** Manipulation Procedures **************************/

// Deletes all edges of G, restoring it to its original (no edge) state. 
void makeNull(Graph G);

// Inserts a new edge joining u to v. v is added to the adjacency List of u, 
// and u is added to the adjacency List of v.
// Pre: 0 < u < getOrder(G) + 1, 0 < v < getOrder(G) + 1
void addEdge(Graph G, int u, int v);

// Inserts a new directed edge joining u to v. v is added to the 
// adjacency List of u. (u is NOT added to the adjacency List of v)
// Pre: 0 < u < getOrder(G) + 1, 0 < v < getOrder(G) + 1
void addArc(Graph G, int u, int v);

// Runs the BFS algorithm on the Graph G with source s. Sets the color, 
// distance, parent, and source fields of G accordingly.
// Pre: 0 < s < getOrder(G) + 1
void BFS(Graph G, int s);

/***************************** Other Procedures ******************************/
 
// Prints the adjacency list of G to the file pointed to by 'out', formatted as 
// a string label followed by a space-separated string.
void printGraph(FILE* out, Graph G);

#endif /* GRAPH_H */

