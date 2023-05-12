#ifndef OBJECTS_H
#define OBJECTS_H
#include "Engine/_components.h"
#include <stdbool.h>

typedef struct score_t
{
    char string[16];
    int value;
    unsigned int num_characters;

} score_t;

typedef struct player_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    circle_collider_t collider;
    int health;
    score_t score;
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

typedef enum zombie_type_t
{
    SMALL_ZOMBIE,
    MEDIUM_ZOMBIE,
    BIG_ZOMBIE
} zombie_type_t;

typedef struct zombie_t
{
    transform_t transform;
    spritesheet_t spritesheet;
    vector_t velocity;
    circle_collider_t collider;
    zombie_type_t type;
    double speed;
    int health;
    int damage;
    bool exists;

} zombie_t;

void update_score(score_t* score, int value);


void bullet_set_state_from_player(bullet_t* bullet, const player_t* player);


bool collision_player_zombie(const player_t* player, const zombie_t* zombie);

bool collision_bullet_zombie(const bullet_t* bullet, const zombie_t* zombie);

#endif