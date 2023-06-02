#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "game.h"
#include "graphics.h"
#include "sdl.h"
#include "utils.h"
#include "rendering.h"
#include "easyTCP.h"

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
    u32 t_start = 0, t_end = 0;

    // init everything
    initSDL(&state);
    initGame(&game);

    // online stuff
    char *ip = "192.168.1.144";
    struct socketInfo server;
    connectToServer(&server, ip, 3476);

    u8 tmpInput[INPUTSIZE*2];

    // game loop
    while(state.running)
    {
        t_start = SDL_GetPerformanceCounter(); // get global timer

        // exit the game if requested
        state.running = !(state.input[BUTTON_START]
                       || state.input[INPUTSIZE+BUTTON_START]);

        // get the input from the user
        getInput(&state);

        printf("\ninp: ");
        for(int i=0; i<18; i++)
            printf("%u", state.input[i]);
        printf("\n");

        // send data to server
        sendMessage(&server, (char *) state.input,
                    2*INPUTSIZE);

        // get data from the server
        recvMessage(&server, (char *) tmpInput,
                   2*INPUTSIZE);

        // mix both player inputs in global input buffer
        for(int i=0; i<2*INPUTSIZE; i++)
            state.input[i] = (state.input[i] | tmpInput[i]);

        printf("net: ");
        for(int i=0; i<18; i++)
            printf("%u", tmpInput[i]);
        printf("\n");

        // check for pause
        //checkPause(&game, &state);

        // processing and rendering
        if (!state.pause)
        {
            // process the next game state
            for(int i=0; i<game.gameSpeed; i++)
                stepGame(&game, &state);

            // render the game into the framebuffer
            renderGame(&game, &state);
        }
        else
            renderPause(&state);

        // put framebuffer into the screen
        renderFrame(&state);


        t_end = SDL_GetPerformanceCounter(); // get global timer
        

        SDL_Delay(
            16.666f -
            1000*(t_end-t_start)/(float)SDL_GetPerformanceFrequency());
    }

    disconnectFromServer(&server);
    quitSDL(&state);

#ifdef __SWITCH__
    closeNxlink();
#endif

    return 0;
}
