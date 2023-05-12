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
TTF_Font* score_font;
SDL_Texture* heart_texture;

// game objects
player_t player;

#define MAX_NUM_BULLETS 30
bullet_t bullets[MAX_NUM_BULLETS];

#define MAX_NUM_ZOMBIES 20
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
        while (accumulator >= tick_duration)
        {
            fixed_update(accumulator);
            accumulator -= tick_duration;
        }
        render();



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
    player.spritesheet.texture = load_texture("Assets/Sprites/player.png");
    player.spritesheet.sprite = NULL;
    player.shooting_cooldown_clock = 0;
    player.collider.radius = 0.5;
    player.invincibility_cooldown_clock = 0;
    player.invincible = false;

    // health
    player.health = 16;
    heart_texture = load_texture("Assets/Sprites/heart.png");


    // score
    update_score(&(player.score), 0);
    score_font = TTF_OpenFont("Assets/Fonts/prstart.ttf", 36);




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




    game_running = true;
    return 0;
}

void cleanup()
{
    SDL_DestroyTexture(player.spritesheet.texture);
    SDL_DestroyTexture(zombie_texture);
    SDL_DestroyTexture(heart_texture);
    SDL_DestroyTexture(bullet_texture);
    TTF_CloseFont(score_font);
}

