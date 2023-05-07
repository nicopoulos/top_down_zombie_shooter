#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SDL2/SDL.h>

typedef struct vector_t
{
    double x;
    double y;
    // double z;
} vector_t;

typedef struct transform_t
{
    vector_t position;
    vector_t scale;
    double rotation;
} transform_t;


typedef struct spritesheet_t
{
    SDL_Rect* sprite;
    SDL_Texture* texture;
} spritesheet_t;

typedef struct circle_collider_t
{
    double radius;
} circle_collider_t;

#endif