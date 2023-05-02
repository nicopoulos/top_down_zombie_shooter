#include "_ecs.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUM_SCENES 5

typedef uint32_t entity_t;

typedef uint32_t component_t;




typedef struct table_t
{
    entity_t* entities;
    component_t* components;
    size_t number_of_entities; // rows
    size_t number_of_components; // columns

} table_t;

typedef struct scene_t
{
    table_t* tables;
    size_t number_of_tables;

} scene_t;

scene_t scenes[MAX_NUM_SCENES];





entity_t* get_entities_with_components(scene_t* scene, component_t* searched_components, size_t number_of_components)
{
    entity_t* entity_array;
    size_t size = 100;
    size_t capacity = 100;
    entity_array = malloc(10 * sizeof(entity_t));
    

    
    // iterate through each table
    for (int table = 0; table < scene->number_of_tables; table++)
    {
        bool table_has_components = true;

        // check whether table has every component
        for (int component = 0; component < number_of_components; component++)
        {
            if (scene->tables[table].components[searched_components[component]] == NULL)
            {
                table_has_components = false;
                break;
            }

        }
        if (table_has_components)
        {
            // add to list
        }
    }

}


