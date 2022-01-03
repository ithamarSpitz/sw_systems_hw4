#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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



int* convertStrtoArr(char* str, int length){
	int* arr = (int*)malloc(length*sizeof(int));

	int j = 1, i, len = 0;
	for (i = 0; i<length ; i++) {
		if (str[i] == ' '){
			j++;
		}
		else {
			arr[j] = arr[j] * 10 + (str[i] - 48);
		}
	}
    arr[0]= j;
    return arr;
}


int main(){
    char *m;

    printf("input string : ");
    m = inputString(stdin, 10);
    printf("%s\n", m);
    printf("length is :\n%ld", strlen(m));
    int* arr = convertStrtoArr(m, strlen);
    for (int i = 1; i < arr[0]; i++){
        printf("\narr[%d] = %d", i, arr[i]);
            }
    
    free(m);
    return 0;
    // Graph* g = initGraph();
    // insertVerticeToGraph(g, '1');
    // printf("%d", size_of_array(g));
}


