#ifndef GRAPH_H
#define GRAPH_H
#include "utils.h"

// convert separated 8-bits colors into a 32-bit RGBA color
u32 getRGBA(u8 r, u8 g, u8 b, u8 a);

// fills the framebuffer in a selected color
void fillBuffer(u32 *framebuffer, u32 color, int width, int height);

void renderPixel(u32 *framebuffer, u32 color, int x, int y, int screenWidth, int screenHeight);

// render a rectangle in the framebuffer
void renderRect(u32 *framebuffer, u32 color,
                int posX, int posY, int w, int h,
                int screenWidth, int screenHeight);

// render a single digit using a bitmap font
void renderDigit(u32 *framebuffer, u32 color,
                  u8 digit, u8 *font,
                  int posX, int posY, int w, int h,
                  int screenWidth, int screenHeight);

#endif
