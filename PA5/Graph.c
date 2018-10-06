/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_5
 *
 * Graph.c
 */

/*
 * A graph representation in the form of a matrix of doubly linked adjacency 
 * lists. The user of this interface may create a graph by adding directed 
 * or undirected edges. Each graph element is also defined by its order (number
 * of vertices), n, and its size (number of edges). Note that identical edges 
 * (more than one edge (u,v)) are disregarded. The user can also choose to run 
 * Depth-First Search on the graph object.
 * 
 * Includes the List ADT (List.c) a bi-directional queue in the form of a 
 * doubly linked list.
 *
 * @author Kevin Wang
 * @since 6.5.2018
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

    // Define Graph DFS attributes
    char* color; // i^th element is the color (W, G, B) of vertex i
    int* parent; // i^th element is the parent of vertex i
    int* discover; // i^th element is the time of discovery for vertex i
    int* finish; // i^th element is the finish time for vertex i
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

    // Initialize Graph DFS attributes
    G->color = calloc(n + 1, sizeof (char));
    G->parent = calloc(n + 1, sizeof (int));
    G->discover = calloc(n + 1, sizeof (int));
    G->finish = calloc(n + 1, sizeof (int));

    for (int i = 1; i < n + 1; i++) {
        G->neighbors[i] = newList();
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return (G);
}

/* Graph Destructor */
void freeGraph(Graph *pG) {
    if (pG != NULL && *pG != NULL) {
        makeNull(*pG);
        for (int i = 1; i < getOrder(*pG) + 1; i++) {
            freeList(&(*pG)->neighbors[i]);
        }
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
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
        printf("Graph Error: Cannot call getOrder() on NULL Graph \n");
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
        printf("Graph Error: Cannot call getSize() on NULL Graph \n");
        exit(1);
    }
    if (G->size < 0) {
        printf("Graph Error: size of Graph cannot be less than 0 \n");
        exit(1);
    }
    return G->size;
}

/* 
 * Returns the parent of vertex u in the Depth-First tree created by DFS(), 
 * or returns NIL if DFS() has not yet been called.
 * Pre: 0 < u < getOrder(G) + 1
 */
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Cannot call getParent() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call getParent() on out-of-bounds u \n");
        exit(1);
    }
    return G->parent[u];
}

/* 
 * Returns the time vertex u is finished by DFS(), or returns UNDEF if DFS()
 * has not yet been called.
 * Pre: 0 < u < getOrder(G) + 1
 */
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Cannot call getDiscover() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call getDiscover() on out-of-bounds u \n");
        exit(1);
    }
    return G->discover[u];
}

/* 
 * Returns the time vertex u is discovered by DFS(), or returns UNDEF if DFS()
 * has not yet been called.
 * Pre: 0 < u < getOrder(G) + 1
 */
int getFinish(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Cannot call getFinish() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call getFinish() on out-of-bounds u \n");
        exit(1);
    }
    return G->finish[u];
}

/****************************************************************************
 ************************* MANIPULATION PROCEDURES **************************
 ****************************************************************************/

/* Deletes all edges of G, restoring it to its original (no edge) state. */
void makeNull(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Cannot call makeNull() on NULL Graph \n");
        exit(1);
    }
    for (int i = 1; i < getOrder(G) + 1; i++) {
        clear(G->neighbors[i]);
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    G->size = 0;
}

/* 
 * Adds vertex x to the adjacency List L. Private helper procedure 
 * for addEdge() and addArc().
 */
void addNeighbor(List L, int x) {
    if (L == NULL) {
        printf("Graph Error: Cannot call addNeighbor() on NULL List \n");
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
        printf("Graph Error: Cannot call addEdge() on NULL Graph \n");
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
        printf("Graph Error: Cannot call addArc() on NULL Graph \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call addArc() on out-of-bounds u \n");
        exit(1);
    }
    if ((v < 1) || (v > getOrder(G))) {
        printf("Graph Error: Cannot call addArc() on out-of-bounds v \n");
        exit(1);
    }

    addNeighbor(G->neighbors[u], v); // add v to the adjacency List of u

    G->size++;
}

/*
 * Recursive helper function for DFS(). 'Visits' the vertex as a part of
 * Depth-First Search and sets the color, parent, discover time and finish
 * time of each vertex of G accordingly.
 * Pre: 0 < u < getOrder(G) + 1, *time < 2 * getOrder(G) + 1
 */
void Visit(Graph G, List S, int u, int* time) {
    if (G == NULL) {
        printf("Graph Error: Cannot call Visit() on NULL Graph \n");
        exit(1);
    }
    if (S == NULL) {
        printf("Graph Error: Cannot call Visit() on NULL List \n");
        exit(1);
    }
    if ((u < 1) || (u > getOrder(G))) {
        printf("Graph Error: Cannot call Visit() on out-of-bounds u \n");
        exit(1);
    }
    if (*time > (2 * getOrder(G))) {
        printf("Graph Error: Cannot call Visit() on out-of-bounds timer \n");
        exit(1);
    }
    // Discover vertex u
    G->color[u] = 'G';
    (*time)++;
    G->discover[u] = *time;

    List L = G->neighbors[u];
    moveFront(L);

    while (index(L) != -1) {
        int v = get(L);
        if (G->color[v] == 'W') { // if adjacent vertex v is undiscovered          
            G->parent[v] = u; // v becomes the child of vertex u
            Visit(G, S, v, time);
        }
        moveNext(L);
    }
    // Finish vertex u
    G->color[u] = 'B';
    (*time)++;
    G->finish[u] = *time;

    prepend(S, u); // push vertex u to stack
}

/*
 * Runs the Depth-First Search algorithm on the Graph G. Sets the color, 
 * parent, discover time and finish time fields of G accordingly. List S 
 * contains some permutation of the integers {1, 2, ..., n}, where 
 * n = getOrder(G)), and defines the order in which the vertices of Graph G 
 * will be processed. When DFS is complete, S will store the vertices in 
 * order of decreasing finish times.
 * Pre: length(S) == getOrder(G)
 */
void DFS(Graph G, List S) {
    if (G == NULL) {
        printf("Graph Error: Cannot call DFS() on NULL Graph \n");
        exit(1);
    }
    if (S == NULL) {
        printf("Graph Error: Cannot call DFS() on NULL List \n");
        exit(1);
    }
    if (length(S) != getOrder(G)) {
        printf("Graph Error: Cannot call DFS() on incorrect List size \n");
        exit(1);
    }

    int time = 0; // initialize time counter

    for (int i = 1; i < getOrder(G) + 1; i++) { // reset DFS attributes
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    List Q = copyList(S); // initialize vector queue

    clear(S); // initialize vector stack

    while (length(Q) != 0) { // while still elements in queue
        int u = front(Q);

        if (G->color[u] == 'W') { // if vertex u is undiscovered
            Visit(G, S, u, &time);
        }

        deleteFront(Q); // dequeue u
    }
    freeList(&Q); // free vertex queue memory
}

/****************************************************************************
 ***************************** OTHER PROCEDURES *****************************
 ****************************************************************************/

/*
 * Returns a new Graph representing the transpose of Graph G (where all the 
 * directed edges are reversed in direction). The new Graph does not 
 * maintain the DFS attributes as Graph G, i.e. DFS() has not been run. 
 * This Graph is unchanged.
 */
Graph transpose(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Cannot call transpose() on NULL Graph \n");
        exit(1);
    }
    // Initialize new Graph (Transpose)
    Graph T = newGraph(getOrder(G));

    // Initialize Graph build attributes
    for (int i = 1; i < getOrder(G) + 1; i++) {
        List L = G->neighbors[i];

        if (length(L) > 0) {
            moveFront(L);
        }
        while (index(L) != -1) { // adds edges in reverse direction
            int v = get(L);
            addArc(T, v, i);
            moveNext(L);
        }
    }
    return T;
}

/*
 * Returns a new Graph representing the isomorphic copy of Graph G. 
 * The new Graph does not maintain the DFS attributes as Graph G,
 * i.e. DFS() has not been run. This Graph is unchanged.
 */
Graph copyGraph(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Cannot call copyGraph() on NULL Graph \n");
        exit(1);
    }
    // Initialize new Graph (Copy)
    Graph C = newGraph(getOrder(G));

    // Initialize Graph build attributes
    for (int i = 1; i < getOrder(C) + 1; i++) {
        C->neighbors[i] = copyList(G->neighbors[i]);
    }
    C->size = G->size;

    return C;
}

/* 
 * Prints the adjacency list of G to the file pointed to by 'out', formatted as
 * a string label followed by a space-separated string.
 */
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        printf("List Error: Cannot call printGraph() on NULL Graph \n");
        exit(1);
    }
    for (int i = 1; i < getOrder(G) + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbors[i]);
        fprintf(out, "\n");
    }
}