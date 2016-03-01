// graph.h
#ifndef _GRAPH_H // must be unique name in the project
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>       /* pow */
#include <map>
#include <queue>
#include <algorithm>    // std::random_shuffle
#include <limits.h>

/*
Define your own marker for the nodes
*/
#define DEFAULT_MARKER -2 


using namespace std;

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};

// for random walk
#define V_m 100 // at most V_m metapathes
struct Property
{
    double r[V_m];
    double r_hold[V_m]; 
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    int cap;
    int* degree;
    int* marker;
    int* parent;
    struct AdjList* array;
    struct Property* property; 
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest);

// A utility function that creates a graph of V vertices (memory allocation)
struct Graph* createGraph(int V);
void deleteGraph(Graph* graph);

void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
void printNode(struct Graph* graph, int v);
int newNode(Graph* graph);
bool isConnected(Graph* graph, int a, int b);
int findNode(Graph* graph, int deg, int forbid);
void removeEdge(Graph* graph, int src, int dst);
void removeAllEdges(Graph* graph, int v);
int randomNeighbor(Graph* graph, int id);

int networkSize(Graph *graph, int k);
void resetMarkers(Graph * graph);
int randomNode(Graph* graph, int k);

#endif
