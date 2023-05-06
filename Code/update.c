#include "gameloop.h"

#include "Engine/engine.h"
#include "objects.h"

#define RADIAN_DEGREE_CONVERSION_FACTOR (57.295779513)

#define PI 3.1415926

#define CAMERA_SPEED_S 2
#define CAMERA_ZOOM_SPEED_S 1.2

#define JOYSTICK_MIN_VALUE 20000

#define PLAYER_SPEED 5


extern bool game_running;
extern SDL_GameController* gamepad;

// ressources
extern SDL_Texture* bullet_texture;

// game objects
extern player_t player;
extern bullet_t test_bullet;

#define MAX_NUM_BULLETS 30
extern bullet_t bullets[MAX_NUM_BULLETS];

void update(double delta_time)
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
            case SDL_CONTROLLERDEVICEREMOVED:
            {
                gamepad = NULL;

                break;

            }
            case SDL_CONTROLLERDEVICEADDED:
            {
                if (SDL_NumJoysticks() == 1)
                {
                    gamepad = SDL_GameControllerOpen(0);
                    player.velocity.x = 0;
                    player.velocity.y = 0;
                }
                break;
            }
            case SDL_CONTROLLERBUTTONDOWN:
            {
                int i;
                for(i = 0; i < MAX_NUM_BULLETS ; i++)
                {
                    if (bullets[i].exists == false)
                    {
                        bullets[i].exists = true;
                        bullets[i].spritesheet = (spritesheet_t){.sprite = NULL, .texture = bullet_texture};
                        bullet_set_state_from_player(&(bullets[i]), &player);
                        
                        break;
                    }
                }

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
        player.transform.rotation = asin((double)right_axis_y / right_axis_diagonal);
        if (right_axis_x < 0 )
            player.transform.rotation = PI - player.transform.rotation;
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

    for (int i = 0; i < MAX_NUM_BULLETS; i++)
    {
        if (bullets[i].exists)
        {
            bullets[i].transform.position.x += bullets[i].velocity.x * delta_time;
            bullets[i].transform.position.y += bullets[i].velocity.y * delta_time;
        }
    }


}