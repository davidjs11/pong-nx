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
    state->input = calloc(INPUT_BUFFER_SIZE, sizeof(u8));

    // init joystick
    #ifndef __PC__
    for (int i=0; i<4; i++)
        SDL_JoystickOpen(i);
    #endif

    return 0;
}

void quitSDL(gameState *state)
{
    SDL_DestroyWindow(state->window);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyTexture(state->texture);
    SDL_Quit();
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


void getInput(gameState *state)
{
    // process all the inputs
    while(SDL_PollEvent(&(state->event)))
    {
        u8 newState = 0;
        #ifdef __SWITCH__
        if (state->event.type == SDL_JOYBUTTONUP)
            newState = 0;
        else if (state->event.type == SDL_JOYBUTTONDOWN)
            newState = 1;
        switch (state->event.jbutton.button)
        {
            case SWITCH_PLUS:
                state->input[BUTTON_START] = newState;
                break;
            case SWITCH_A:
                state->input[BUTTON_A] = newState;
                break;
            case SWITCH_B:
                state->input[BUTTON_B] = newState;
                break;
            case SWITCH_UP:
                state->input[ARROW_UP] = newState;
                break;
            case SWITCH_DOWN:
                state->input[ARROW_DOWN] = newState;
                break;
            case SWITCH_LEFT:
                state->input[ARROW_LEFT] = newState;
                break;
            case SWITCH_RIGHT:
                state->input[ARROW_RIGHT] = newState;
                break;
        }
        #endif

        #ifdef __PC__
        const u8 *keystate = SDL_GetKeyboardState(NULL);
        state->input[BUTTON_START] = keystate[SDL_SCANCODE_Q]; 
        state->input[ARROW_UP] = keystate[SDL_SCANCODE_UP];
        state->input[ARROW_DOWN] = keystate[SDL_SCANCODE_DOWN];
        state->input[ARROW_LEFT] = keystate[SDL_SCANCODE_LEFT];
        state->input[ARROW_RIGHT] = keystate[SDL_SCANCODE_RIGHT];
        state->input[BUTTON_A] = keystate[SDL_SCANCODE_A];
        state->input[BUTTON_B] = keystate[SDL_SCANCODE_S];
        if (state->event.type == SDL_QUIT)
            state->input[BUTTON_START] = 1;
        #endif
    }
    
}