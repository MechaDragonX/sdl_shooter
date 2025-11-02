#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL_image.h>
#include "vector2.h"

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rectangle;
    Vector2 position;
    Vector2 speed;
} Entity;

#endif
