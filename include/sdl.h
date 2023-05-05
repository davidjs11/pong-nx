#ifndef SDL_H
#define SDL_H 

#include "utils.h"

// inits SDL and saves the info in the gameState structure
int initSDL(gameState *state);

// quits SDL (wow)
void quitSDL(gameState *state);

// renders the framebuffer into the screen
void renderFrame(gameState *state);

// saves the input in an array for a better input system
void getInput(gameState *state);

#endif
