#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "game.h"
#include "graphics.h"
#include "inet.h"
#include "sdl.h"
#include "utils.h"

#ifdef __SWITCH__
#include "switch.h"
#endif


int main(void)
{
    gameState state; 
    initSDL(&state);

    SDL_Event event;
    state.running = 1;
    while(state.running)
    {

        while(SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                state.running = 0;

        memset(state.framebuffer,0xFFFFFF00,SCREEN_WIDTH*SCREEN_HEIGHT*4);
        render(&state);
    }

    return 0;
}

