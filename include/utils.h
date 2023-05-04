#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 180


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

// sdl and game state
typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event;
    u32 *framebuffer;
    bool running;

} gameState;


#endif
