#include "graf.h"
#define INFINITY 9999


char* allocName(char* name) {
    return (char*)malloc(sizeof(name) + 1);
}

// initializes Vertice
Vertice* initVertice(char* name) {
    Vertice* vertice = (Vertice*)malloc(sizeof(Vertice));
    vertice->firstEdge = NULL;
    vertice->lastEdge = NULL;
    vertice->prevVertice = NULL;
    vertice->nextVertice = NULL;
    vertice->name = allocName(name);
    strcpy(vertice->name, name);
    return vertice;
}

// initializes Edge
Edge* initEdge(char* name) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->prevEdge = NULL;
    edge->nextEdge = NULL;
    edge->name = allocName(name);
    strcpy(edge->name, name);
    return edge;
}

// initializes Graph
Graph* initGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));  // MUST BE FREED
    graph->verticesNum = 0;
    graph->edgesNum = 0;
    return graph;
}

// frees all Edges of Vertice recursively starting from a specific Edge
void freeEdge(Edge* edge) {
    if (edge->nextEdge != NULL)
        freeEdge(edge->nextEdge);
    free(edge->name);
    free(edge);
    return;
}

// frees all Vertices of Graph recursively starting from a specific Vertice
void freeVertice(Vertice* vertice) {
    if (vertice->nextVertice != NULL)
        freeVertice(vertice->nextVertice);
    if (vertice->firstEdge != NULL)
        freeEdge(vertice->firstEdge);
    free(vertice->name);
    free(vertice);
    return;
}

// frees Graph recursively
void destroyGraph(Graph* graph) {
    if (graph != NULL) {
        if (graph->verticesNum > 0) {
            freeVertice(graph->firstVertice);
        } else {
            printf("Graph is empty\n");
            return;
        }
        free(graph);
    }
    printf("Graph was destroyed successfully\n");
    return;
}

int size_of_array(Graph* graph){
    Vertice* contVertice = graph->firstVertice;
    int counter = 0;

    while (contVertice != NULL) {
        contVertice = contVertice->nextVertice;
        if(atoi(contVertice->name) > counter){
            counter = atoi(contVertice->name);
        }
    }
    return counter;
}

int* g2arr(Graph* graph) {
    int counter = size_of_array(graph);

    int array[counter][counter];
    for (int i = 0; i < counter; i++){
        for (int j = 0; j < counter; j++){
            array[i][j] = 0;
        }
    }

    Vertice* curVertice = graph->firstVertice;
    while (curVertice != NULL) {
        Edge* curEdge = curVertice->firstEdge;
        while (curEdge != NULL) {
            array[atoi(curVertice->name)-48][atoi(curEdge->name)-48] = curEdge->weight;
            curEdge = curEdge->nextEdge;
        }
        curVertice = curVertice->nextVertice;
    }
    return array;
}
int dijkstra(Graph* graph, int startnode, int endnode){
int n = size_of_array(graph);
int* g = g2arr(graph);
int cost[n][n],distance[n],pred[n];
int visited[n],count,mindistance,nextnode,i,j;
//pred[] stores the predecessor of each node
//count gives the number of nodes seen so far
//create the cost matrix
for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(g[i*n+j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=g[i*n+j];
//initialize pred[],distance[] and visited[]
for(i=0;i<n;i++){
distance[i]=cost[startnode][i];
pred[i]=startnode;
visited[i]=0;
}
distance[startnode]=0;
visited[startnode]=1;
count=1;
while(count<n-1){
mindistance=INFINITY;
//nextnode gives the node at minimum distance
for(i=0;i<n;i++)
if(distance[i]<mindistance&&!visited[i]){
mindistance=distance[i];
nextnode=i;
}
//check if a better path exists through nextnode
visited[nextnode]=1;
for(i=0;i<n;i++)
if(!visited[i])
if(mindistance+cost[nextnode][i]<distance[i]){
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
}
count++;
}
return distance[endnode];
} 

// prints receiving Edges of Vertice
void printReceivingEdges(Graph* graph, char* nameTo) {
    Vertice* curVertice = graph->firstVertice;
    char found = 0;
    while (curVertice != NULL) {
        Edge* curEdge = curVertice->firstEdge;
        while (curEdge != NULL) {
            if (strcmp(curEdge->name, nameTo) == 0) {
                if (found == 0) {
                    printf("Rec-edges ");
                    printf("|%s|->%u->|%s|\n", curVertice->name, curEdge->weight, curEdge->name);
                    found = 1;
                } else
                    printf("          |%s|->%u->|%s|\n", curVertice->name, curEdge->weight, curEdge->name);
            }

            curEdge = curEdge->nextEdge;
        }

        curVertice = curVertice->nextVertice;
    }

    if (found == 0)
        printf("No-rec-edges %s\n\n", nameTo);
    else
        printf("\n");
}

Vertice* findVerticeInGraph(Graph* graph, char* name) {
    Vertice* curVertice = graph->firstVertice;
    while (curVertice != NULL) {
        if (strcmp(curVertice->name, name) == 0) {
            return curVertice;
        } else if (strcmp(name, curVertice->name) < 0)
            return NULL;

        curVertice = curVertice->nextVertice;
    }

    return NULL;
}


void find2VerticesInGraph(Graph* graph, char* name1, char* name2, Vertice* foundVertices[2]) {
    Vertice *curVertice1 = graph->firstVertice, *curVertice2 = graph->firstVertice;
    foundVertices[0] = NULL;
    foundVertices[1] = NULL;

    char found1 = 0, found2 = 0, passed1 = 0, passed2 = 0;
    while (curVertice1 != NULL && curVertice2 != NULL) {
        if (found1 == 1) {
            if (strcmp(curVertice2->name, name2) == 0) {
                found2 = 1;
                foundVertices[1] = curVertice2;
                break;
            } else if (strcmp(name2, curVertice2->name) < 0)
                break;  // because list is sorted by name

            curVertice2 = curVertice2->nextVertice;
        } else if (found2 == 1) {
            if (strcmp(curVertice1->name, name1) == 0) {
                found1 = 1;
                foundVertices[0] = curVertice1;
                break;
            } else if (strcmp(name1, curVertice1->name) < 0)
                break;

            curVertice1 = curVertice1->nextVertice;
        } else {
            if (strcmp(curVertice1->name, name1) == 0) {
                found1 = 1;
                foundVertices[0] = curVertice1;
            } else if (strcmp(name1, curVertice1->name) < 0)
                passed1 = 1;  // actually vertice is not found, but set found1 = 1 just to speed up the process of search

            if (strcmp(curVertice2->name, name2) == 0) {
                found2 = 1;
                foundVertices[1] = curVertice2;
            } else if (strcmp(name2, curVertice2->name) < 0)
                passed2 = 1;  // actually vertice is not found, but set found2 = 1 just to speed up the process of search

            if (passed1 == 1 && passed2 == 1) {  // we passed the position where the vertices must have been
                                                 // (because list is sorted)
                foundVertices[0] = NULL;
                foundVertices[1] = NULL;
                return;
            }

            if (found1 == 0 || passed1 == 0)
                curVertice1 = curVertice1->nextVertice;

            if (found2 == 0 || passed2 == 0)
                curVertice2 = curVertice2->nextVertice;
        }
    }
    return;
}

// finds one Edge of a Vertice with or without weight comparison
Edge* findEdgeOfVertice(Graph* graph, Vertice* verticeFrom, char* nameTo, unsigned int weight) {
    char compareWeight = 1;
    if (weight == -1) {
        compareWeight = 0;
    }

    Edge* curEdge = verticeFrom->firstEdge;
    while (curEdge != NULL) {
        if (strcmp(nameTo, curEdge->name) == 0) {
            if (compareWeight == 1) {
                if (curEdge->weight == weight)
                    return curEdge;
            } else
                return curEdge;
        } else if (strcmp(nameTo, curEdge->name) < 0)
            return NULL;

        curEdge = curEdge->nextEdge;
    }

    return NULL;
}

// finds and deletes all Edges in graph that go to the Vertice with name: nameTo
void findAndDeleteEdgesInGraph(Graph* graph, char* nameTo) {
    Vertice* curVertice = graph->firstVertice;

    while (curVertice != NULL) {
        Edge* foundEdge = findEdgeOfVertice(graph, curVertice, nameTo, -1);

        while (foundEdge != NULL) {
            if (foundEdge->prevEdge != NULL) {
                if (foundEdge->nextEdge != NULL)
                    foundEdge->prevEdge->nextEdge = foundEdge->nextEdge;
                else {  // is last edge
                    foundEdge->prevEdge->nextEdge = NULL;
                    curVertice->lastEdge = foundEdge->prevEdge;
                }
            } else {
                if (foundEdge->nextEdge != NULL) {  // is first vertice
                    curVertice->firstEdge = foundEdge->nextEdge;
                    curVertice->firstEdge->prevEdge = NULL;
                } else {  // is the only edge
                    curVertice->firstEdge = NULL;
                    curVertice->lastEdge = NULL;
                }
            }

            free(foundEdge->name);
            free(foundEdge);

            curVertice->edgesNum--;
            graph->edgesNum--;

            foundEdge = findEdgeOfVertice(graph, curVertice, nameTo, -1);
        }

        curVertice = curVertice->nextVertice;
    }
}

// adds an Edge to a Vertice
void addEdgeToVertice(Vertice* vertice, char* name, unsigned int weight) {
    if (vertice->edgesNum == 0) {
        vertice->firstEdge = initEdge(name);
        vertice->firstEdge->weight = weight;

        vertice->lastEdge = vertice->firstEdge;
        vertice->edgesNum++;
        return;
    } else {
        Edge* curEdge = vertice->firstEdge;

        if (strcmp(name, curEdge->name) < 0) {
            Edge* edgeToInsert = initEdge(name);
            edgeToInsert->nextEdge = curEdge;
            edgeToInsert->weight = weight;

            curEdge->prevEdge = edgeToInsert;
            vertice->firstEdge = edgeToInsert;
            vertice->edgesNum++;
            return;
        } else {
            // search for a position in the sorted list
            while (curEdge != NULL) {
                if (curEdge->nextEdge != NULL) {
                    if (strcmp(name, curEdge->nextEdge->name) < 0) {
                        Edge* edgeToInsert = initEdge(name);
                        edgeToInsert->prevEdge = curEdge;
                        edgeToInsert->nextEdge = curEdge->nextEdge;
                        edgeToInsert->weight = weight;

                        curEdge->nextEdge->prevEdge = edgeToInsert;
                        curEdge->nextEdge = edgeToInsert;
                        vertice->edgesNum++;
                        return;
                    }
                } else {
                    vertice->lastEdge->nextEdge = initEdge(name);
                    vertice->lastEdge->nextEdge->prevEdge = curEdge;
                    vertice->lastEdge->nextEdge->weight = weight;

                    vertice->lastEdge = vertice->lastEdge->nextEdge;
                    vertice->edgesNum++;
                    return;
                }
                curEdge = curEdge->nextEdge;
            }
        }
    }
}

// inserts a Vertice to the Graph
Vertice* insertVerticeToGraph(Graph* graph, char* name) {
    Vertice* foundVertice = findVerticeInGraph(graph, name);

    if (foundVertice != NULL) {
        printf("Node |%s| Exists;\n\n", name);
        return NULL;
    }

    if (graph->verticesNum == 0) {
        graph->firstVertice = initVertice(name);

        graph->lastVertice = graph->firstVertice;
        graph->verticesNum++;
        printf("Inserted |%s|\n\n", name);
        return graph->firstVertice;
    } else {
        Vertice* curVertice = graph->firstVertice;
        // insert at start

        if (strcmp(name, curVertice->name) < 0) {
            Vertice* verticeToInsert = initVertice(name);
            verticeToInsert->nextVertice = curVertice;

            curVertice->prevVertice = verticeToInsert;
            graph->firstVertice = verticeToInsert;
            graph->verticesNum++;
            printf("Inserted |%s|\n\n", name);
            return graph->firstVertice;
        } else {
            while (curVertice != NULL) {
                if (curVertice->nextVertice != NULL) {
                    if (strcmp(name, curVertice->nextVertice->name) < 0) {
                        Vertice* verticeToInsert = initVertice(name);
                        verticeToInsert->prevVertice = curVertice;
                        verticeToInsert->nextVertice = curVertice->nextVertice;

                        curVertice->nextVertice->prevVertice = verticeToInsert;
                        curVertice->nextVertice = verticeToInsert;
                        graph->verticesNum++;
                        printf("Inserted |%s|\n\n", name);

                        return curVertice->nextVertice;
                    }
                } else {
                    graph->lastVertice->nextVertice = initVertice(name);
                    graph->lastVertice->nextVertice->prevVertice = curVertice;

                    graph->lastVertice = graph->lastVertice->nextVertice;
                    graph->verticesNum++;
                    printf("Inserted |%s|\n\n", name);
                    return graph->lastVertice;
                }

                curVertice = curVertice->nextVertice;
            }
        }
    }
}

// inserts an Edge to the Graph
void insertEdgeToGraph(Graph* graph, char* name1, char* name2, unsigned int weight) {
    Vertice* foundVertices[2];
    Vertice* verticeTarget;
    if (strcmp(name1, name2) == 0) {
        verticeTarget = findVerticeInGraph(graph, name1);
        if (verticeTarget == NULL)
            verticeTarget = insertVerticeToGraph(graph, name1);
    } else {
        find2VerticesInGraph(graph, name1, name2, foundVertices);
        verticeTarget = foundVertices[0];
        if (foundVertices[0] == NULL)
            verticeTarget = insertVerticeToGraph(graph, name1);

        if (foundVertices[1] == NULL)
            insertVerticeToGraph(graph, name2);
    }

    addEdgeToVertice(verticeTarget, name2, weight);
    graph->edgesNum++;
    printf("Inserted |%s|->%u->|%s|\n\n", name1, weight, name2);
    return;
}

// deletes a Vertice from the Graph
void deleteVerticeFromGraph(Graph* graph, char* name) {
    Vertice* verticeToDelete = findVerticeInGraph(graph, name);
    if (verticeToDelete != NULL) {
        findAndDeleteEdgesInGraph(graph, verticeToDelete->name);

        if (verticeToDelete->firstEdge != NULL)
            freeEdge(verticeToDelete->firstEdge);

        if (verticeToDelete->prevVertice != NULL) {
            if (verticeToDelete->nextVertice != NULL) {
                verticeToDelete->prevVertice->nextVertice = verticeToDelete->nextVertice;
                verticeToDelete->nextVertice->prevVertice = verticeToDelete->prevVertice;
            } else {  // is last vertice
                verticeToDelete->prevVertice->nextVertice = NULL;
                graph->lastVertice = verticeToDelete->prevVertice;
            }
        } else {
            if (verticeToDelete->nextVertice != NULL) {  // is first vertice
                graph->firstVertice = verticeToDelete->nextVertice;
                graph->firstVertice->prevVertice = NULL;
            } else {  // is the only vertice
                graph->firstVertice = NULL;
                graph->lastVertice = NULL;
            }
        }
        free(verticeToDelete->name);
        free(verticeToDelete);
        verticeToDelete = NULL;

        graph->verticesNum--;

        printf("Deleted |%s|\n\n", name);
    } else
        printf("Node |%s| does not exist - abort-d;\n\n", name);

    return;
}

// deletes an Edge from the Graph
char deleteEdgeFromGraph(Graph* graph, char* nameFrom, char* nameTo, unsigned int weight) {
    Vertice* verticeFrom = findVerticeInGraph(graph, nameFrom);
    Vertice* verticeTo = findVerticeInGraph(graph, nameTo);

    if (verticeFrom == NULL) {
        printf("|%s| does not exist - abort-l;\n\n", nameFrom);
        return 1;
    }

    if (verticeTo == NULL) {
        printf("|%s| does not exist - abort-l;\n\n", nameTo);
        return 1;
    }

    Edge* edgeToDelete = findEdgeOfVertice(graph, verticeFrom, nameTo, weight);  // no weight comparison if weight == -1

    if (edgeToDelete == NULL) {
        printf("|%s|->%u->|%s| does not exist - abort-l;\n\n", nameFrom, weight, nameTo);
        return 1;
    }

    if (edgeToDelete->prevEdge != NULL) {
        if (edgeToDelete->nextEdge != NULL) {
            edgeToDelete->prevEdge->nextEdge = edgeToDelete->nextEdge;
            edgeToDelete->nextEdge->prevEdge = edgeToDelete->prevEdge;
        } else {  // is last conn vertice
            edgeToDelete->prevEdge->nextEdge = NULL;
            verticeFrom->lastEdge = edgeToDelete->prevEdge;
        }
    } else {
        if (edgeToDelete->nextEdge != NULL) {  // is first head vertice
            verticeFrom->firstEdge = edgeToDelete->nextEdge;
            verticeFrom->firstEdge->prevEdge = NULL;
        } else {  // is the only conn vertice
            verticeFrom->firstEdge = NULL;
            verticeFrom->lastEdge = NULL;
        }
    }

    free(edgeToDelete->name);
    free(edgeToDelete);
    edgeToDelete = NULL;

    verticeFrom->edgesNum--;
    printf("Del-vertex |%s|->%u->|%s|\n\n", nameFrom, weight, nameTo);
    return 0;
}

int main(){
    Graph* g = initGraph();
    char* c = malloc(sizeof(char));
    c[0] = '1';
    insertVerticeToGraph(g, c);
    printf("%d", size_of_array(g));
}