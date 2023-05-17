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
    u32 t_start, t_end;

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
        if (!state.input[0][BUTTON_PAUSE])
            state.readPause = 1;
        else if (state.readPause)
        {
            state.pause = !state.pause;
            renderPause(&game, &state);
            renderFrame(&state);
            state.readPause = 0;
        }

        // processing and rendering
        if (!state.pause)
        {
            // process the next game state
            stepGame(&game, &state);

            // render the game into the framebuffer
            renderGame(&game, &state);

            // put framebuffer into the screen
            renderFrame(&state);
        }

        // get global timer at finish 
        t_end = SDL_GetPerformanceCounter();

        // cap game to 60 fps
        SDL_Delay(16.666f - 1000*(t_end-t_start)/(float)SDL_GetPerformanceFrequency());
    }

    quitSDL(&state);

#ifdef __SWITCH__
    closeNxlink();
#endif

    return 0;
}
