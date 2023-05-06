#include "game.h"
#include "objects.h"
#include "Engine/engine.h"


#include "gameloop.h"

#define RADIAN_DEGREE_CONVERSION_FACTOR (57.295779513)

#define TICKRATE 30
const double tick_duration = (1.0 / (double)TICKRATE);

#define CAMERA_SPEED_S 2
#define CAMERA_ZOOM_SPEED_S 1.2

#define JOYSTICK_MIN_VALUE 20000

#define PLAYER_SPEED 5


int setup();
void cleanup();



extern SDL_GameController* gamepad;

bool game_running;

// ressources
SDL_Texture* bullet_texture;

// game objects
player_t player;
bullet_t test_bullet;

#define MAX_NUM_BULLETS 30
bullet_t bullets[MAX_NUM_BULLETS];


int game()
{
    double previous_time_stamp_s;
    double current_time_stamp_s;

    double delta_time = 0;
    double accumulator = 0;

    if (setup() != 0)
        return -1;

    previous_time_stamp_s = SDL_GetTicks64() / 1000.0;


    while (game_running)
    {
        current_time_stamp_s = SDL_GetTicks64() / 1000.0;
        delta_time = current_time_stamp_s - previous_time_stamp_s;
        accumulator += delta_time;
        previous_time_stamp_s = current_time_stamp_s;


        update(delta_time);
        render();
        while (accumulator >= tick_duration)
        {
            fixed_update(accumulator);
            accumulator -= tick_duration;
        }



    }    

    cleanup();


    return 0;
}

int setup()
{
    set_render_colour(0x80, 0x80, 0x80, 0xff);
    camera_set_zoom(0.2);

    // player

    player.transform.position = (vector_t){.x = 0, .y = 0};
    player.transform.rotation = 0;
    player.transform.scale = (vector_t){.x = 1, .y = 1};
    player.velocity.x = 0;
    player.velocity.y = 0;
    player.health = 100;
    player.ammunition = 50;
    player.spritesheet.texture = load_texture("Assets/Sprites/player.png");
    player.spritesheet.sprite = NULL;

    // bullets
    bullet_texture = load_texture("Assets/Sprites/bullet.png");

    for (int i = 0; i < MAX_NUM_BULLETS; i++)
    {
        bullets[i].exists = false;;
    }





    game_running = true;
    return 0;
}

void cleanup()
{
    SDL_DestroyTexture(player.spritesheet.texture);
    SDL_DestroyTexture(bullet_texture);
}

