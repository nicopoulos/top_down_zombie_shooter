#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdlib.h>



typedef struct array_t
{
    void* data;
    size_t length;
    size_t capacity;

} array_t;

array_t p_array_create(size_t length);

int array_push(array_t* array, void* element);

int array_pop(array_t* array, void* element);




#endif