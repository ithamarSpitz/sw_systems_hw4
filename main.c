#include<stdio.h>
#include<stdlib.h>
#define INFINITY 9999
int n; // number of nodes or the number of the biggest node number
int** graph; // edges of the graph if there is no edge we use 0
int arr_size;
char* arr;

int** create_graph(int size){
    int** new_graph = malloc(sizeof(int*)* size);
    for (int i = 0; i < size; i++){
        new_graph[i] = malloc(sizeof(int)*size);
    }
    // for (int i = 0; i < size; i++)
    //     for (int j = 0; j < size; j++)

    return new_graph;
}



void add_edges_to_graph(int node_number, int* edges){
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

void a_function(char* str, int size){// get strig from(includes) the letter 'a' untill the next functions letter(not includes that letter)
    n = str[1]-48;
    graph = create_graph(n); // ascii code
    int edges[n];
    int current_node;
    for (int i = 0; i < size; i++){
      if(str[i]=='n'){
          for (int j = 0; j < n; j++)
            edges[j] = 0;
          i +=2;
          current_node = str[i]-48;
          while (i<size && str[i] != 'n'){ // maybe str[i+1]
            int to_node = -1;
            int cur_distance = 0;
            while (str[i] != ' '){
                to_node = to_node*10 + (str[1]-48);
                i++;
            }
            if(to_node !=0)
                i++;
            while (str[i] != ' '){
                cur_distance = cur_distance*10 + (str[1]-48);
                i++;
            }
            if(to_node !=-1)
                edges[to_node] = cur_distance;
          }
          add_edges_to_graph(current_node, edges);
      }
    }
}

void b_function(char* str, int size){
    int edges[n];
    int current_node = str[2]-48;
    for (int i = 0; i < n; i++)
        edges[i] = 0;
    for (int i = 3; i < size; i++){        
            int to_node = -1;
            int cur_distance = 0;
            while (str[i] != ' '){
                to_node = to_node*10 + (str[1]-48);
                i++;
            }
            if(to_node !=0)
                i++;
            while (str[i] != ' '){
                cur_distance = cur_distance*10 + (str[1]-48);
                i++;
            }
            if(to_node !=-1)
                edges[to_node] = cur_distance;
    }
          add_edges_to_graph(current_node, edges);
}


void read_string(){
    char letter;
    scanf("%c",&letter)
    int count = 0;
    char* current_arr;
    while(letter != "\n"){
        current_arr[count] = letter;
        count++;
        scanf("%c",&letter)
    }
    arr = malloc(sizeof(char)*count); 
    for (int i = 0; i < count; i++){
        arr[i] = current_arr[i];
    }
    arr_size = count;
}
    

int main(){
    printf("start");
    read_string();
    printf("scan scceeded");
    for (int i = 0; i < arr_size; i++)
    {
        printf("%c", arr[i]);
    }
    

// printf("Enter no. of vertices:");
// scanf("%d",&n);


// int s,d;
// printf("\nEnter the adjacency matrix:\n");
// for(int i=0;i<n;i++)
// for(int j=0;j<n;j++)
// scanf("%d",&G[i][j]);

// printf("\nEnter the starting node:");
// scanf("%d",&s);
// scanf("%d",&d);
// dijkstra(G,n,s,d);
// return 0;
}