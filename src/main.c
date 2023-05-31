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
    u32 t_start = 0, t_end = 0;

    // init everything
    initSDL(&state);
    initGame(&game);

    // online stuff
    char *ip = "192.168.1.144";
    socketInfo server, client;
    server = resolveHost(ip, 3475);
    setSocketTimeout(server.socket);
    client = server;

    // init everything
    initSDL(&state);
    initGame(&game);

    // game loop
    while(state.running)
    {
        t_start = SDL_GetPerformanceCounter(); // get global timer

        // exit the game if requested
        state.running = !(state.input[0][BUTTON_START]
                       || state.input[1][BUTTON_START]);

        // get the input from the user
        getInput(&state);

        // send data to server
        sendMessage(&server, &client,
                    (char *) state.input[0],
                    2*INPUT_BUFFER_SIZE);
        sendMessage(&server, &client,
                    (char *) state.input[1],
                    INPUT_BUFFER_SIZE);

        /*
        // get data from the server
        getMessage(&client, &server,
                   (char *) *state.input, 2*INPUT_BUFFER_SIZE);
        */

        printf("net: ");
        for(int i=0; i<18; i++)
            printf("%u", state.input[0][i]);
        printf("\n");

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

    quitSDL(&state);

#ifdef __SWITCH__
    closeNxlink();
#endif

    return 0;
}
