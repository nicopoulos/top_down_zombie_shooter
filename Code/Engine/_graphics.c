#include "_graphics.h"
#include "_components.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* window;
SDL_Renderer* renderer;

int output_width;
int output_height;


double virtual_pixel_width;
double virtual_pixel_height;

const double virtual_output_width = 3840;
const double virtual_output_height = 2160;

double screen_center_x;
double screen_center_y;



camera_t camera;



int graphics_init()
{
    window = SDL_CreateWindow("hallo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1, 1, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL)
        return -1;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        return -1;

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    SDL_GetRendererOutputSize(renderer, &output_width, &output_height);
    virtual_pixel_width = (double)output_width / virtual_output_width;
    virtual_pixel_height = (double)output_height / virtual_output_height;

    screen_center_x = virtual_output_width / 2.0;
    screen_center_y = virtual_output_height / 2.0;

    camera.vpx_per_meter = 1000; // 1 vpx = 1mm -> 1m = 1000 vpx.
    camera.position = (vector_t){0, 0};

    printf("virtual_pixel: (%f, %f)\n", virtual_pixel_width, virtual_pixel_height);
    printf("screen_center: (%f, %f)\n", screen_center_x, screen_center_y);



    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return 0;


}

int graphics_quit()
{
    TTF_Quit();
    IMG_Quit();

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);

    if (window != NULL)
        SDL_DestroyWindow(window);

    printf("C\n");



    return 0;

}


int camera_set_zoom(double zoom)
{
    if (zoom <= 0)
        return -1;
    camera.vpx_per_meter = 1000 * zoom;
    return 0;
}

int camera_zoom(double factor)
{
    if (factor <= 0)
        return -1;
    camera.vpx_per_meter *= factor;
    return 0;
}

void show_buffer()
{
    SDL_RenderPresent(renderer);
}

int clear_buffer()
{
    return SDL_RenderClear(renderer);
}


SDL_Texture* load_texture(const char* file)
{
    return IMG_LoadTexture(renderer, file);
}


int draw_world_element(const transform_t* transform, const spritesheet_t* spritesheet)
{
    double w = camera.vpx_per_meter * transform->scale.x;
    double h = camera.vpx_per_meter * transform->scale.y;
    double x = screen_center_x + camera.vpx_per_meter * (transform->position.x - camera.position.x);
    double y = screen_center_y + camera.vpx_per_meter * (-(transform->position.y - camera.position.y));
    printf("x: %f, y: %f\n", x, y);
    x -= 0.5 * w;
    y -= 0.5 * h;
    SDL_Rect dstrect = {.x = virtual_pixel_width * x, .y = virtual_pixel_height * y, .w = virtual_pixel_width * w, .h = virtual_pixel_height * h};
    return SDL_RenderCopy(renderer, spritesheet->texture, & (spritesheet->sprite), &dstrect);
}

// int draw_hud_element(const )






