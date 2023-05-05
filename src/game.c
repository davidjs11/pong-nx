#include "game.h"

void initGame(gameData *game)
{
    // player position
    game->player[0].posX = (SCREEN_WIDTH/PLAYER_WIDTH);
    game->player[1].posX = (SCREEN_WIDTH/PLAYER_WIDTH)*(PLAYER_WIDTH-1);
    game->player[0].posY = SCREEN_HEIGHT/2+PLAYER_HEIGHT/2;
    game->player[1].posY = SCREEN_HEIGHT/2+PLAYER_HEIGHT/2;

    // player speed
    game->player[0].speedX = 2;
    game->player[1].speedY = 2;

    // initialize ball position
    game->ball.posX = SCREEN_WIDTH/2;
    game->ball.posY = SCREEN_HEIGHT/2;

    // ball speed
    game->ball.speedX = 1;
    game->ball.speedY = 1;
}
