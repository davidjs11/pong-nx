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
    printf("connected to switch!\n");
    #endif

    // temporal position
    int posX = 0, posY = 0;

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
        state.running = !state.input[BUTTON_START];

        // update players position
        game.player[0].posY +=
            state.input[ARROW_UP] - state.input[ARROW_DOWN];
        game.player[1].posY +=
            state.input[ARROW_UP] - state.input[ARROW_DOWN];

        renderGame(&game, &state);

        renderFrame(&state);
        SDL_Delay(5);
    }

    quitSDL(&state);
    
    #ifdef __SWITCH__
    closeNxlink();
    #endif

    return 0;
}
