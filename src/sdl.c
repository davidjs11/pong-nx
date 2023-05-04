#include "sdl.h"

int initSDL(gameState *state)
{
    // init SDL modules
    SDL_Init( SDL_INIT_VIDEO );

    // init window
    state->window =
        SDL_CreateWindow(
            "pongNX",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1280, 720, 0);
    if (!state->window) return -1;

    // init renderer
    state->renderer =
        SDL_CreateRenderer(
            state->window,
            SDL_RENDERER_ACCELERATED,
            0);
    if (!state->renderer) return -1;

    // init texture
    state->texture =
        SDL_CreateTexture(
            state->renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            SCREEN_WIDTH,
            SCREEN_HEIGHT);
    if (!state->texture) return -1;

    // start running the game
    state->running = 1;

    // init the framebuffer 
    state->framebuffer = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * 4);
    if (!state->framebuffer) return -1;

    return 0;
}
