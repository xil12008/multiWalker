#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>       /* pow */
#include <map>
#include <set>
#include "graph.h"

using namespace std;

int V = 15; // the maximum number of nodes of the network

void initGraph(Graph* graph)
{
    int id;
    for (int i = 0; i < V; ++i)
    {
       id = newNode(graph); // node to be added, it increases the graph->cap by one
       addEdge(graph, id, rand() % (graph->cap)); // add a random edge 
    }
}

// Driver program to test above functions
int main(int argc, char *argv[])
{
    srand(time(NULL));

    // we create a graph (memory allocation)
    struct Graph* graph = createGraph(V);
    // initialize the graph by adding edges
    initGraph(graph);
    // print the graph
    printGraph(graph);
    // remove all the out-going edges of a node 
    for (int i = 0; i < graph->cap; ++i)
       removeAllEdges(graph, i);
    // release the memory allocated to the graph
    deleteGraph(graph);
    return 0;
}
