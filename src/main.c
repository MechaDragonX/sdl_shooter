#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "entity.h"
#include "macros.h"
#include "vector2.h"


// === FUNCTIONS ===
// Params: Pointer to pointer to SDL_GameController
// Set up game controller
// Returns: void
void setGameController(SDL_GameController** controller)
{
    if(SDL_NumJoysticks() > 0)
    {
        * controller = SDL_GameControllerOpen(0);
        SDL_Log("Controller type %d found!", SDL_GameControllerGetType(* controller));
    }
    else
    {
        SDL_Log("No controllers found!");
    }
}


// Params: Pointer to distance as 2D vector
// Use keyboard controls to get raw distance vector before normalization
// Returns: void
void getRawDistanceKeyboard(Vector2* distance)
{
    // Get array of keys with their states
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);

    // Assign vector values based on keys pressed
    if(keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP])
        distance->y -= 1;
    if(keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN])
        distance->y += 1;
    if(keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT])
        distance->x -= 1;
    if(keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT])
        distance->x += 1;
}

// Params: Pointer to pointer to SDL_GameController, Pointer to distance as 2D vector
// Use game controller controls to get raw distance vector before normalization
// Returns: void
void getRawDistanceController(SDL_GameController** controller, Vector2* distance)
{
    // Assign vector values based on DPad directions pressed
    if(SDL_GameControllerGetButton(* controller, SDL_CONTROLLER_BUTTON_DPAD_UP))
        distance->y -= 1;
    if(SDL_GameControllerGetButton(* controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
        distance->y += 1;
    if(SDL_GameControllerGetButton(* controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
        distance->x -= 1;
    if(SDL_GameControllerGetButton(* controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
        distance->x += 1;
}

// Params: Pointer to pointer to SDL_GameController
// Check for controller and use either keyboard or controller to get raw distance vector before normalization
// Returns: Vector2 distance
Vector2 getRawDistance(SDL_GameController** controller)
{
    Vector2 distance = {0, 0};

    // Check if there are no controllers
    if(SDL_NumJoysticks() == 0)
    {
        // If so handle keyboard input
        getRawDistanceKeyboard(&distance);
    }
    else
    {
        // Otherwise handle controller input
        getRawDistanceController(controller, &distance);
    }

    return distance;
}


// === Main Function ===
int main(int argc, char* argv[])
{
    // Return zero for success and vice versa
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow
    (
        "Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    // Create render flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    Entity player = setupEntity
    (
        0,
        "assets/jack.png",
        renderer,
        (Vector2){0, 0},
        (Vector2){300, 300}
    );

    // Set up game controller
    SDL_GameController* controller;
    setGameController(&controller);

    // Looping var
    int looping = 1;
    while(looping)
    {
        // Handle SDL events
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                looping = 0;
        }

        // Calculate raw distance from keyboard or controller movement
        Vector2 distance = getRawDistance(&controller);
        // Normalize vectors so diagonal is at same speed as cardinal
        normalizeDistance(&distance);

        // Set new sprite position
        updateEntityPosition(&player, &distance);
        // Handle Bounds
        normalizeEntityPositionBounds(&player);

        // Clear Screen
        SDL_RenderClear(renderer);
        // Render sprite
        SDL_RenderCopy(renderer, player.texture, NULL, &player.rectangle);
        SDL_RenderPresent(renderer);
        // Handle framerate
        SDL_Delay(1000 / FRAME_CAP);
    }

    // Destroy everything!!
    SDL_DestroyTexture(player.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit
    SDL_Quit();

    return 0;
}
