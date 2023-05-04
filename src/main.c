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

        for(int x=0; x<SCREEN_WIDTH; x++)
            for(int y=0; y<SCREEN_HEIGHT; y++)
                state.framebuffer[y*SCREEN_WIDTH+x] =
                        (x%2) ? 0xFF0000FF : 0x000000FF;

        render(&state);
    }

    return 0;
}

