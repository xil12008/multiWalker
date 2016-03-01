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

int V = 5; // the maximum number of nodes of the network
int M = 8; // the maximum number of edges of the network
int L = 2; // the number of layers

Graph* metapath = NULL; // the metapath

// return the metapath y = metapath x + a node of type e
int mpHash(int x, int e)
{
    int y = -1; 
    if ( metapath == NULL ) 
    {
        metapath = createGraph(V_m);
        newNode(metapath);//for the root #0
    }
    struct AdjListNode* pCrawl = metapath->array[x].head;
    while (pCrawl)
    {
        int neighbor = pCrawl->dest;
        if (metapath->marker[neighbor] == e)
        {
            return neighbor;//hits the target 
        }
        pCrawl = pCrawl->next;
    }
    if ( metapath->cap >= metapath->V ) return -1; 
    //target type e from path x is not found
    y = newNode(metapath);
    metapath->marker[y] = e;
    addEdge(metapath, x, y);
    return y;
}

void printMetapath(int mp) 
{
    printf("type %d:\t", mp);
    while (metapath->parent[mp] != -1)
    {
        printf("%d->", metapath->marker[mp]);
        mp = metapath->parent[mp];	
    }
    printf("\n");
}

void printAllMetapath()
{
    for (int i = 0;i < V_m; ++i)
    {
        printMetapath(i);
    }
}

void initGraph(Graph* graph)
{
    int id;
    for (int i = 0; i < V; ++i)
    {
       id = newNode(graph); // node to be added, it increases the graph->cap by one
    }
    for (int i = 0; i < M; ++i)
    {
       addEdge(graph, rand() % (graph->cap), rand() % (graph->cap)); // add a random edge 
    }
    // for graph
    graph->property = (struct Property*) malloc(V * sizeof(struct Property));
    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V_m; ++j)
	{
            graph->property[i].r[j] = 0;
            graph->property[i].r_hold[j] = 0;
	}
	graph->marker[i] = rand() % L;
    }
}

void random_walk_helper(Graph* graph, int v)
{
    struct AdjListNode* pCrawl = graph->array[v].head;
    int count[L];
    for (int i = 0;i < L; ++i)   count[i] = 0;
    while ( pCrawl )
    {
        ++ count [ graph->marker[pCrawl->dest] ] ;
        pCrawl = pCrawl->next ;
    }
    int targetPath, sourcePath, targetType; 
    for ( int sourcePath = 0; sourcePath < V_m; ++sourcePath)
    {
        if (graph->property[v].r[sourcePath] < 0.01) continue; 
        struct AdjListNode* pCrawl = graph->array[v].head;
        while ( pCrawl )
        {
            targetType = graph->marker[pCrawl->dest];
            targetPath = mpHash(sourcePath, targetType); 
	    if (targetPath != -1)
	    {
                graph->property[pCrawl->dest].r_hold[targetPath]
	                 += 1.0 * graph->property[v].r[sourcePath] / count[ targetType ] ; 
	        printf("%d.r[%d]--%0.1f-->%d.r[%d]\n", v, sourcePath 
                         , 1.0 * graph->property[v].r[sourcePath] / count[ targetType ] 
	        	 , pCrawl->dest, targetPath); 
            }
            pCrawl = pCrawl->next;		 
        }
    }
}

void random_walk(Graph* graph, int start)
{
   graph->property[start].r[0] = 100000;
   printf("Random Walk Starts\n");

   for ( int step = 0; step < 5; ++step)
   {
       printf("Iteration %d\n", step);
       for ( int i = 0; i < V; ++i)
       {
           random_walk_helper(graph, i);
       }
       for ( int i = 0; i < V; ++i)
           for ( int j = 0;j < V_m; ++j)
           {
               graph->property[i].r[j] = graph->property[i].r_hold[j];
               graph->property[i].r_hold[j] = 0; 
           }
   }
}

// Driver program to test above functions
int main(int argc, char *argv[])
{
    //srand(time(NULL));
    srand(0);

    // we create a graph (memory allocation)
    struct Graph* graph = createGraph(V);
    // initialize the graph by adding edges
    initGraph(graph);
    // print the graph
    printGraph(graph);
 
    //random walk with restart
    random_walk(graph, 2);
    
    printAllMetapath(); //after random walk

    // remove all the out-going edges of a node 
    for (int i = 0; i < graph->cap; ++i)
       removeAllEdges(graph, i);
    // release the memory allocated to the graph
    deleteGraph(graph);
    return 0;
}
