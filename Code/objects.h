#ifndef OBJECTS_H
#define OBJECTS_H
#include "Engine/_components.h"
#include <stdbool.h>

typedef struct player_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    circle_collider_t collider;
    int health;
    unsigned int ammunition;
    double shooting_cooldown_clock;
    double invincibility_cooldown_clock;
    bool invincible;
    vector_t velocity;

} player_t;

typedef struct bullet_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    vector_t velocity;
    circle_collider_t collider;
    bool exists;
    

} bullet_t;

typedef struct zombie_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    vector_t velocity;
    circle_collider_t collider;
    bool exists;

} zombie_t;



void bullet_set_state_from_player(bullet_t* bullet, const player_t* player);


bool collision_player_zombie(const player_t* player, const zombie_t* zombie);

bool collision_bullet_zombie(const bullet_t* bullet, const zombie_t* zombie);

#endif