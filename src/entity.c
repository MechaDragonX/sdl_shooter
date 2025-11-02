#include "entity.h"
#include "macros.h"
#include "vector2.h"

// Prams: path to image, pointer to SDL_Renderer
// Create surface, load image to surface, create texture, free surface
// Returns: Pointer to SDL_Texture
SDL_Texture* createTexture(const char* path, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

// Params: Pointer to Entity
// Set intitial entity position. At present is center of window
// Returns: void
void setInitialEntityPosition(Entity* entity)
{
    // Set initial x and y position of sprite
    entity->rectangle.x = (WINDOW_WIDTH - entity->rectangle.w) / 2;
    entity->rectangle.y = (WINDOW_HEIGHT - entity->rectangle.h) / 2;
}

// Params: path string, pointer to SDL_Renderer, Vector2 position, Vector2 speed
// Create tecture, set texture to entity rectangle, set intitla position
// Returns Entity
Entity setupEntity(const char* path, SDL_Renderer* renderer, Vector2 position, Vector2 speed)
{
    Entity entity =
    {
        createTexture(path, renderer),
        {},
        {0, 0},
        {300, 300}
    };
    SDL_QueryTexture(entity.texture, NULL, NULL, &entity.rectangle.w, &entity.rectangle.h);

    setInitialEntityPosition(&entity);

    return entity;
}

// Params: Pointer to Entity, pointe to Vector2 distance
// Set new entity position based on distance travelled
// Returns: void
void updateEntityPosition(Entity* entity, Vector2* distance)
{
    entity->rectangle.x += distance->x * entity->speed.x / FRAME_CAP;
    entity->rectangle.y += distance->y * entity->speed.y / FRAME_CAP;
}

// Params: Poitner to Entity
// Make sure entity position is within window bounds
// Returns: void
void normalizeEntityPositionBounds(Entity* entity)
{
    // Left
    if(entity->rectangle.x + entity->rectangle.w > WINDOW_WIDTH)
        entity->rectangle.x = WINDOW_WIDTH - entity->rectangle.w;
    // Right
    if(entity->rectangle.x < 0)
        entity->rectangle.x = 0;
    // Top
    if(entity->rectangle.y < 0)
        entity->rectangle.y = 0;
    // Bottom
    if(entity->rectangle.y + entity->rectangle.h > WINDOW_HEIGHT)
        entity->rectangle.y = WINDOW_HEIGHT - entity->rectangle.h;
}
