#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

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

    // game related structures
    gameState state = {0}; 
    gameData game = {0};

    // time related values
    u32 t_start, t_end, fps = 60; 

    // init everything
    initSDL(&state);
    initGame(&game);

    // game loop
    while(state.running)
    {
        // get global timer at start
        t_start = SDL_GetPerformanceCounter();

        // get the input from the user
        getInput(&state);

        // exit the game if requested
        state.running = !state.input[0][BUTTON_START];

        // check for pause
        checkPause(&game, &state);

        // processing and rendering
        if (!state.pause)
        {
            // process the next game state
            for(int i=0; i<game.gameSpeed; i++)
                stepGame(&game, &state);

            // render the game into the framebuffer
            renderGame(&game, &state);

            // put framebuffer into the screen
            renderFrame(&state);
        }
        else
        {
            renderPause(&state);
            renderFrame(&state);
        }

        // get global timer at finish 
        t_end = SDL_GetPerformanceCounter();

        // cap game to selected fps
        SDL_Delay(1000/fps
            -1000*(t_end-t_start)/(float)SDL_GetPerformanceFrequency());
    }

    quitSDL(&state);

#ifdef __SWITCH__
    closeNxlink();
#endif

    return 0;
}
