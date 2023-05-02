#ifndef OBJECTS_H
#define OBJECTS_H
#include "Engine/_components.h"

typedef struct player_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    unsigned int health;
    unsigned int ammunition;
    vector_t velocity;

} player_t;


#endif