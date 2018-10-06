/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_4
 *
 * Graph.c
 */

/*
 * A graph representation in the form of a matrix of doubly linked adjacency 
 * lists. The user of this interface may create a graph by adding directed 
 * or undirected edges. Each graph element is also defined by its order (number
 * of vertices), n, and its size (number of edges). Note that identical edges 
 * (more than one edge (u,v)) are disregarded.
 * 
 * Includes the List ADT (List.c) a bi-directional queue in the form of a 
 * doubly linked list.  
 *
 * @author Kevin Wang
 * @since 5.26.2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

/****************************************************************************
 ******************************* STRUCTURES *********************************
 ****************************************************************************/

/* GraphObj Type */
typedef struct GraphObj {
    // Define Graph build attributes
    List* neighbors; // i^th element contains the neighbors of vertex i
    int order; // number of vertices
    int size; // number of edges
    
    // Define Graph BFS attributes
    int source; // label of the vertex most recently used as source for BFS
    char* color; // i^th element is the color (W, G, B) of vertex i
    int* parent; // i^th element is the parent of vertex i
    int* distance; // i^th element is the distance from (most recent) source 
                   // to vertex i.
} GraphObj;

/****************************************************************************
 *********************** CONSTRUCTORS & DESTRUCTORS *************************
 ****************************************************************************/

/* Graph Constructor.  */
Graph newGraph(int n) {
    // Initialize Graph
    Graph G;
    G = malloc(sizeof (GraphObj));
    // Initialize Graph build attributes
    G->neighbors = calloc(n + 1, sizeof (List));
    G->order = n;
    G->size = 0;
    
    // Initialize Graph BFS attributes
    G->source = NIL;
    G->color = calloc(n + 1, sizeof (char));
    G->parent = calloc(n + 1, sizeof (int));
    G->distance = calloc(n + 1, sizeof (int));
    
    for (int i = 1; i < n + 1; i++) {
        G->neighbors[i] = newList();
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return (G);
}

/* Graph Destructor */
void freeGraph(Graph *pG) {
    if (pG != NULL && *pG != NULL) {
        makeNull(*pG);
        for(int i = 1; i < getOrder(*pG) + 1; i++){
            freeList(&(*pG)->neighbors[i]);
	}
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/****************************************************************************
 **************************** ACCESS FUNCTIONS ******************************
 ****************************************************************************/

/* Returns the order (number of vertices) of G. */
int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph error: Cannot call getOrder() on NULL Graph \n");
        exit(1);
    }
    if (G->order < 1) {
        printf("Graph Error: order of Graph cannot be less than 1 \n");
        exit(1);
    }
    return G->order;
}

/* Returns the size (number of edges) of G. */
int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph error: Cannot call getSize() on NULL Graph \n");
        exit(1);
    }
    if (G->size < 0) {
        printf("Graph Error: size of Graph cannot be less than 0 \n");
        exit(1);
    }
    return G->size;
}

/* 
 * Returns the source vertex most recently used in function BFS(), 
 * or returns NIL if BFS() has not yet been called. 
 */
int getSource(Graph G) {
    if (G == NULL) {
        printf("Graph error: Cannot call getSource() on NULL Graph \n");
        exit(1);
    }
    if (G->source < NIL) {
        printf("Graph Error: source of Graph cannot be less than NIL \n");
        exit(1);
    }
    return G->source;
}

/* 
 * Returns the parent of vertex u in the BreadthFirst tree created by BFS(), 
 * or returns NIL if BFS() has not yet been called.
 * Pre: 0 < u < getOrder(G) + 1
 */
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: Cannot call getParent() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call getParent() on out-of-bounds u");
        exit(1);
    }
    if (getSource(G) == NIL) { // BFS has not been called
        return NIL;
    } 
    return G->parent[u];
}

/* 
 * Returns the distance from the most recent BFS source to vertex u, 
 * or returns INF if BFS() has not yet been called. 
 * Pre: 0 < u < getOrder(G) + 1
 */
int getDist(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: Cannot call getDist() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call getDist() on out-of-bounds u");
        exit(1);
    }
    if (getSource(G) == NIL) { // BFS has not been called
        return INF;
    }
    return G->distance[u];
}

/* 
 * Appends to the List L the vertices of a shortest path in G from source to u, 
 * or appends to L the value NIL if no such path exists. BFS() must have been 
 * called before getPath().
 * Pre: 0 < u < getOrder(G) + 1, getSource(G)!=NIL
 */
void getPath(List L, Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: Cannot call getPath() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call getPath() on out-of-bounds u");
        exit(1);
    }
    if (getSource(G) == NIL) {
        printf("Graph Error: Cannot call getPath() on undefined source");
        exit(1);
    }
    if (u == getSource(G)) { // if vertex u is source
        append(L, u);
    } else if (getParent(G, u) == NIL) { // if vertex u has no parent
        append(L, NIL);
        return;
    } else { // else recursively search ancestors
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

/****************************************************************************
 ************************* MANIPULATION PROCEDURES **************************
 ****************************************************************************/

/* Deletes all edges of G, restoring it to its original (no edge) state. */
void makeNull(Graph G) {
    if (G == NULL) {
        printf("Graph error: Cannot call makeNull() on NULL Graph \n");
        exit(1);
    }
    for (int i = 1; i < getOrder(G) + 1; i++) {
        clear(G->neighbors[i]);
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->size = 0;
    G->source = NIL;
}

/* 
 * Adds vertex x to the adjacency List L. Private helper procedure 
 * for addEdge() and addArc().
 */
void addNeighbor(List L, int x) {
    if (L == NULL) {
        printf("Graph error: Cannot call addNeighbor() on NULL List \n");
        exit(1);
    }
    moveFront(L);
    while (index(L) != -1) { // while still Nodes to check
        if (get(L) < x) { // traverse List
            moveNext(L);
        } else if (get(L) > x) { // if vertex is not in adjacency List
            insertBefore(L, x);
            return;
        } // if vertex is already in adjacency list, do nothing
    }
    append(L, x); // vertex is at back of List, or List is empty
}

/* 
 * Inserts a new edge joining u to v. v is added to the adjacency List of u, 
 * and u is added to the adjacency List of v.
 * Pre: 0 < u < getOrder(G) + 1, 0 < v < getOrder(G) + 1
 */
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph error: Cannot call addEdge() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call addEdge() on out-of-bounds u");
        exit(1);
    }
    if ((v < 1) || (v > getOrder(G))) {
        printf("Graph Error: Cannot call addEdge() on out-of-bounds v");
        exit(1);
    }
    if (u != v) {
        addNeighbor(G->neighbors[u], v); // add v to the adjacency List of u
        addNeighbor(G->neighbors[v], u); // add u to the adjacency List of v
        
        G->size++;
    }
}

/* 
 * Inserts a new directed edge joining u to v. v is added to the 
 * adjacency List of u. (u is NOT added to the adjacency List of v)
 * Pre: 0 < u < getOrder(G) + 1, 0 < v < getOrder(G) + 1
 */
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph error: Cannot call addArc() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call addArc() on out-of-bounds u");
        exit(1);
    }
    if ((v < 1) || (v > getOrder(G))) {
        printf("Graph Error: Cannot call addArc() on out-of-bounds v");
        exit(1);
    }
    if (u != v) {
        addNeighbor(G->neighbors[u], v); // add v to the adjacency List of u

        G->size++;
    }
}

/*
 * Runs the BFS algorithm on the graph G with source s. Sets the color, 
 * distance, parent, and source fields of G accordingly.
 * Pre: 0 < s < getOrder(G) + 1
 */
void BFS(Graph G, int s) {
    if (G == NULL) {
        printf("Graph error: Cannot call BFS() on NULL Graph \n");
        exit(1);
    }
    if ((s < 1) || (s > getOrder(G))) {
        printf("Graph Error: Cannot call BFS() on out-of-bounds source");
        exit(1);
    }
    G->source = s; // set source

    for (int i = 1; i < getOrder(G) + 1; i++) { // reset BFS attributes
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    // Discover source
    G->color[s] = 'G';
    G->parent[s] = NIL;
    G->distance[s] = 0;

    List Q = newList(); // initialize FIFO queue
    append(Q, s); // enqueue source

    while (length(Q) != 0) { // while still elements in queue
        int x = front(Q);
        deleteFront(Q); // dequeue x

        List L = G->neighbors[x];
        moveFront(L);
        
        while (index(L) != -1) {
            int y = get(L);
            if (G->color[y] == 'W') { // if adjacent vertex y is undiscovered
                G->color[y] = 'G';
                G->parent[y] = x;
                G->distance[y] = getDist(G, x) + 1;

                append(Q, y); // enqueue vertex y
            }
            moveNext(L);
        }
        G->color[x] = 'B'; // finish vertex x
    }
    freeList(&Q); // free FIFO queue memory
}

/****************************************************************************
 ***************************** OTHER PROCEDURES *****************************
 ****************************************************************************/

/* 
 * Prints the adjacency list of G to the file pointed to by 'out', formatted as
 * a string label followed by a space-separated string.
 */
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        printf("List error: Cannot call printGraph() on NULL Graph \n");
        exit(1);
    }
    for (int i = 1; i < getOrder(G) + 1; i++) {
        fprintf(out, "%d: ", i); 
        printList(out, G->neighbors[i]);
        fprintf(out, "\n");
    }
}