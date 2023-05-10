#include "gameloop.h"
#include "objects.h"

#include "Engine/engine.h"


// game objects
extern player_t player;
extern bullet_t test_bullet;
extern SDL_Texture* heart_texture;

#define MAX_NUM_BULLETS 30
extern bullet_t bullets[MAX_NUM_BULLETS];

#define MAX_NUM_ZOMBIES 30
extern zombie_t zombies[MAX_NUM_ZOMBIES];

extern TTF_Font* score_font;


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

    // player
    if ((int)(player.invincibility_cooldown_clock * 12) % 2 == 0)
        draw_world_element(&(player.transform), &(player.spritesheet));


    // score
    SDL_Texture* score_texture = text_to_texture(score_font, player.score.string, (SDL_Color){0xff, 0xff, 0xff, 0xff});
    SDL_Rect score_dstrect = {.h = 100, .w = 50 * player.score.num_characters, .x = 20, .y = 20};
    draw_element(score_texture, NULL, &score_dstrect);

    // palyer health
    SDL_Rect heart_rect = {.h = 100, .w = 100, .x = 20, .y = 150};
    for (int i = 0; i < player.health; i++)
    {
        draw_element(heart_texture, NULL, &heart_rect);
        heart_rect.x += heart_rect.w;
    }



    show_buffer();
}