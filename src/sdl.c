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
            SDL_TEXTUREACCESS_STREAMING,
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

void render(gameState *state)
{
    void *pixels;
    int pitch;

    // draw framebuffer into the texture
    SDL_LockTexture(state->texture, NULL, &pixels, &pitch);

    for (int y=0; y<SCREEN_HEIGHT; y++)
        memcpy(
            &((u8*) pixels)[y * pitch],
            &state->framebuffer[y * SCREEN_WIDTH],
            SCREEN_WIDTH * 4);

    SDL_UnlockTexture(state->texture);

    // clear the renderer
    SDL_SetRenderTarget(state->renderer, NULL);
    SDL_SetRenderDrawColor(state->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_NONE);
    SDL_RenderClear(state->renderer);

    // copy the framebuffer into the renderer
    SDL_RenderCopyEx(
        state->renderer,
        state->texture,
        NULL,
        NULL,
        0.0,
        NULL,
        SDL_FLIP_VERTICAL);
    
    SDL_RenderPresent(state->renderer);
}
