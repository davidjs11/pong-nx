#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "game.h"
#include "graphics.h"
#include "inet.h"
#include "sdl.h"
#include "utils.h"
#include "rendering.h"

#ifdef __SWITCH__
#include "switch.h"
#include "nx.h"
#endif


int main(void)
{
    // debugging for switch
#ifdef __SWITCH__
    initNxlink();
#endif

    gameState state = {0}; 
    gameData game = {0};

    initSDL(&state);
    initGame(&game);

    // game loop
    while(state.running)
    {
        // get the input from the user
        getInput(&state);

        // exit the game if requested
        state.running = !state.input[0][BUTTON_START];

        // check for pause 
        /*
        if (state.input[0][BUTTON_PAUSE])
        {
            if (state.readPause)
            {
                state.pause = !state.pause; 
                state.readPause = 0;
            }
        }
        else 
            state.readPause = 1;
        */

        if (!state.input[0][BUTTON_PAUSE])
            state.readPause = 1;
        else
            if (state.readPause)
            {
                state.pause = !state.pause;
                state.readPause = 0;
            }

        // processing and rendering
        if (!state.pause)
        {
            // update players position
            stepGame(&game, &state);

            // render the game into the framebuffer
            renderGame(&game, &state);

            // put framebuffer into the screen
            renderFrame(&state);
        }
    }

    quitSDL(&state);

#ifdef __SWITCH__
    closeNxlink();
#endif

    return 0;
}
