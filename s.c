#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
//            printf("Graph is empty\n");
            return;
        }
        free(graph);
    }
//    printf("Graph was destroyed successfully\n");
    return;
}

int size_of_array(Graph* graph){
    Vertice* contVertice = graph->firstVertice;
    int counter = 0;
    while (contVertice != NULL) {
        if(atoi(contVertice->name)+1 > counter){
            counter = atoi(contVertice->name)+1;
        }
        contVertice = contVertice->nextVertice;

    }
    return counter;
}

int* g2arr(Graph* graph) {
    int counter = size_of_array(graph);
    int* array = (int*) malloc(counter* counter * sizeof(int));
    //int array[counter*counter];
    for (int i = 0; i < counter; i++){
        for (int j = 0; j < counter; j++){
            array[i*counter+j] = 0;
        }
    }
//    printf("function cleard the array");

    Vertice* curVertice = graph->firstVertice;
    while (curVertice != NULL) {
        Edge* curEdge = curVertice->firstEdge;
        while (curEdge != NULL) {
//            printf("atoi(curVertice->name): %d\n atoi(curEdge->name):%d",atoi(curVertice->name),atoi(curEdge->name));
            array[atoi(curVertice->name)*counter+atoi(curEdge->name)] = curEdge->weight;
            curEdge = curEdge->nextEdge;
        }
        curVertice = curVertice->nextVertice;
    }
    return array;
}

int dijkstra(Graph* graph, int startnode, int endnode){
int n = size_of_array(graph);
int* g = g2arr(graph);
/////////////////////
// for (int i = 0; i < n; i++){
//     for (int j = 0; j < n; j++){
//         printf("|%d",g[n*i+j]);
//     }
//     printf("|\n");
// }

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
int ans = distance[endnode];
if(ans == 0 || ans>INFINITY)
    return -1;
return ans;
}

Vertice* findVerticeInGraph(Graph* graph, char* name) {
    Vertice* curVertice = graph->firstVertice;
    while (curVertice != NULL) {
        if(curVertice->name != NULL){
        char* n = curVertice->name;
//        printf("%s\n", n);
        }
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

        if (strcmp(name, curEdge->name) < 0) {//////////// copares to null cur name is not initialize while edges num is 1
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
        // printf("Node |%s| Exists;\n\n", name);
        return NULL;
    }

    if (graph->verticesNum == 0) {
        graph->firstVertice = initVertice(name);

        graph->lastVertice = graph->firstVertice;
        graph->verticesNum++;
        // printf("Inserted woo|%s|\n\n", name);
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
            // printf("first Inserted |%s|\n\n", name);
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
                        // printf("Inserted |%s|\n\n", name);

                        return curVertice->nextVertice;
                    }
                } else {
                    Vertice* verticeToInsert = initVertice(name);
                    graph->lastVertice->nextVertice = verticeToInsert;
                    verticeToInsert->prevVertice = curVertice;

                    graph->lastVertice = verticeToInsert;
                    graph->verticesNum++;
                    // printf("last Inserted |%s|\n\n", name);
                    return verticeToInsert;
                }

                curVertice = curVertice->nextVertice;
            }
        }
    }
}

// inserts an Edge to the Graph
void insertEdgeToGraph(Graph* graph, char* name1, char* name2, unsigned int weight) {

//    printf("\nname1:%s name2:%s\n", name1,  name2);
    Vertice* foundVertices[2];
    Vertice* verticeTarget;
    if (strcmp(name1, name2) == 0) {
//        printf("strings are equall!?");
        verticeTarget = findVerticeInGraph(graph, name1);
        if (verticeTarget == NULL)
            verticeTarget = insertVerticeToGraph(graph, name1);
    } else {
        find2VerticesInGraph(graph, name1, name2, foundVertices);
        verticeTarget = foundVertices[0];
        if (foundVertices[0] == NULL){
            verticeTarget = insertVerticeToGraph(graph, name1);
//            printf("foundVertices[0] == NULL");
        }

        if (foundVertices[1] == NULL){
            insertVerticeToGraph(graph, name2);
            // printf("foundVertices[1] == NULL");
        }
    }
    // printf("verticeTarget is: %s, name2 is: %s weight is: %d\n", verticeTarget->name, name2, weight);
    addEdgeToVertice(verticeTarget, name2, weight);
    graph->edgesNum++;
//    printf("Inserted |%s|->%u->|%s|\n\n", name1, weight, name2);
    return;
}

// deletes a Vertice from the Graph
void deleteVerticeFromGraph(Graph* graph, char* name, int should_delete_incoming_eges) {
    Vertice* verticeToDelete = findVerticeInGraph(graph, name);
    if (verticeToDelete != NULL) {
        if(should_delete_incoming_eges){
            findAndDeleteEdgesInGraph(graph, verticeToDelete->name);
        }

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
        verticeToDelete->edgesNum=0;
        free(verticeToDelete);
        verticeToDelete = NULL;

        graph->verticesNum--;

//        printf("Deleted |%s|\n\n", name);
    } else
//        printf("Node |%s| does not exist - abort-d;\n\n", name);

    return;
}

// deletes an Edge from the Graph
char deleteEdgeFromGraph(Graph* graph, char* nameFrom, char* nameTo, unsigned int weight) {
    Vertice* verticeFrom = findVerticeInGraph(graph, nameFrom);
    Vertice* verticeTo = findVerticeInGraph(graph, nameTo);

    if (verticeFrom == NULL) {
//        printf("|%s| does not exist - abort-l;\n\n", nameFrom);
        return 1;
    }

    if (verticeTo == NULL) {
//        printf("|%s| does not exist - abort-l;\n\n", nameTo);
        return 1;
    }

    Edge* edgeToDelete = findEdgeOfVertice(graph, verticeFrom, nameTo, weight);  // no weight comparison if weight == -1

    if (edgeToDelete == NULL) {
//        printf("|%s|->%u->|%s| does not exist - abort-l;\n\n", nameFrom, weight, nameTo);
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
//    printf("Del-vertex |%s|->%u->|%s|\n\n", nameFrom, weight, nameTo);
    return 0;
}

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}

void s(int* arr, Graph* graph){
    int *garr = g2arr(graph);
    int size = size_of_array(graph); 
    // printf("size is: %d", size);
    // for (int i = 0; i < size; i++)
    // {for (int j = 0; j < size; j++){
    //     printf("|%d", garr[i*size+j]);
    // }
    // printf("|\n");
    // }
    int distance = dijkstra(graph, arr[1], arr[2]);
    printf("Dijakstra is: %d\n", distance);
}

int dijkstra_in_line(Graph* graph, int* arr, int size){
    int* myarr = (int*)malloc(size*sizeof(int));
    int j = 0, sum = 0;
    for (int i = 0; i < 6; i++)
        if(arr[i] != -1)
            myarr[j++] = arr[i];

    for (int i = 0; i < size-1; i++){// size-1 deleted?
        int ans = dijkstra(graph, myarr[i], myarr[i+1]);
        if(ans == -1)
            return -1;
        sum +=  ans;
    }
    return sum;
}

void t(int* arr, Graph* graph){
int min_path = 2147483646;
int nodes[] = {-1, -1, -1, -1, -1, -1};///////////////////////////////////////////
for (int i = 2; i < arr[1]+2; i++)
    nodes[i-2] = arr[i];
int* permute = (int*)malloc(6*sizeof(int));
for (int i1 = 0; i1 < 6; i1++)
    for (int i2 = 0; i2 < 6; i2++)
        for (int i3 = 0; i3 < 6; i3++)
            for (int i4 = 0; i4 < 6; i4++)
                for (int i5 = 0; i5 < 6; i5++)
                    for (int i6 = 0; i6 < 6; i6++){
                        permute[0] = nodes[i1];
                        permute[1] = nodes[i2];
                        permute[2] = nodes[i3];
                        permute[3] = nodes[i4];
                        permute[4] = nodes[i5];
                        permute[5] = nodes[i6];
                        int all_exsists = 0;
                        for (int i7 = 0; i7 < arr[1]; i7++)
                            for (int i8 = 0; i8 < arr[1]; i8++)
                                if(permute[i7]==nodes[i8])
                                    all_exsists++;
                        if(all_exsists == arr[1]){
                            int path = dijkstra_in_line(graph, permute, arr[1]);
                            if(path<min_path && path != -1)
                                    min_path = path;
                        }
                    }
    if(min_path == 2147483646)
        min_path= -1;
    printf("TSP shortest path: %d\n", min_path);
}

int* convertStrtoArr(char* str){
    int length = strlen(str);
	int* arr = (int*)malloc(length*sizeof(int));
    for (int k = 0; k<length ; k++) 
        arr[k] = 0;
	int j = 1, i, len = 0;
	for (i = 0; i<length ; i++) {
		if (str[i] == ' '){
            if(i == 0)
                continue;
			j++;
		}
		else {
			arr[j] = arr[j] * 10 + (str[i] - 48);
		}
	}
    if(str[length-1] != ' ')
        j++;
    arr[0]= j;
    return arr;
}
int is_function(char letter){
    if(letter == 'A'
    || letter == 'B'
    || letter == 'D'
    || letter == 'S'
    || letter == 'T'
    || letter == 'n'
    || letter == '\n'
    ){
        return 1;
    }
    else{
        return 0;
    }
}

int find_next_func(char* str, int start){
    for (int i = start; i < strlen(str); i++){
        if(is_function(str[i])){
            return i;
        }
    }
    return strlen(str);
}
int* func_to_arr(char* str, int start){
    int length = find_next_func(str, start+1) - start -1;
    char* dest;
    dest = realloc(NULL, sizeof(*str)*length);
    strncpy(dest, str+start+1, length);
    return convertStrtoArr(dest);
}

void b(int* arr, Graph* graph){
    int number = arr[1];
    char* name;   
    name = realloc(NULL, sizeof(char)*10);   ///////////////////////////////
    for (int i = 0; i < 10; i++)
        name[i] = ' ';
    snprintf (name, 10*sizeof(char), "%d",number);
    //itoa(number, name, 10);
    deleteVerticeFromGraph(graph, name, 0);
    if(arr[0] == 2){
        insertVerticeToGraph(graph, name);
        return;
    }else{
    char* dest_name;    
    dest_name = realloc(NULL, sizeof(char)*10);
    for (int i = 2; i < arr[0]; i+=2){
        for (int j = 0; j < 10; j++)
            dest_name[j] = ' ';
        number = arr[i];
        snprintf (dest_name, 10*sizeof(char), "%d",number);
        //itoa(number,dest_name,10);
        int weight = arr[i+1];
        // printf("\nname1:%s  name2:%s\n", name, dest_name);
        insertEdgeToGraph(graph, name, dest_name, weight);
    }}
}

void d(int* arr, Graph* graph){
    int number=arr[1];
    char* name;    
    name = realloc(NULL, sizeof(char)*10);
    for (int i = 0; i < 10; i++)
        name[i] = ' ';
    snprintf (name, 10*sizeof(char), "%d",number);
    //itoa(number,name,10);
    deleteVerticeFromGraph(graph, name, 1);
}

Graph* function_finder(char* str, Graph* graph){
    for (int i = 0; i < strlen(str); i++){
        if(is_function(str[i])){
            int* a = realloc(NULL, sizeof(int)*strlen(str));
            a = func_to_arr(str, i);
    switch (str[i]){
    case 'A':
        // printf("finder found A");
        destroyGraph(graph);
        graph = initGraph();
        // printf("graph initiate successfuly");
        break;
    case 'n':
        b(a, graph);
        // printf("node initiate successfuly");
        break;
    case 'B':
        b(a, graph);
        break;
    case 'D':
        // printf("d(a, graph);");
        d(a, graph);
        break;
    case 'S':
        s(a, graph);
        // printf("s(a, graph);");
        break;
    case 'T':
        // printf("t(a, graph);");
        t(a, graph);
        break;
    default:
        break;
    }
    }
    }return graph;
}

int main(void){
    char *str;
    str = inputString(stdin, 10);
    Graph* g = initGraph();
    g = function_finder(str, g);
    int i = 1;
    Vertice* node = g->firstVertice;
    free(str);
    return 0;
}
//uninitialized value ats
