#include "rendering.h"
#include "font.h"

void renderGame(gameData *data, gameState *state)
{
    // clear the screen
    fillBuffer(state->framebuffer, 0x000000FF,
               SCREEN_WIDTH, SCREEN_HEIGHT);

    // draw a line in the center
    for(int y=5; y<SCREEN_HEIGHT; y+=5)
        renderPixel(state->framebuffer, 0xFFFFFFFF,
                    SCREEN_WIDTH/2, y,
                    SCREEN_WIDTH, SCREEN_HEIGHT);

    // render the player
    for (int i=0; i<2; i++)
        renderRect(state->framebuffer, 0xFFFFFFFF,
               data->player[i].posX,
               data->player[i].posY,
               data->player[i].width, data->player[i].height,
               SCREEN_WIDTH, SCREEN_HEIGHT);

    renderRect(state->framebuffer, 0xFFFFFFFF,
               data->ball.posX,
               data->ball.posY,
               data->ball.width, data->ball.height,
               SCREEN_WIDTH, SCREEN_HEIGHT);

    renderDigit(state->framebuffer, 0xFFFFFFFF, data->player[0].score,
                digitFont, 50, 50, 2, 2, SCREEN_WIDTH, SCREEN_HEIGHT);

}
