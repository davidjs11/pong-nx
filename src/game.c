#include "game.h"

void initGame(gameData *game)
{
    // player
    game->player[0].posX = (SCREEN_WIDTH/PLAYER_WIDTH);
    game->player[1].posX = (SCREEN_WIDTH/PLAYER_WIDTH)*(PLAYER_WIDTH-1);
    for(int i=0; i<2; i++)
    {
        game->player[i].posY = SCREEN_HEIGHT/2+PLAYER_HEIGHT/2;
        game->player[i].width = PLAYER_WIDTH;
        game->player[i].height = PLAYER_HEIGHT;
        game->player[i].speedX = 0;
        game->player[i].speedY = 2;
    }

    // ball
    game->ball.posX = SCREEN_WIDTH/2;
    game->ball.posY = SCREEN_HEIGHT/2;
    game->ball.speedX = 1;
    game->ball.speedY = 1;
}

u8 checkCollision(body *a, body *b)
{
    u8 collision = false;
    // need to rewrite this
    return collision;
}

void moveObject(body *obj, i8 dirX, i8 dirY)
{
    obj->posX += obj->speedX * dirX;
    obj->posY += obj->speedY * dirY;
}
