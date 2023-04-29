#include "game.h"
#include "Engine/engine.h"

bool game_running;

int game()
{
    transform_t transform;
    transform.position = (vector_t){.x = 0, .y = 0};
    transform.rotation = 0;
    transform.scale = (vector_t){.x = 1, .y = 1};

    spritesheet_t spritesheet;
    spritesheet.texture = load_texture("Assets/Sprites/test_spritesheet.png");
    spritesheet.sprite = (SDL_Rect){.x = 0, .y = 0, .w = 60, .h = 110};
    printf("texture: %p\n", spritesheet.texture);

    game_running = true;
    while (game_running)
    {
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
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.scancode)
                    {


                        default:
                            break;
                    }
                    break;
                }


                default:
                {
                    break;
                }
            }
        }

        const Uint8* keyboard_state;
        keyboard_state = SDL_GetKeyboardState(NULL);

        if (keyboard_state[SDL_SCANCODE_ESCAPE])
            game_running = false;
        if (keyboard_state[SDL_SCANCODE_UP])
        {
            if (keyboard_state[SDL_SCANCODE_LSHIFT])
                camera_zoom(1.1);
            else
                camera.position.y += 0.1;
        }
        else if (keyboard_state[SDL_SCANCODE_DOWN])
        {
            if (keyboard_state[SDL_SCANCODE_LSHIFT])
                camera_zoom(0.9);
            else
                camera.position.y -= 0.1;
        }
        else if (keyboard_state[SDL_SCANCODE_LEFT])
            camera.position.x -= 0.1;
        else if (keyboard_state[SDL_SCANCODE_RIGHT])
            camera.position.x += 0.1;
            


        clear_buffer();
        draw_world_element(&transform, &spritesheet);
        show_buffer();


        SDL_Delay(10);



    }

    SDL_DestroyTexture(spritesheet.texture);






    

    return 0;
}