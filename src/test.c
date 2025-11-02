#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

// === MACROS ===
// Window dimensions
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define FRAME_CAP 60


// === STRUCTS ===
typedef struct
{
    float x;
    float y;
} Vector2;

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rectangle;
    Vector2 position;
    Vector2 speed;
} Entity;


// === FUNCTIONS ===
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

// Params: Pointer to SDL_GameController
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

    Entity player =
    {
        createTexture("assets/jack.png", renderer),
        {},
        {0, 0},
        {300, 300}
    };
    SDL_QueryTexture(player.texture, NULL, NULL, &player.rectangle.w, &player.rectangle.h);

    // Set initial x and y position of sprite
    player.rectangle.x = (WINDOW_WIDTH - player.rectangle.w) / 2;
    player.rectangle.y = (WINDOW_HEIGHT - player.rectangle.h) / 2;

    // Array of keys with their states
    const Uint8* key_states;

    // Raw distance
    Vector2 distance = {0, 0};
    // Final distance
    float final_distance = 0;

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

        // Reset vectors
        distance = (Vector2){0, 0};

        // Check if there are no controllers
        if(SDL_NumJoysticks() == 0)
        {
            // If so handle keyboard input
            // Get array of keys with their states
            key_states = SDL_GetKeyboardState(NULL);
            // Assign vector values based on keys pressed
            if(key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_UP])
                distance.y -= 1;
            if(key_states[SDL_SCANCODE_S] || key_states[SDL_SCANCODE_DOWN])
                distance.y += 1;
            if(key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
                distance.x -= 1;
            if(key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
                distance.x += 1;
        }
        else
        {
            // Otherwise handle controller input
            // Assign vector values based on DPad directions pressed
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP))
                distance.y -= 1;
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
                distance.y += 1;
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
                distance.x -= 1;
            if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
                distance.x += 1;
        }

        // Normalize vectors so diagonal is at same speed as cardinal
        final_distance = sqrtf((distance.x * distance.x) + (distance.y * distance.y));
        if(final_distance != 0)
        {
            distance.x /= final_distance;
            distance.y /= final_distance;
        }

        // Set new sprite position
        player.rectangle.x += distance.x * player.speed.x / FRAME_CAP;
        player.rectangle.y += distance.y * player.speed.y / FRAME_CAP;

        // Handle Bounds
        // Left
        if(player.rectangle.x + player.rectangle.w > WINDOW_WIDTH)
            player.rectangle.x = WINDOW_WIDTH - player.rectangle.w;
        // Right
        if(player.rectangle.x < 0)
            player.rectangle.x = 0;
        // Top
        if(player.rectangle.y < 0)
            player.rectangle.y = 0;
        // Bottom
        if(player.rectangle.y + player.rectangle.h > WINDOW_HEIGHT)
            player.rectangle.y = WINDOW_HEIGHT - player.rectangle.h;

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
