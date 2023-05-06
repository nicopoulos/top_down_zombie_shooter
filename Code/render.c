#include "gameloop.h"
#include "objects.h"

#include "Engine/engine.h"


// game objects
extern player_t player;
extern bullet_t test_bullet;

#define MAX_NUM_BULLETS 30
extern bullet_t bullets[MAX_NUM_BULLETS];

#define MAX_NUM_ZOMBIES 30
extern zombie_t zombies[MAX_NUM_ZOMBIES];

void render()
{
    clear_buffer();

    // bullets
    for (int i = 0; i < MAX_NUM_BULLETS; i++)
    {
        if (bullets[i].exists)
            draw_world_element(&(bullets[i].transform), &(bullets[i].spritesheet));
    }

    // zombies
    for (int i = 0; i < MAX_NUM_ZOMBIES; i++)
    {
        if (zombies[i].exists)
            draw_world_element(&(zombies[i].transform), &(zombies[i].spritesheet));
    }


    draw_world_element(&(player.transform), &(player.spritesheet));
    show_buffer();
}