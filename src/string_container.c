#include "string_container.h"
#include<stdlib.h>
#include<string.h>
//function: init_c_string_container
//container: the pionter to the contianer of string.
//returns: the initiatization of the contianer so it won't point to the garbage val.
void init_c_string_container(c_string_container *container){
    container->size =0;
    container->arr = NULL;
}

//function: add_element_to_c_string_container
//description: this is to add the found result from the kv_get to the contianer if there is more than 1 match.
//contianer: pointer to the contianer of string.
//text: string to insert
//text_length: the length of the string to insert
//returns: 0 if the insertion is successful and -1 if otherwise.
int add_element_to_c_string_container(c_string_container *container, const char* text,size_t text_length){
    //allocate the mem for an array pointer
    char** new_arr = (char **) realloc(container->arr, (container->size+1) * sizeof(char *));
    if(!new_arr){
        return -1;
    }
    container->arr = new_arr;
    // allocate the mem for the string itsel to be inserted at the array pointer.
    container->arr[container->size] = malloc(sizeof(text_length)+1);
    if(!container->arr[container->size]){
        return -1;
    }
    memcpy(container->arr[container->size], text, text_length);
    container->arr[container->size][text_length] = '\0';
    container->size++;
    return 0;
}
//function: free_c_string_container
//contianer: pointer to the container of string.
//returns: a free slot of the memory of the allocated the contianer for the string.
void free_c_string_container(c_string_container* container){
    if(container==NULL) {
        return;
    }
    for(size_t i = container->size;i--;){
        free(container->arr[i]);
    }
    free(container->arr);
}

// function: substrings
// input: the string/phrase to input with delimeter.
// delimeter: the char to split elements in the string.
// returns: the container of the substrings addes to the container split by the delimeter.
c_string_container substrings(char* input, const char delimeter){
    c_string_container* container = NULL;
    char* input_end = input+strlen(input);
    init_c_string_container(container);
    char* endpoint=NULL;
    while((endpoint = strchr(input, delimeter))){
        add_element_to_c_string_container(container, input, endpoint-input);
        while(strchr(endpoint, delimeter)== endpoint){
            ++endpoint;
        }
        input = endpoint;
    }
    if(input<input_end){
        add_element_to_c_string_container(container,input,(input_end-input));
    }
    return *container;
}
