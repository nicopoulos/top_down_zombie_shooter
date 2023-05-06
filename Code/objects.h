#ifndef OBJECTS_H
#define OBJECTS_H
#include "Engine/_components.h"
#include <stdbool.h>

typedef struct player_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    unsigned int health;
    unsigned int ammunition;
    double shooting_cooldown_clock;
    vector_t velocity;

} player_t;

typedef struct bullet_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    vector_t velocity;
    bool exists;

} bullet_t;

typedef struct zombie_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    vector_t velocity;
    bool exists;

} zombie_t;



void bullet_set_state_from_player(bullet_t* bullet, const player_t* player);


#endif