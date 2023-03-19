/**
 * ZAD1 - Wykonane w 100%
*/

#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * COMPLETED:
 * Create an array with specified size (int)
*/
wc_array array_init(unsigned int size){
    struct wc_array array ={NULL,0,0};
    array.data = (char **)calloc(size,sizeof(char *));
    array.size = size;
    array.current_size = 0;
    return array;
}

/**
 * COMPLETED:
 * Execute wc command to count lines and words in file
*/
int wc_execute(char* file,struct wc_array *array){
    if(array->size <= array->current_size){
        printf("You don't have enaugh space in the array");
        return -1;
    }

    char cmd[10240];
    char cmd_beg[10240] = "wc ";
    char cmd_end[] = " > /tmp/tmp.txt";

    int result = snprintf(cmd,sizeof(cmd),"%s%s%s",cmd_beg,file,cmd_end);
    if(result < 0){
        printf("Length of file names is longer than 1000 characters\n\n");
        return -2;
    }
    system(cmd);

    FILE* filename = fopen("/tmp/tmp.txt","r");

    if(filename == NULL){
        perror("Cannot open the file");
        return -3;
    }

    fseek(filename,0L,SEEK_END);
    
    long long file_len = ftell(filename);
    char* block = (char *)calloc(file_len,sizeof(char));

    if(file_len == -1){
        printf("Cannot read the size of tmp.txt\n\n");
        return -4;
    }

    if(fseek(filename,0L,SEEK_SET) != 0){
        printf("Cannot rewind tmp.txt");
        return -5;
    }

    size_t new_len = fread(block,sizeof(char),file_len,filename);
    if(ferror(filename) != 0){
        printf("Error reading tmp.txt");
        return -6;
    }
    else{
        block[new_len++] = '\0';
    }
    

    fclose(filename);
    result = system("rm -f /tmp/tmp.txt");

    int idx = 0;
    while(array->data[idx] != NULL && idx < array->size){
        idx++;
    }
    
    array->data[idx] = block;
    array->current_size++;

    return idx;
}

/**
 * COMPLETED:
 * Show array data under specified index
*/
char* show_index(int index,struct wc_array *array){
    if(array->data == NULL){
        printf("The array has not been allocated yet\n\n");
        exit(0);
    }

    if(array->size <= index){
        printf("The array is smaller than %d\n\n",index);
        exit(0);
    }

    if(array->data[index] == NULL){
        printf("There is no block under %d index\n\n",index);
        exit(0);
    }

    return array->data[index];
}

/**
 * COMPLETED:
 * Delete from array blocks of spefified index
*/

int delete_index(int index,struct wc_array *array){
    if(array->data == NULL){
        printf("The array has not been allocated yet\n\n");
        return -1;
    }

    if(array->size <= index){
        printf("The index is greater than %d\n\n",array->size);
        return -2;
    }

    if(array->data[index] == NULL){
        printf("There is no block under %d index\n\n",index);
        return -3;
    }

    free(array->data[index]);

    for(int i=index;i<array->size;i++){
        array->data[i] = array->data[i+1];
    }

    array->current_size--;
    return 0;
}

/**
 * COMPLETED:
 * Remove array from memory
*/
int destroy_array(struct wc_array *array){
    if(array->data == NULL){
        printf("The array has not been allocated yet\n\n");
        return -1;
    }

    for(int i=0;i<array->size;i++){
        free(array->data[i]);
    }

    free(array->data);
    return 0;
}