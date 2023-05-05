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
#include "nx.h"
#endif


int main(void)
{
    // debugging for switch
    #ifdef __SWITCH__
    initNxlink();
    printf("connected to switch!\n");
    #endif

    // create the game state info
    gameState state = {0}; 

    // init SDL
    initSDL(&state);

    // fill the screen 
    for(int x=0; x<SCREEN_WIDTH; x++)
        for (int y=0; y<SCREEN_HEIGHT; y++)
            state.framebuffer[y*SCREEN_WIDTH + x] = 0xFFFFFFFF;
    
    // game loop
    while(state.running)
    {
        processInput(&state);
        renderFrame(&state);
    }

    // quit SDL
    SDL_DestroyWindow(state.window);
    SDL_DestroyRenderer(state.renderer);
    SDL_Quit();
    
    #ifdef __SWITCH__
    closeNxlink();
    #endif

    return 0;
}

