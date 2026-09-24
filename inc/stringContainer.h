#ifndef C_STRING_CONTAINER
#define C_STRING_CONTAINER
// c_string_container
#include <stddef.h>
typedef struct {
    char** arr;
    size_t size;
}c_string_container;

void init_c_string_container(c_string_container *contianer);
int add_element_to_c_string_container(c_string_container *container, const char* text, size_t text_length);
void free_c_string_container(c_string_container* container);
c_string_container substrings(char* input, char* delimeter);

#endif
