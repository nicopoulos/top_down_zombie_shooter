#include "game.h"
#include "objects.h"
#include "Engine/engine.h"


#include "gameloop.h"

#define RADIAN_DEGREE_CONVERSION_FACTOR (57.295779513)
#define PI 3.1415926

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
SDL_Texture* zombie_texture;

// game objects
player_t player;

#define MAX_NUM_BULLETS 30
bullet_t bullets[MAX_NUM_BULLETS];

#define MAX_NUM_ZOMBIES 30
zombie_t zombies[MAX_NUM_ZOMBIES];


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
    player.shooting_cooldown_clock = 0;
    player.collider.radius = 0.5;
    player.invincibility_cooldown_clock = 0;
    player.invincible = false;

    // bullets
    bullet_texture = load_texture("Assets/Sprites/bullet_4.png");

    for (int i = 0; i < MAX_NUM_BULLETS; i++)
    {
        bullets[i].exists = false;;
    }

    zombie_texture = load_texture("Assets/Sprites/zombie.png");
    for (int i = 0; i < MAX_NUM_ZOMBIES; i++)
    {
        zombies[i].exists = false;
    }
    for (int i = 0; i < 7; i++)
    {
        zombies[i].exists = true;
        zombies[i].spritesheet.texture = zombie_texture;
        zombies[i].spritesheet.sprite = NULL;
        zombies[i].velocity.x = 0;
        zombies[i].velocity.y = 0;
        zombies[i].collider.radius = 0.5;
    }

    zombies[0].transform = (transform_t){.position = {7, 2.5}, .rotation = 0, .scale = {1, 1}};
    zombies[1].transform = (transform_t){.position = {-5, -0.5}, .rotation = PI, .scale = {1, 1}};
    zombies[2].transform = (transform_t){.position = {-8, -7}, .rotation = 0, .scale = {1, 1}};
    zombies[3].transform = (transform_t){.position = {2, 12}, .rotation = PI, .scale = {1, 1}};
    zombies[4].transform = (transform_t){.position = {-4, -18}, .rotation = PI, .scale = {1, 1}};
    zombies[5].transform = (transform_t){.position = {0, 10}, .rotation = PI, .scale = {1, 1}};
    zombies[6].transform = (transform_t){.position = {5, -20}, .rotation = PI, .scale = {1, 1}};



    game_running = true;
    return 0;
}

void cleanup()
{
    SDL_DestroyTexture(player.spritesheet.texture);
    SDL_DestroyTexture(bullet_texture);
}

