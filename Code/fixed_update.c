#include "gameloop.h"
#include "objects.h"
#include "Engine/engine.h"

#include <time.h>
#include <math.h>

#define PI 3.1415926
extern bool game_running;

#define INVINCIBILITY_TIME 1.7
extern player_t player;

#define BULLET_DESPAWN_DISTANCE 15
#define MAX_NUM_BULLETS 30
extern bullet_t bullets[MAX_NUM_BULLETS];

#define MAX_NUM_ZOMBIES 20
extern zombie_t zombies[MAX_NUM_ZOMBIES];
extern SDL_Texture* zombie_texture;
#define BASE_ZOMBIE_SPAWN_INTERVAL 1.5
double zombie_spawn_interval = BASE_ZOMBIE_SPAWN_INTERVAL;
double zombie_spawn_cooldown = 0;


bool spawn_zombie(const vector_t* spawn_point);
vector_t get_rand_spawn_point();


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
            if (hypothenuse >= player.collider.radius)
            {
                double factor = zombies[i].speed / hypothenuse;
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
                player.health -= zombies[i].damage;
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
                        zombies[i].health--;
                        if (zombies[i].health <= 0)
                        {
                            zombies[i].exists = false;
                            int points;
                            switch(zombies[i].type)
                            {
                                case SMALL_ZOMBIE:
                                    points = 50;
                                    break;
                                case BIG_ZOMBIE:
                                    points = 200;
                                    break;
                                case MEDIUM_ZOMBIE:
                                default:
                                    points = 100;
                                    break;
                            }
                            update_score(&(player.score), player.score.value + points);
                        }
                        break;
                    }
                }
            }
            
        }
    }

    // spawn zombies
    zombie_spawn_cooldown += delta_time;
    if (zombie_spawn_cooldown >= zombie_spawn_interval)
    {
        vector_t spawn_point = get_rand_spawn_point();
        if (spawn_zombie(&spawn_point))
           zombie_spawn_cooldown -= zombie_spawn_interval;

    }


    // adjust spawn_interval
    int exponent = player.score.value / 1000;
    zombie_spawn_interval = BASE_ZOMBIE_SPAWN_INTERVAL * pow(0.95, exponent);



}


bool spawn_zombie(const vector_t* spawn_point)
{
    if (spawn_point == NULL)
        return false;

    for (int i = 0; i < MAX_NUM_ZOMBIES; i++)
    {
        if (zombies[i].exists == false)
        {
            zombies[i].exists = true;
            zombies[i].spritesheet.texture = zombie_texture;
            zombies[i].spritesheet.sprite = NULL;
            zombies[i].velocity.x = 0;
            zombies[i].velocity.y = 0;
            zombies[i].transform.rotation = 0;

            zombies[i].transform.position = *spawn_point;

            int num = rand() % 9 + 1 ;
            zombies[i].type = (num <= 2) ? SMALL_ZOMBIE : (num >= 8) ? BIG_ZOMBIE : MEDIUM_ZOMBIE;

            switch(zombies[i].type)
            {
                case SMALL_ZOMBIE:
                {
                    zombies[i].speed = 4;
                    zombies[i].transform.scale = (vector_t){0.7, 0.7};
                    zombies[i].collider.radius = 0.35;
                    zombies[i].health = 1;
                    zombies[i].damage = 1;
                    break;
                }
                case BIG_ZOMBIE:
                {
                    zombies[i].speed = 1.5;
                    zombies[i].transform.scale = (vector_t){1.7, 1.7};
                    zombies[i].collider.radius = 0.85;
                    zombies[i].health = 3;
                    zombies[i].damage = 4;
                    break;
                }
                case MEDIUM_ZOMBIE:
                default:
                {
                    zombies[i].speed = 2.5;
                    zombies[i].transform.scale = (vector_t){1, 1};
                    zombies[i].collider.radius = 0.5;
                    zombies[i].health = 2;
                    zombies[i].damage = 2;

                    break;
                }
            }


            return true;
        }
    }
    return false;
}
#define OUTER_SPAWNPOINTS_DX 18
#define INNER_SPAWNPOINTS_DX 14
#define INNER_SPAWNPOINTS_DY 12

vector_t get_rand_spawn_point()
{
    srand(time(0));
    int spawn_point = rand() % 6;

    vector_t vec;
    switch(spawn_point)
    {
        case 0:
            vec = (vector_t){OUTER_SPAWNPOINTS_DX, 0};
            break;

        case 1:
            vec = (vector_t){INNER_SPAWNPOINTS_DX, INNER_SPAWNPOINTS_DY};
            break;

        case 2:
            vec = (vector_t){- INNER_SPAWNPOINTS_DX, INNER_SPAWNPOINTS_DY};
            break;

        case 3:
            vec = (vector_t){- OUTER_SPAWNPOINTS_DX, 0};
            break;

        case 4:
            vec = (vector_t){- INNER_SPAWNPOINTS_DX, - INNER_SPAWNPOINTS_DY};
            break;

        case 5:
            vec = (vector_t){INNER_SPAWNPOINTS_DX, - INNER_SPAWNPOINTS_DY};
            break;

        default:
            break;
    }

    return vec;

}


