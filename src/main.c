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
        state.running = !state.input[BUTTON_START];

        // update players position
        moveObject(&game.player[0], 0,
                    (game.player[0].posY <= SCREEN_HEIGHT)
                        * state.input[ARROW_UP]
                  - (game.player[0].posY-game.player[0].height >= 0)
                        * state.input[ARROW_DOWN]);

        moveObject(&game.ball, 1, 1);

        printf("collision %d\n", checkCollision(&(game.player[0]), &(game.player[1])));

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
