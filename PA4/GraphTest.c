/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_4
 *
 * GraphTest.c
 */

/*
 * Test file for Graph ADT based off of 'ModelGraphTest.c' taken from:
 * www.github.com/legendddhgf/
 *         cmps101-pt.s18.grading/blob/master/pa4/ModelGraphTest.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// Resets test objects

void reset(Graph A, List L, List C) {
    makeNull(A);
    clear(L);
    clear(C);
}

int main(int argc, char** argv) {
    // Initialize test objects
    Graph A = newGraph(100);
    List L = newList();
    List C = newList();

    // DG_getSize()
    printf("Testing DG_getSize... \n");
    if (getSize(A) != 0) {
        printf("Failed: DG_getSize1 on NullGraph \n");
    }
    addArc(A, 54, 1);
    addArc(A, 54, 2);
    addArc(A, 54, 3);
    addArc(A, 1, 54);
    addArc(A, 1, 55);
    if (getSize(A) != 5) {
        printf("Failed: DG_getSize2 after addArc() pre-BFS() \n");
    }
    BFS(A, 67);
    if (getSize(A) != 5) {
        printf("Failed: DG_getSize3 after BFS() \n");
    }
    addArc(A, 55, 1);
    if (getSize(A) != 6) {
        printf("Failed: DG_getSize4 after addArc() post-BFS() \n");
    }

    reset(A, L, C);

    // DG_getSource()
    printf("Testing DG_getSource... \n");
    if (getSource(A) != NIL) {
        printf("Failed: DG_getSource1 on undefined source \n");
    }
    BFS(A, 42);
    if (getSource(A) != 42) {
        printf("Failed: DG_getSource2 after BFS() call \n");
    }
    BFS(A, 88);
    if (getSource(A) != 88) {
        printf("Failed: DG_getSource3 after new BFS() call \n");
    }

    reset(A, L, C);

    // DG_getParent()
    printf("Testing DG_getParent... \n");
    for (int i = 1; i <= 100; i++)
        if (getParent(A, i) != NIL) {
            printf("Failed: DG_getParent1 before BFS() \n");
        }
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 42);
    if (getParent(A, 42) != NIL) {
        printf("Failed: DG_getParent2 on source after BFS() \n");
    }
    if (getParent(A, 2) != 42) {
        printf("Failed: DG_getParent3 on source descendant after BFS() \n");
    }
    if (getParent(A, 8) != NIL) {
        printf("Failed: DG_getParent4 on disconnected vertex after BFS() \n");
    }

    reset(A, L, C);

    // DG_getDist()
    printf("Testing DG_getDist... \n");
    for (int i = 1; i <= 100; i++)
        if (getDist(A, i) != INF) {
            printf("Failed: DG_getDist1 before BFS() \n");
        }
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 64);
    if (getDist(A, 64) != 0) {
        printf("Failed: DG_getDist2 on source after BFS() \n");
    }
    if (getDist(A, 2) != 2) {
        printf("Failed: DG_getDist3 on source descendant after BFS() \n");
    }
    BFS(A, 4);
    if (getDist(A, 42) != 4) {
        printf("Failed: DG_getDist4 on source descendant after new BFS() \n");
    }
    if (getDist(A, 43) != INF) {
        printf("Failed: DG_getDist5 on disconnected vertex after BFS() \n");
    }
    BFS(A, 99);
    if (getDist(A, 64) != INF) {
        printf("Failed: DG_getDist6 on disconnected vertex after new BFS() \n");
    }

    reset(A, L, C);

    // DG_getPath()
    printf("Testing DG_getPath... \n");
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 3);
    getPath(L, A, 64);
    append(C, 3);
    append(C, 42);
    append(C, 2);
    append(C, 64);
    if (!equals(L, C)) {
        printf("Failed: DG_getPath1 on source descendant \n");
    }
    moveFront(L);
    BFS(A, 2);
    getPath(L, A, 2);
    append(C, 2);
    if (!equals(L, C)) {
        printf("Failed: DG_getPath2 on source \n");
    }
    getPath(L, A, 99);
    if (equals(L, C)) {
        printf("Failed: DG_getPath3 on disconnected vertex \n");
    }
    clear(L);
    clear(C);
    append(C, NIL);
    BFS(A, 99);
    getPath(L, A, 2);
    if (!equals(C, L)) {
        printf("Failed: DG_getPath4 on disconnected vertex \n");
    }

    reset(A, L, C);

    // UG_getSize()
    printf("Testing UG_getSize... \n");
    if (getSize(A) != 0) {
        printf("Failed: UG_getSize1 on NullGraph \n");
    }
    addEdge(A, 54, 1);
    addEdge(A, 54, 2);
    addEdge(A, 54, 3);
    addEdge(A, 1, 55);
    if (getSize(A) != 4) {
        printf("Failed: UG_getSize2 after addEdge() pre-BFS() \n");
    }
    BFS(A, 67);
    if (getSize(A) != 4) {
        printf("Failed: UG_getSize3 after BFS() \n");
    }
    addEdge(A, 55, 2);
    if (getSize(A) != 5) {
        printf("Failed: UG_getSize4 after addEdge() post-BFS() \n");
    }

    reset(A, L, C);

    // UG_getSource()
    printf("Testing UG_getSource... \n");
    if (getSource(A) != NIL) {
        printf("Failed: UG_getSource1 on undefined source \n");
    }
    BFS(A, 42);
    if (getSource(A) != 42) {
        printf("Failed: UG_getSource2 after BFS() call \n");
    }
    BFS(A, 88);
    if (getSource(A) != 88) {
        printf("Failed: UG_getSource3 after new BFS() call \n");
    }

    reset(A, L, C);

    // UG_getParent()
    printf("Testing UG_getParent... \n");
    for (int i = 1; i <= 100; i++)
        if (getParent(A, i) != NIL) {
            printf("Failed: UG_getParent1 before BFS() \n");
        }
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    BFS(A, 42);
    if (getParent(A, 42) != NIL) {
        printf("Failed: UG_getParent2 on source after BFS() \n");
    }
    if (getParent(A, 64) != 2) {
        printf("Failed: UG_getParent3 on source descendant after BFS() \n");
    }
    if (getParent(A, 3) != 42) {
        printf("Failed: UG_getParent4 on source descendant after BFS() \n");
    }
    if (getParent(A, 8) != NIL) {
        printf("Failed: UG_getParent5 on disconnected vertex after BFS() \n");
    }

    reset(A, L, C);

    // UG_getDist()
    printf("Testing UG_getDist... \n");
    for (int i = 1; i <= 100; i++)
        if (getDist(A, i) != INF) {
            printf("Failed: UG_getDist1 before BFS() \n");
        }
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    BFS(A, 64);
    if (getDist(A, 64) != 0) {
        printf("Failed: UG_getDist2 on source after BFS() \n");
    }
    if (getDist(A, 2) != 1) {
        printf("Failed: UG_getDist3 on source descendant after BFS() \n");
    }
    BFS(A, 4);
    if (getDist(A, 42) != 2) {
        printf("Failed: UG_getDist4 on source descendant after new BFS() \n");
    }
    if (getDist(A, 43) != INF) {
        printf("Failed: UG_getDist5 on disconnected vertex after BFS() \n");
    }
    BFS(A, 99);
    if (getDist(A, 64) != INF) {
        printf("Failed: UG_getDist6 on disconnected vertex after new BFS() \n");
    }

    reset(A, L, C);

    // UG_getPath()
    printf("Testing UG_getPath... \n");
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    BFS(A, 3);
    getPath(L, A, 64);
    append(C, 3);
    append(C, 64);
    if (!equals(L, C)) {
        printf("Failed: UG_getPath1 on source descendant \n");
    }
    moveFront(L);
    BFS(A, 2);
    getPath(L, A, 2);
    append(C, 2);
    if (!equals(L, C)) {
        printf("Failed: UG_getPath2 on source \n");
    }
    getPath(L, A, 99);
    if (equals(L, C)) {
        printf("Failed: UG_getPath3 on disconnected vertex \n");
    }
    clear(L);
    clear(C);
    append(C, NIL);
    BFS(A, 99);
    getPath(L, A, 2);
    if (!equals(C, L)) {
        printf("Failed: UG_getPath4 on disconnected vertex \n");
    }

    // Free test objects
    freeGraph(&A);
    freeList(&L);
    freeList(&C);
    return (EXIT_SUCCESS);
}


