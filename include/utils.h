#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// video resolution
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 180

// player size
#define PLAYER_WIDTH  10 
#define PLAYER_HEIGHT 60

// global input index
#define ARROW_UP     0
#define ARROW_DOWN   1
#define ARROW_LEFT   2 
#define ARROW_RIGHT  3
#define BUTTON_A     4
#define BUTTON_B     5
#define BUTTON_START 6
#define INPUT_BUFFER_SIZE 7

// int definition
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;


/*
// 16-bit int 2D vector
typedef struct
{
    i16 x;
    u16 y;

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
    u8 speed;
    u8 score;

} player;
*/

typedef struct
{
    i16 posX;
    i16 posY;
    i16 speedX;
    i16 speedY;

} body;

// game info
typedef struct
{
    body player[2];
    body ball;

} gameData;

// sdl and game state
typedef struct
{
    // video stuff
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    u32 *framebuffer;

    // input stuff
    SDL_Event event;
    u8 *input;
    SDL_Joystick *joysticks[4];

    // game stuff
    bool running;

} gameState;


#endif
