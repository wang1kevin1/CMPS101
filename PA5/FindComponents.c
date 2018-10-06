/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_5
 *
 * FindComponents.c
 */

/*
 * This program takes two command line arguments giving the names of an input
 * file and an output file. The input contains the Graph and Path information.
 * FindPath.java reads the input file, initializes and builds the array of 
 * adjacency List representation of Graph G, then finds the Strongly Connected
 * Components of Graph G and prints them in topologically sorted order to 'out'.
 * 
 * @author Kevin Wang
 * @since 6.5.2018
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 1000

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    FILE *in;
    FILE *out;
    
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    char line[MAX_LEN];
    char* tokens;

    fgets(line, MAX_LEN, in);
    tokens = strtok(line, " \n");
    
    int n = atoi(&tokens[0]); // get order
    Graph G = newGraph(n); // Initialize Graph
    
    int u;
    int v;
    
    while (fgets(line, MAX_LEN, in) != NULL) { // scan through input file lines
        tokens = strtok(line, " \n");
        u = atoi(tokens);
        tokens = strtok(NULL, "\n");
        v = atoi(tokens);
        
        if((u == 0) && (v == 0)) { // if reached "0 0" delimiter, terminate
            break;
        } else {
            addArc(G, u, v);
        }
    }
    
    // Print Adjacency List representation of Graph G to file 'out'
    fprintf(out,"Adjacency list representation of G: \n");
    printGraph(out, G);
    fprintf(out, "\n");
    
    // Initialize queue
    List Q = newList();
    for(int i = 1; i < getOrder(G) + 1; i++) {
        append(Q, i);
    }
    
    DFS(G, Q); // DFS on G
    Graph T = transpose(G);
    DFS(T, Q); // DFS on T, processed by decreasing finish times from DFS on G
    
    // Initialize SCC count
    int SCC = 0;
    for(int i = 1; i < getOrder(G) + 1; i++) {
        if(getParent(T,i) == NIL) { // if vertex i is a DFS tree root
            SCC++; // each tree root is the start of a DFS forest component
        }
    }
    
    // Print number of SCC's of Graph G to file 'out'
    fprintf(out, "G contains %d strongly connected components:\n", SCC);
    
    // Initialize stack
    List S = newList();
    
    int component = 1; // initialize component counter
    
    moveBack(Q);
    while((index(Q) != -1) && (component < SCC + 1)) { // while still components
        int x = get(Q);
        
        // Print components of Graph G to file 'out'
        fprintf(out, "Component %d: ", component);
        
        // While vertex is not a DFS tree root
        while((index(Q) != -1) && (getParent(T, x) != NIL)){ 
            prepend(S, x); // add to component List
            
            movePrev(Q);
            if(index(Q) != -1) { // if not a leaf node
                x = get(Q);
            }
        }
        
        // If vertex is a DFS tree root
        if(index(Q) != -1 && (getParent(T, x) == NIL)) { 
            prepend(S, x); // add to component List
            
            movePrev(Q);
        }
        
        // Print List of vertices of a component in topologically sorted order
        printList(out, S);
        fprintf(out,"\n");
        
        clear(S); // reset stack
        component++; // next component
    }
    
    // Free memory
    freeGraph(&G);
    freeGraph(&T);
    freeList(&Q);
    freeList(&S);
    
    // Close FILE streams
    fclose(in);
    fclose(out);
    
    return(0);
}

