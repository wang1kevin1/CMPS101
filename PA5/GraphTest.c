/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_5
 *
 * GraphTest.c
 */

/*
 * Test file for Graph ADT based off of 'ModelGraphTest.c' taken from:
 * www.github.com/legendddhgf/
 *         cmps101-pt.s18.grading/blob/master/pa5/ModelGraphTest.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char** argv) {
    // Initialize test objects
    Graph A = newGraph(100);
    List L = newList();

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
        printf("Failed: DG_getSize2 on DirectedGraph (pre-DFS) \n");
    }
    for (int i = 1; i <= 100; i++) {
        append(L, i);
    }
    DFS(A, L);
    if (getSize(A) != 5) {
        printf("Failed: DG_getSize3 on DirectedGraph (post-DFS) \n");
    }
    addArc(A, 55, 1);
    if (getSize(A) != 6) {
        printf("Failed: DG_getSize4 on DirectedGraph addArc()(post-DFS) \n");
    }

    makeNull(A);
    clear(L);

    // DG_getParent:
    printf("Testing DG_getParent... \n");
    for (int i = 1; i <= 100; i++) {
        if (getParent(A, i) != NIL) {
            printf("Failed: DG_getParent1 on NullGraph \n");
        }
    }
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
        append(L, i);
    }
    DFS(A, L);
    if (getParent(A, 100) != NIL) {
        printf("Failed: DG_getParent2 on DirectedGraph no edge (post-DFS) \n");
    }
    if (getParent(A, 2) != NIL) {
        printf("Failed: DG_getParent3 on DirectedGraph root (post-DFS) \n");
    }
    if (getParent(A, 42) != 3) {
        printf("Failed: DG_getParent4 on DirectedGraph (post-DFS) \n");
    }
    if (getParent(A, 3) != 64) {
        printf("Failed: DG_getParent5 on DirectedGraph (post-DFS) \n");
    }
    if (getParent(A, 4) != 64) {
        printf("Failed: DG_getParent6 on DirectedGraph (post-DFS) \n");
    }

    makeNull(A);
    clear(L);

    // DG_getDiscover:
    printf("Testing DG_getDiscover... \n");
    for (int i = 1; i <= 100; i++) {
        if (getDiscover(A, i) != UNDEF) {
            printf("Failed: DG_getDiscover1 on NullGraph \n");
        }
    }
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
        prepend(L, i);
    }
    DFS(A, L);
    if (getDiscover(A, 100) != 1) {
        printf("Failed: DG_getParent2 on DirectedGraph first (post-DFS) \n");
    }
    if (getDiscover(A, 64) != 73) {
        printf("Failed: DG_getParent3 on DirectedGraph root (post-DFS) \n");
    }
    if (getDiscover(A, 4) != 80) {
        printf("Failed: DG_getParent4 on DirectedGraph (post-DFS) \n");
    }
    DFS(A, L);
    if (getDiscover(A, 4) != 126) {
        printf("Failed: DG_getParent5 on DirectedGraph new L (post-DFS) \n");
    }
    if (getDiscover(A, 63) != 117) {
        printf("Failed: DG_getParent6 on DirectedGraph no edge (post-DFS) \n");
    }
    DFS(A, L);
    if (getDiscover(A, 65) != 71) {
        printf("Failed: DG_getParent7 on DirectedGraph no edge (post-DFS) \n");
    }
    if (getDiscover(A, 1) != 199) {
        printf("Failed: DG_getParent8 on DirectedGraph last (post-DFS) \n");
    }

    makeNull(A);
    clear(L);

    // DG_getFinish:
    printf("Testing DG_getFinish... \n");
    for (int i = 1; i <= 100; i++) {
        if (getFinish(A, i) != UNDEF) {
            printf("Failed: DG_getFinish1 on NullGraph \n");
        }
    }
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
        prepend(L, i);
    }
    DFS(A, L);
    if (getFinish(A, 100) != 2) {
        printf("Failed: DG_getFinish2 on DirectedGraph first (post-DFS) \n");
    }
    if (getFinish(A, 64) != 82) {
        printf("Failed: DG_getFinish3 on DirectedGraph root (post-DFS) \n");
    }
    if (getFinish(A, 42) != 78) {
        printf("Failed: DG_getFinish4 on DirectedGraph (post-DFS) \n");
    }
    DFS(A, L);
    if (getFinish(A, 64) != 128) {
        printf("Failed: DG_getFinish5 on DirectedGraph new L (post-DFS) \n");
    }
    if (getFinish(A, 63) != 118) {
        printf("Failed: DG_getFinish6 on DirectedGraph no edge (post-DFS) \n");
    }
    DFS(A, L);
    if (getFinish(A, 65) != 72) {
        printf("Failed: DG_getFinish7 on DirectedGraph no edge (post-DFS) \n");
    }
    if (getFinish(A, 1) != 200) {
        printf("Failed: DG_getFinish8 on DirectedGraph last (post-DFS) \n");
    }

    makeNull(A);
    clear(L);
    
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
        printf("Failed: DG_getSize2 on DirectedGraph (pre-DFS) \n");
    }
    for (int i = 1; i <= 100; i++) {
        append(L, i);
    }
    DFS(A, L);
    if (getSize(A) != 5) {
        printf("Failed: DG_getSize3 on DirectedGraph (post-DFS) \n");
    }
    addArc(A, 55, 1);
    if (getSize(A) != 6) {
        printf("Failed: DG_getSize4 on DirectedGraph addArc()(post-DFS) \n");
    }

    makeNull(A);
    clear(L);

    // UG_getSize:
    printf("Testing UG_getSize... \n");
    if (getSize(A) != 0) {
        printf("Failed: UG_getSize1 on NullGraph \n");
    }
    addEdge(A, 54, 1);
    addEdge(A, 54, 2);
    addEdge(A, 54, 3);
    addEdge(A, 1, 55);
    if (getSize(A) != 4) {
        printf("Failed: UG_getSize2 on UndirectedGraph (pre-DFS) \n");
    }
    for (int i = 1; i <= 100; i++) {
        append(L, i);
    }
    DFS(A, L);
    if (getSize(A) != 4) {
        printf("Failed: UG_getSize3 on UndirectedGraph (post-DFS) \n");
    }
    addEdge(A, 1, 56);
    if (getSize(A) != 5) {
        printf("Failed: UG_getSize4 on UndirectedGraph addEdge()(post-DFS) \n");
    }

    makeNull(A);
    clear(L);

    // UG_getParent:
    printf("Testing UG_getParent... \n");
    for (int i = 1; i <= 100; i++) {
        if (getParent(A, i) != NIL) {
            printf("Failed: UG_getParent1 on NullGraph \n");
        }
    }
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
        append(L, i);
    }
    DFS(A, L);
    if (getParent(A, 100) != NIL) {
        printf("Failed: UG_getParent2 on UndirectedGraph no edge (post-DFS) \n");
    }
    if (getParent(A, 2) != NIL) {
        printf("Failed: UG_getParent3 on UndirectedGraph root (post-DFS) \n");
    }
    if (getParent(A, 42) != 3) {
        printf("Failed: UG_getParent4 on UndirectedGraph (post-DFS) \n");
    }
    if (getParent(A, 3) != 64) {
        printf("Failed: UG_getParent5 on UndirectedGraph (post-DFS) \n");
    }
    if (getParent(A, 4) != 2) {
        printf("Failed: UG_getParent6 on UndirectedGraph (post-DFS) \n");
    }
    
    makeNull(A);
    clear(L);
    
    // UG_getDiscover:
    printf("Testing UG_getDiscover... \n");
    for (int i = 1; i <= 100; i++) {
        if (getDiscover(A, i) != UNDEF) {
            printf("Failed: UG_getDiscover1 on NullGraph \n");
        }
    }
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
        prepend(L, i);
    }
    DFS(A, L);
    if (getDiscover(A, 100) != 1) {
        printf("Failed: UG_getParent2 on UndirectedGraph first (post-DFS) \n");
    }
    if (getDiscover(A, 64) != 73) {
        printf("Failed: UG_getParent3 on UndirectedGraph root (post-DFS) \n");
    }
    if (getDiscover(A, 4) != 75) {
        printf("Failed: UG_getParent4 on UndirectedGraph (post-DFS) \n");
    }
    DFS(A, L);
    if (getDiscover(A, 4) != 121) {
        printf("Failed: UG_getParent5 on UndirectedGraph new L (post-DFS) \n");
    }
    if (getDiscover(A, 63) != 117) {
        printf("Failed: UG_getParent6 on UndirectedGraph no edge (post-DFS) \n");
    }
    DFS(A, L);
    if (getDiscover(A, 65) != 71) {
        printf("Failed: UG_getParent7 on UndirectedGraph no edge (post-DFS) \n");
    }
    if (getDiscover(A, 1) != 199) {
        printf("Failed: UG_getParent8 on UndirectedGraph last (post-DFS) \n");
    }

    makeNull(A);
    clear(L);
    
    // UG_getFinish:
    printf("Testing UG_getFinish... \n");
    for (int i = 1; i <= 100; i++) {
        if (getFinish(A, i) != UNDEF) {
            printf("Failed: UG_getFinish1 on NullGraph \n");
        }
    }
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
        prepend(L, i);
    }
    DFS(A, L);
    if (getFinish(A, 100) != 2) {
        printf("Failed: UG_getFinish2 on UndirectedGraph first (post-DFS) \n");
    }
    if (getFinish(A, 64) != 82) {
        printf("Failed: UG_getFinish3 on UndirectedGraph root (post-DFS) \n");
    }
    if (getFinish(A, 42) != 80) {
        printf("Failed: UG_getFinish4 on UndirectedGraph (post-DFS) \n");
    }
    DFS(A, L);
    if (getFinish(A, 64) != 128) {
        printf("Failed: UG_getFinish5 on UndirectedGraph new L (post-DFS) \n");
    }
    if (getFinish(A, 63) != 118) {
        printf("Failed: UG_getFinish6 on UndirectedGraph no edge (post-DFS) \n");
    }
    DFS(A, L);
    if (getFinish(A, 65) != 72) {
        printf("Failed: UG_getFinish7 on UndirectedGraph no edge (post-DFS) \n");
    }
    if (getFinish(A, 1) != 200) {
        printf("Failed: UG_getFinish8 on UndirectedGraph last (post-DFS) \n");
    }

    // Free test objects
    freeGraph(&A);
    freeList(&L);
    
    return(0);
}
