#include<stdio.h>
#include<stdlib.h>
#include"graf.h"




int main(){
    Graph* g = initGraph();
    insertVerticeToGraph(g, '1');
    printf("%d", size_of_array(g));
}