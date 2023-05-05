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

    // temporal position
    int posX = 0, posY = 0;

    gameState state = {0}; 
    initSDL(&state);

    // game loop
    while(state.running)
    {
        getInput(&state);

        state.running = !state.input[BUTTON_START];
        posY += state.input[ARROW_UP] - state.input[ARROW_DOWN];
        posX += state.input[ARROW_RIGHT] - state.input[ARROW_LEFT];

        // clear frame
        for(int x=0; x<SCREEN_WIDTH; x++)
            for (int y=0; y<SCREEN_HEIGHT; y++)
                state.framebuffer[y*SCREEN_WIDTH+x] = 0x000000FF;

        // render the player
        for(int x=posX; x<posX+1; x++)
            for (int y=posY; y<posY+1; y++)
                if (0 <= x && x < SCREEN_WIDTH && 0 <= y && y < SCREEN_HEIGHT)
                    state.framebuffer[y*SCREEN_WIDTH + x] = 0xFF000000;

        renderFrame(&state);
        SDL_Delay(5);
    }

    quitSDL(&state);
    
    #ifdef __SWITCH__
    closeNxlink();
    #endif

    return 0;
}
