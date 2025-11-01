#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

// Window dimensions
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define FRAME_CAP 60

// Set up game controller
void setGameController(SDL_GameController* controller)
{
    if(SDL_NumJoysticks() > 0)
    {
        controller = SDL_GameControllerOpen(0);
        SDL_Log("Controller type %d found!", SDL_GameControllerGetType(controller));
    }
    else
    {
        SDL_Log("No controllers found!");
    }
}

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

    // Create surface to load image into memory
    SDL_Surface* surface;
    // Load image
    surface = IMG_Load("assets/jack.png");

    // Create texture from image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // Free the memory
    SDL_FreeSurface(surface);
    // Create a rectangle sprite to put the texture on
    SDL_Rect sprite;
    SDL_QueryTexture(texture, NULL, NULL, &sprite.w, &sprite.h);

    // Set initial x and y position of sprite
    sprite.x = (WINDOW_WIDTH - sprite.w) / 2;
    sprite.y = (WINDOW_HEIGHT - sprite.h) / 2;

    // Movement speed
    int speed = 300;

    // Array of keys with their states
    const Uint8* key_states;
    // x and y vectors of distance
    float dx = 0;
    float dy = 0;
    // Final distance
    float distance = 0;

    // Set up game controller
    SDL_GameController* controller;
    setGameController(controller);

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

        // Reset vectors
        dx = 0;
        dy = 0;

        // Check if there are no controllers
        if(SDL_NumJoysticks() == 0)
        {
            // If so handle keyboard input
            // Get array of keys with their states
            key_states = SDL_GetKeyboardState(NULL);
            // Assign vector values based on keys pressed
            if(key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_UP])
                dy -= 1;
            if(key_states[SDL_SCANCODE_S] || key_states[SDL_SCANCODE_DOWN])
                dy += 1;
            if(key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
                dx -= 1;
            if(key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
                dx += 1;
        }
        else
        {
            // Otherwise handle controller input
            // Assign vector values based on DPad directions pressed
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP))
                dy -= 1;
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
                dy += 1;
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
                dx -= 1;
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
                dx += 1;
        }

        // Normalize vectors so diagonal is at same speed as cardinal
        distance = sqrtf((dx * dx) + (dy * dy));
        if(distance != 0)
        {
            dx /= distance;
            dy /= distance;
        }

        // Set new sprite position
        sprite.x += dx * speed / FRAME_CAP;
        sprite.y += dy * speed / FRAME_CAP;

        // Handle Bounds
        // Left
        if(sprite.x + sprite.w > WINDOW_WIDTH)
            sprite.x = WINDOW_WIDTH - sprite.w;
        // Right
        if(sprite.x < 0)
            sprite.x = 0;
        // Top
        if(sprite.y < 0)
            sprite.y = 0;
        // Bottom
        if(sprite.y + sprite.h > WINDOW_HEIGHT)
            sprite.y = WINDOW_HEIGHT - sprite.h;

        // Clear Screen
        SDL_RenderClear(renderer);
        // Render sprite
        SDL_RenderCopy(renderer, texture, NULL, &sprite);
        SDL_RenderPresent(renderer);
        // Handle framerate
        SDL_Delay(1000 / FRAME_CAP);
    }

    // Destroy everything!!
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit
    SDL_Quit();

    return 0;
}
