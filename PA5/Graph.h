/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_5
 *
 * Graph.h
 */

/*
 * Header file for Graph.c
 *
 * @author Kevin Wang
 * @since 6.5.2018
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

#define UNDEF -1
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

// Returns the parent of vertex u in the Depth-First tree created by DFS(), 
// or returns NIL if DFS() has not yet been called.
// Pre: 0 < u < getOrder(G) + 1
int getParent(Graph G, int u);

// Returns the time vertex u is discovered by DFS(), or returns UNDEF if DFS()
// has not yet been called.
// Pre: 0 < u < getOrder(G) + 1
int getDiscover(Graph G, int u);

// Returns the time vertex u is finished by DFS(), or returns UNDEF if DFS()
// has not yet been called.
// Pre: 0 < u < getOrder(G) + 1
int getFinish(Graph G, int u);

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

// Runs the Depth-First Search algorithm on the Graph G. Sets the color, 
// parent, discover time and finish time fields of G accordingly. List S 
// contains some permutation of the integers {1, 2, ..., n}, where 
// n = getOrder(G)), and defines the order in which the vertices of Graph G 
// will be processed. When DFS is complete, S will store the vertices in 
// order of decreasing finish times.
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List s);

/***************************** Other Procedures ******************************/

// Returns a new Graph representing the transpose of Graph G (where all the 
// directed edges are reversed in direction). The new Graph does not 
// maintain the DFS attributes as Graph G, i.e. DFS() has not been run. 
// This Graph is unchanged.
Graph transpose(Graph G);

// Returns a new Graph representing the isomorphic copy of Graph G. The new 
// Graph does not maintain the DFS attributes as Graph G, i.e. DFS() has not 
// been run. This Graph is unchanged.
Graph copyGraph(Graph G);

// Prints the adjacency list of G to the file pointed to by 'out', formatted as 
// a string label followed by a space-separated string.
void printGraph(FILE* out, Graph G);

#endif /* GRAPH_H */

