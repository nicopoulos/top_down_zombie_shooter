#include "gameloop.h"
#include "objects.h"

#include "Engine/engine.h"


// game objects
extern player_t player;
extern bullet_t test_bullet;

#define MAX_NUM_BULLETS 30
extern bullet_t bullets[MAX_NUM_BULLETS];

void render()
{
    clear_buffer();

    for (int i = 0; i < MAX_NUM_BULLETS; i++)
    {
        if (bullets[i].exists)
            draw_world_element(&(bullets[i].transform), &(bullets[i].spritesheet));
    }


    draw_world_element(&(player.transform), &(player.spritesheet));
    show_buffer();
}