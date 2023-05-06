#ifndef GAME_H
#define GAME_H

#include "utils.h"

// initializes a gameData structure
void initGame(gameData *game);

// checks if two objects are colliding
u8 checkCollision(body *a, body *b);

// move an object given a direction 
void moveObject(body *obj, i8 dirX, i8 dirY);

#endif 
