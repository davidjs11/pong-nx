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

// font size
#define FONT_WIDTH  4
#define FONT_HEIGHT 8

// player size
#define PLAYER_WIDTH  10
#define PLAYER_HEIGHT 60
#define BALL_SIZE 5

// global input index
#define PLAYER_ID    0
#define ARROW_UP     1
#define ARROW_DOWN   2
#define ARROW_LEFT   3 
#define ARROW_RIGHT  4
#define BUTTON_A     5
#define BUTTON_B     6
#define BUTTON_START 7
#define BUTTON_PAUSE 8
#define INPUTSIZE 9

// int definition
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;


typedef struct
{
    i16 posX, posY;
    i16 speedX, speedY;
    i16 width, height;
    u8 score;

} body;

// game info
typedef struct
{
    body player[2];
    body ball;
    u8 gameSpeed;

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
    u8 running;
    u8 pause, readPause;
} gameState;


#endif
