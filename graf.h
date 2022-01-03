#ifndef GRAF_H
#define GRAF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comments: 
// - the Graph has a double linked list for its Vertices and a double linked list for the Edges of each of the Vertices
// - Vertices are sorted for fast search
// - Edges are sorted for fast search
// - the Graph has a head and last pointer for its Vertices
// - each Vertice has a head and last pointer for its Edges

typedef struct Edge {
    struct Edge* nextEdge;
    struct Edge* prevEdge;
    char* name;
    unsigned int weight; // unsigned int because it represents money
    char visited;
} Edge;

typedef struct Vertice {
    Edge* firstEdge;
    Edge* lastEdge;
    struct Vertice* nextVertice;
    struct Vertice* prevVertice;
    char* name;
    unsigned int edgesNum;
    char visited;
} Vertice;

typedef struct Graph {
    Vertice* firstVertice;
    Vertice* lastVertice;
    unsigned int verticesNum;
    unsigned int edgesNum;
} Graph;

char* allocName(char* name);

Vertice* initVertice(char* name);
Edge* initEdge(char* name);
Graph* initGraph();

void freeEdge(Edge* edge);
void freeVertice(Vertice* vertice);
void destroyGraph(Graph* graph);
int size_of_array(Graph* graph);
int* g2arr(Graph* graph);
int dijkstra(Graph* graph, int startnode, int endnode);

Vertice* findVerticeInGraph(Graph* graph, char* name);
void find2VerticesInGraph(Graph* graph, char* name1, char* name2, Vertice* foundVertices[2]);

Edge* findEdgeOfVertice(Graph* graph, Vertice* verticeFrom, char* nameTo, unsigned int weight);
void findAndDeleteEdgesInGraph(Graph* graph, char* nameTo);

void addEdgeToVertice(Vertice* vertice, char* name, unsigned int weight);
Vertice* insertVerticeToGraph(Graph* graph, char* name);
void insertEdgeToGraph(Graph* graph, char* name1, char* name2, unsigned int weight);

void deleteVerticeFromGraph(Graph* graph, char* name, int should_delete_incoming_eges);

char deleteEdgeFromGraph(Graph* graph, char* nameFrom, char* nameTo, unsigned int weight);


#endif