#include "_data_structures.h"
#include <stdlib.h>
#include <stdint.h>



array_t p_array_create(size_t length)
{
    array_t arr;
    arr.length = length;
    arr.capacity = 2 * length;
    arr.data = malloc(arr.capacity * sizeof(void*));
    return arr;
}

int array_free(array_t* array)
{
    return 0;

}

int array_push(array_t* array, void* element)
{


    return 0;
}

int array_pop(array_t* array, void* element)
{


    return 0;
}