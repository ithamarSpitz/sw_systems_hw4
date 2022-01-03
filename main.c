#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *inputString(){
    FILE* fp = stdin;
    size_t size = 10;
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

void function_finder(char* str){
    for (int i = 0; i < strlen(str); i++)
    {switch (str[i]){
    case 'A':
        printf("a is between %d to %d", i+1, find_next_func(str, i+1));
        break;
    case 'B':
        printf("b is between %d to %d", i+1, find_next_func(str, i+1));
        break;
    case 'D':
        printf("d is between %d to %d", i+1, find_next_func(str, i+1));
        break;
    case 'S':
        printf("s is between %d to %d", i+1, find_next_func(str, i+1));
        break;
    case 'T':
        printf("t is between %d to %d", i+1, find_next_func(str, i+1));
        break;
    default:
        break;
    }

    }
    
}


int main(){
    char *m;

    printf("input string : ");
    m = inputString();
    printf("%s\n", m);
    printf("length is :\n%ld", strlen(m));
    int* arr = convertStrtoArr(m);
    printf("length of arr is: %d", arr[0]);
    for (int i = 1; i < arr[0]; i++){
        printf("\narr[%d] = %d", i, arr[i]);
            }
    
    free(m);
    return 0;
    // Graph* g = initGraph();
    // insertVerticeToGraph(g, '1');
    // printf("%d", size_of_array(g));
}


