#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL_image.h>
#include "vector2.h"

// Entity struct definition
typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rectangle;
    Vector2 position;
    Vector2 speed;
} Entity;

// Function protypes
SDL_Texture* createTexture(const char* path, SDL_Renderer* renderer);
void setInitialEntityPosition(Entity* entity);
Entity setupEntity(int pathOrTexture, void* textureInfo, SDL_Renderer* renderer, Vector2 position, Vector2 speed);
void updateEntityPosition(Entity* entity, Vector2* distance);
void normalizeEntityPositionBounds(Entity* entity);

#endif
