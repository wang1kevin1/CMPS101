/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_4
 *
 * FindPath.c
 */

/*
 * This program takes two command line arguments giving the names of an input
 * file and an output file. The input contains the Graph and Path information.
 * FindPath.java reads the input file, initializes and builds the array of 
 * adjacency List representation of Graph G, then runs Breadth-First Search on 
 * source vertex u to find and print a shortest path between source vertex u 
 * and vertex v from Path information. 
 * 
 * @author Kevin Wang
 * @since 5.26.2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 1000

int main(int argc, char * argv[]) {
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
        
        if(u == 0) { // if reached "0 0" delimiter, terminate
            break;
        } else {
            addEdge(G, u, v);
        }
    }
    
    printGraph(out, G); // print adjacency List representation of Graph to 'out'
    
    List L = newList(); // Initialize path List
    while (fgets(line, MAX_LEN, in) != NULL) { // scan through input file lines
        tokens = strtok(line, " \n");
        u = atoi(tokens);
        tokens = strtok(NULL, " \n");
        v = atoi(tokens);
        
        if(u == 0) { // if reached "0 0" delimiter, terminate
            break;
        } else {
            clear(L);
            
            BFS(G, u);
            getPath(L, G, v);
            
            fprintf(out, "\nThe distance from %d to %d is ", u, v);
            if(getDist(G, v) == INF){ // if no path exists
                fprintf(out, "infinity\n");
                fprintf(out, "No %d-%d path exists", u, v);
            } else { // if path exists
                fprintf(out, "%d\n", getDist(G, v));
                fprintf(out, "A shortest %d-%d path is: ", u, v);
                printList(out, L);
            }
            fprintf(out, "\n");
        }
    }
    // close File streams
    fclose(in);
    fclose(out);
    
    return(0);
}
