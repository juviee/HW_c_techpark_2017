#include <stdio.h>
#include <malloc.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

size_t sub_search(int32_t *array, size_t length, int32_t **sub);
void error_exit(char* msg);
int main(){
    size_t length = 0;
    if(scanf("%zd", &length)<1)
        error_exit("[error]");
    if(length < 0)
        error_exit("[error]");
    if(length == 0)
        printf("0");
    int32_t* array = (int32_t*)malloc(length*sizeof(int32_t));
    if(!array)
        error_exit("[error]");
    for(size_t i = 0; i<length; i++)
        if(scanf("%" SCNd32, &array[i])!=1){
            free(array);
            error_exit("[error]");
        }
    int32_t* sub_array = 0;
    size_t sub_length = sub_search(array, length, &sub_array);
    printf("%zd\n", sub_length);
    for(size_t i = 0; i<sub_length; i++){
        printf("%" PRId32, sub_array[i]);
        printf(" ");
    }
    free(array);
    return 0;
}

size_t sub_search(int32_t *array, size_t length, int32_t **sub_arr_address){
    size_t sub_len = 1, sub_len_cached = 1;
    int32_t* sub_arr = array, *sub_arr_cached = array;
    size_t i = 1;
    for(i = 1; i<length; i++){
       if(array[i]-1 == array[i-1])
           sub_len_cached++;
       else if(sub_len_cached<=sub_len){
           sub_len_cached = 1;
           sub_arr_cached = array + i;
       }
       else{
           sub_len = sub_len_cached;
           sub_arr = sub_arr_cached;
           sub_len_cached = 1;
           sub_arr_cached = array + i;
       }
    }
    
    if(sub_len_cached>sub_len){
       sub_len = sub_len_cached;
       sub_arr = sub_arr_cached;
       sub_len_cached = 1;
       sub_arr_cached = array + i;
   }

    if(sub_len == 1){
        return 0;
    }
    *sub_arr_address = sub_arr;
    return sub_len;
}

void error_exit(char *msg){
    fputs(msg, stdout);
    exit(0);
}
