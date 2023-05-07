#include "objects.h"
#include "Engine/_physics.h"
#include <math.h>
#include <stdbool.h>

#define PI 3.1415926

#define BULLET_WIDTH 0.3
#define BULLET_HEIGHT 0.15
#define BULLET_COLLIDER_RADIUS 0.15
#define BULLET_SPEED 15

void bullet_set_state_from_player(bullet_t* bullet, const player_t* player)
{
    bullet->transform.scale.x = BULLET_WIDTH;
    bullet->transform.scale.y = BULLET_HEIGHT;

    double distance_player_weapon = player->transform.scale.x / 2.0;
    bullet->velocity.x = cos(player->transform.rotation) * BULLET_SPEED;
    bullet->velocity.y = sin(player->transform.rotation) * BULLET_SPEED;
    double x_offset = cos(player->transform.rotation) * distance_player_weapon;
    double y_offset = sin(player->transform.rotation) * distance_player_weapon;

    bullet->transform.position.x = player->transform.position.x + x_offset;
    bullet->transform.position.y = player->transform.position.y + y_offset;
    bullet->transform.rotation = player->transform.rotation;
    bullet->collider.radius = BULLET_COLLIDER_RADIUS;


}


bool collision_player_zombie(const player_t* player, const zombie_t* zombie)
{
    return collision_detected(&(player->collider), &(player->transform), &(zombie->collider), &(zombie->transform));
}

bool collision_bullet_zombie(const bullet_t* bullet, const zombie_t* zombie)
{
    return collision_detected(&(bullet->collider), &(bullet->transform), &(zombie->collider), &(zombie->transform));
}
