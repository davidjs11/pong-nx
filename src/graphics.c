#include "graphics.h"


u32 getRGBA(u8 r, u8 g, u8 b, u8 a)
{
    return (r << 24) + (g << 16) + (b << 8) + a;
}

void fillBuffer(u32 *framebuffer, u32 color, int width, int height)
{
    for(int x=0; x<width; x++)
        for (int y=0; y<height; y++)
             framebuffer[y*width + x] = color; 
}

void renderPixel(u32 *framebuffer, u32 color, int x, int y,
                 int screenWidth, int screenHeight)
{
    framebuffer[y*SCREEN_WIDTH+x] = color;
}

void renderRect(u32 *framebuffer, u32 color,
                int posX, int posY, int w, int h,
                int screenWidth, int screenHeight)
{
    for (int x=posX; x<posX+w; x++)
        for (int y=posY; y>posY-h; y--)
            if (0 <= x && x < screenWidth && 0 <= y && y < screenHeight)
                framebuffer[y*screenWidth + x] = color;
}
