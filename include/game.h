#ifndef GAME_H
#define GAME_H


#include "utils.h"

// int definition
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;

// float vector
typedef struct
{
    float x;
    float y;
} vector;

// ball
typedef struct 
{
    vector pos;
    vector speed;
} ball;

// player
typedef struct
{
    vector pos;
    float speed;
    u8 score;

} player;

// game info
typedef struct
{
    player player[2];
    ball ball;
} gameData;


#endif 
