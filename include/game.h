#ifndef GAME_H
#define GAME_H

#include "utils.h"

// initializes a gameData structure
void initGame(gameData *game);

// checks if two objects are colliding
u8 checkCollision(body *a, body *b);

// move an object given a direction 
void moveObject(body *obj, float dirX, float dirY);

// calculate next game state
void stepGame(gameData *game, gameState *state);

// check for pause
void checkPause(gameData *game, gameState *state);

#endif 
