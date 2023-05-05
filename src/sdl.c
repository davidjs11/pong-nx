#include "sdl.h"

#ifdef __SWITCH__
#include "nx.h"
#endif

int initSDL(gameState *state)
{
    // init SDL modules
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );

    // init window
    state->window =
        SDL_CreateWindow("pongNX", SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (!state->window) return -1;

    // init renderer
    state->renderer =
        SDL_CreateRenderer(state->window, 0,
                           SDL_RENDERER_ACCELERATED);
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

    // init the input buffer
    state->input = malloc(INPUT_BUFFER_SIZE);

    // init joystick
    for (int i=0; i<4; i++)
        SDL_JoystickOpen(i);

    return 0;
}


void renderFrame(gameState *state)
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


void processInput(gameState *state)
{
    // process all the inputs
    while(SDL_PollEvent(&(state->event)))
    {
        #ifdef __SWITCH__
        if (state->event.type == SDL_JOYBUTTONDOWN)
            if (state->event.jbutton.button == SWITCH_PLUS)
                state->running = 0;
        #endif

        #ifdef __PC__
        if (state->event.type == SDL_QUIT)
            state->running = 0;
        #endif
    }
    
}
