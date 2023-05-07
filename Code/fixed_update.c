#include "gameloop.h"
#include "objects.h"
#include "Engine/engine.h"

#include <math.h>

#define PI 3.1415926
extern bool game_running;

#define PLAYER_HORIZONTAL_BORDER 4
#define PLAYER_VERTICAL_BORDER 3
#define INVINCIBILITY_TIME 1.4
extern player_t player;

#define BULLET_DESPAWN_DISTANCE 13
#define MAX_NUM_BULLETS 30
extern bullet_t bullets[MAX_NUM_BULLETS];

#define MAX_NUM_ZOMBIES 30
#define ZOMBIE_SPEED 2.5
extern zombie_t zombies[MAX_NUM_ZOMBIES];

void fixed_update(double delta_time)
{
    if (player.invincible)
    {
        player.invincibility_cooldown_clock += delta_time;
        if (player.invincibility_cooldown_clock >= INVINCIBILITY_TIME)
        {
            player.invincibility_cooldown_clock = 0;
            player.invincible = false;

        }

    }

    // bullets
    for (int i = 0; i < MAX_NUM_BULLETS; i++)
    {
        if (bullets[i].exists)
        {
            if (bullets[i].transform.position.x > BULLET_DESPAWN_DISTANCE || bullets[i].transform.position.x < - BULLET_DESPAWN_DISTANCE || bullets[i].transform.position.y > BULLET_DESPAWN_DISTANCE || bullets[i].transform.position.y < - BULLET_DESPAWN_DISTANCE)
            {
                bullets[i].exists = false;
            }
        }
    }
    
    
    // zombies

    for (int i = 0; i < MAX_NUM_ZOMBIES; i++)
    {
        if (zombies[i].exists)
        {
            // zombie AI
            double dx = player.transform.position.x - zombies[i].transform.position.x;
            double dy = player.transform.position.y - zombies[i].transform.position.y;

            double hypothenuse = sqrt(pow(dx, 2) + pow(dy, 2));
            if (hypothenuse >= 0.5)
            {
                double factor = ZOMBIE_SPEED / hypothenuse;
                zombies[i].velocity.x = factor * dx;
                zombies[i].velocity.y = factor * dy;
                zombies[i].transform.rotation = asin(dy / hypothenuse);
                if (dx < 0)
                    zombies[i].transform.rotation = PI - zombies[i].transform.rotation;
            }
            else
            {
                zombies[i].velocity = (vector_t){0, 0};
            }

            // zombie collision with player
            if (collision_player_zombie(&player, &(zombies[i])) && player.invincible == false)
            {
                player.health -= 20;
                if (player.health <= 0)
                    game_running = false;
                else
                    player.invincible = true;
            }

            // zombie collision with bullet

            for (int j = 0; j < MAX_NUM_BULLETS; j++)
            {
                if (bullets[j].exists)
                {
                    if (collision_bullet_zombie(&(bullets[j]), &(zombies[i])))
                    {
                        bullets[j].exists = false;
                        zombies[i].exists = false;
                        break;
                    }
                }
            }
            
        }
    }


    // collision detection



}