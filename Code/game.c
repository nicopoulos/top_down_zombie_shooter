#include "game.h"
#include "objects.h"
#include "Engine/engine.h"

#define RADIAN_DEGREE_CONVERSION_FACTOR (57.295779513)

#define TICKRATE 30
const double tick_duration = (1.0 / (double)TICKRATE);

#define CAMERA_SPEED_S 2
#define CAMERA_ZOOM_SPEED_S 1.2

#define JOYSTICK_MIN_VALUE 20000

#define PLAYER_SPEED 2


int setup();
void cleanup();
void update();
void render();


double previous_time_stamp_s;
double current_time_stamp_s;
double delta_time = 0;

bool game_running;

extern SDL_GameController* gamepad;



// game objects
transform_t transform;
spritesheet_t spritesheet;

player_t player;


int game()
{
    if (setup() != 0)
        return -1;

    previous_time_stamp_s = SDL_GetTicks64() / 1000.0;


    while (game_running)
    {
        current_time_stamp_s = SDL_GetTicks64() / 1000.0;
        delta_time += current_time_stamp_s - previous_time_stamp_s;
        previous_time_stamp_s = current_time_stamp_s;

        while (delta_time >= tick_duration)
        {
            render();
            update();
            delta_time -= tick_duration;
        }
        render();


    }    

    cleanup();


    return 0;
}

int setup()
{
    /*
    transform.position = (vector_t){.x = 0, .y = 0};
    transform.rotation = 0;
    transform.scale = (vector_t){.x = 1, .y = 1};

    spritesheet.texture = load_texture("Assets/Sprites/test_spritesheet.png");
    *(spritesheet.sprite) = (SDL_Rect){.x = 0, .y = 0, .w = 60, .h = 110};
    */
   set_render_colour(0x80, 0x80, 0x80, 0xff);
   camera_set_zoom(0.2);

    player.transform.position = (vector_t){.x = 0, .y = 0};
    player.transform.rotation = 0;
    player.transform.scale = (vector_t){.x = 1, .y = 1};
    player.velocity.x = 0;
    player.velocity.y = 0;
    player.health = 100;
    player.ammunition = 50;
    player.spritesheet.texture = load_texture("Assets/Sprites/player.png");
    player.spritesheet.sprite = NULL;

    game_running = true;
    return 0;
}

void cleanup()
{
    SDL_DestroyTexture(player.spritesheet.texture);
}



void update()
{
    // input
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                game_running = false;
                break;
            }

            default:
            {
                break;
            }
        }
    }

    int16_t left_axis_x = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTX);
    int16_t left_axis_y = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY);
    double left_axis_diagonal = pow(pow(left_axis_x, 2) + pow(left_axis_y, 2), 0.5);
    if ( left_axis_diagonal >= JOYSTICK_MIN_VALUE)
    {
        double factor = (double)PLAYER_SPEED / left_axis_diagonal;
        player.velocity.x = factor * left_axis_x;
        player.velocity.y = factor * left_axis_y;
    }
    else
    {
        player.velocity.x = 0;
        player.velocity.y = 0;
    }

    int16_t right_axis_x = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_RIGHTX);
    int16_t right_axis_y = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_RIGHTY);
    double right_axis_diagonal = pow(pow(right_axis_x, 2) + pow(right_axis_y, 2), 0.5);
    if (right_axis_diagonal >= JOYSTICK_MIN_VALUE)
    {
        player.transform.rotation = RADIAN_DEGREE_CONVERSION_FACTOR * asin((double)right_axis_y / right_axis_diagonal);
        if (right_axis_x < 0 )
            player.transform.rotation = 180 - player.transform.rotation;
    }



    const Uint8* keyboard_state;
    keyboard_state = SDL_GetKeyboardState(NULL);
    
    if (keyboard_state[SDL_SCANCODE_ESCAPE])
    {
        game_running = false;
    }

    {
    if (keyboard_state[SDL_SCANCODE_UP])
    {
        if (keyboard_state[SDL_SCANCODE_LSHIFT])
            camera_zoom(pow(CAMERA_SPEED_S, delta_time));
        else
            camera_move(0, - CAMERA_SPEED_S * delta_time);
    }
    else if (keyboard_state[SDL_SCANCODE_DOWN])
    {
        if (keyboard_state[SDL_SCANCODE_LSHIFT])
            camera_zoom(pow((1.0 / CAMERA_SPEED_S), delta_time));
        else
            camera_move(0,  CAMERA_SPEED_S * delta_time);
    }
    else if (keyboard_state[SDL_SCANCODE_LEFT])
        camera_move(- CAMERA_SPEED_S * delta_time, 0);
    else if (keyboard_state[SDL_SCANCODE_RIGHT])
        camera_move( CAMERA_SPEED_S * delta_time, 0);
    }


    // update game

    player.transform.position.x += player.velocity.x * delta_time;
    player.transform.position.y += player.velocity.y * delta_time;


}


void render()
{
    clear_buffer();
    draw_world_element(&(player.transform), &(player.spritesheet));
    show_buffer();


    SDL_Delay(10);
}


