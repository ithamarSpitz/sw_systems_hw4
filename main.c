#include<stdio.h>
#define INFINITY 9999
int n; // number of nodes or the number of the biggest node number
int** graph; // edges of the graph if there is no edge we use 0

int** create_graph(int size){
    int** new_graph = malloc(sizeof(int*)* size);
    for (int i = 0; i < size; i++){
        new_graph[i] = malloc(sizeof(int)*size);
    }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < count; j++)

    return new_graph;
}

int* node_edges(char*, int size){

}

void add_edges_to_graph(int node_number, *int edges){
    // this function add the node and its edges, the array above it is its edges (were is no edge we use 0)
    int** new_graph;
    if(node_number > n){
        new_graph = create_graph(node_number);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                new_graph[i][j] = graph[i][j];
        n = node_number;
    }
    // add the edges to the graph 
    for (int i = 0; i < n; i++){
        new_graph[node_number][i] = edges[i];
    }
    graph = new_graph;
}

void delete_edges_from_graph(int node_number){
    // this function puts 0 insteade all the edges of the deleted node
    for (int i = 0; i < n; i++)
        graph[node_number][i] = 0;
    for (int i = 0; i < n; i++)
        graph[i][node_number] = 0; 
}

int dijkstra(int startnode, int endnode){
int cost[n][n],distance[n],pred[n];
int visited[n],count,mindistance,nextnode,i,j;
//pred[] stores the predecessor of each node
//count gives the number of nodes seen so far
//create the cost matrix
for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(graph[i][j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=graph[i][j];
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

int main(){
printf("Enter no. of vertices:");
scanf("%d",&n);


int s,d;
printf("\nEnter the adjacency matrix:\n");
for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
scanf("%d",&G[i][j]);

printf("\nEnter the starting node:");
scanf("%d",&s);
scanf("%d",&d);
dijkstra(G,n,s,d);
return 0;
}