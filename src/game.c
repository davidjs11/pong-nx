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
    game->ball.speedX = -2;
    game->ball.speedY = 2;
}

u8 checkCollision(body *a, body *b)
{
    u8 tmp = 0;
    return tmp;
}

void moveObject(body *obj, float dirX, float dirY)
{
}


void stepGame(gameData *game, gameState *state)
{
    body *player = game->player;
    body *ball = &(game->ball);
    u8 collisionX = 0, collisionY = 0;

    // update player position
    for(int i=0; i<2; i++)
    {
        player[i].posY +=
            (player[i].posY < SCREEN_HEIGHT) *
            player[i].speedY * state->input[ARROW_UP];
        player[i].posY -=
            (player[i].posY-player[i].height > 0) *
            player[i].speedY * state->input[ARROW_DOWN];
    }


    // oh no; it's ball movement time
    for (int i=0; i<2; i++)
        collisionX +=
            (ball->posX <= player[i].posX+player[i].width
        &&  ball->posX >= player[i].posX
        &&  ball->posY >= player[i].posY-player[i].height
        &&  ball->posY <= player[i].posY);

    collisionY += (ball->posY >= SCREEN_HEIGHT);
    collisionY += (ball->posY <= 0);

    printf("Y%d\n", collisionY);
    
    if (collisionX)
        ball->speedX = -ball->speedX;
    if (collisionY)
        ball->speedY = -ball->speedY;

    ball->posX += ball->speedX;
    ball->posY += ball->speedY;
}
