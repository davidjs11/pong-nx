#include "game.h"
    // pansio mira y juega Dwarf Fortress!!!!!
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
    game->ball.width = BALL_SIZE;
    game->ball.height = BALL_SIZE;
    game->ball.speedX = -1;
    game->ball.speedY = 1;
    game->ball.score = 0; // ball score is for touch counting

    // other
    game->gameSpeed = 1;
}

void stepGame(gameData *game, gameState *state)
{
    body *player = game->player;
    body *ball = &(game->ball);
    u8 collisionX = 0, collisionY = 0;
    u8 rightBorder = 0, leftBorder = 0;

    // update player position
    for(int i=0; i<2; i++)
    {
        player[i].posY +=
            (player[i].posY < SCREEN_HEIGHT) *
            player[i].speedY * state->input[i][ARROW_UP];
        player[i].posY -=
            (player[i].posY-player[i].height > 0) *
            player[i].speedY * state->input[i][ARROW_DOWN];
    }

    // oh no; it's ball movement time

    // check collision with players
    // player 1
    if (ball->posX <= player[0].posX+player[0].width)
    {
        collisionX +=
            (ball->posX == player[0].posX+player[0].width)
        &&  ball->posY >= player[0].posY-player[0].height
        &&  ball->posY-ball->height <= player[0].posY;

        collisionY +=
            ball->posX+ball->width >= player[0].posX
        &&  ball->posX <= player[0].posX+player[0].width
        && (ball->posY == player[0].posY-player[0].height
        ||  ball->posY-ball->height == player[0].posY);
    }

    // player 2
    if (ball->posX+ball->width >= player[1].posX)
    {
        collisionX +=
            (ball->posX+ball->width == player[1].posX)
        &&  ball->posY >= player[1].posY-player[1].height
        &&  ball->posY-ball->height <= player[1].posY;

        collisionY +=
            ball->posX+ball->width >= player[1].posX
        &&  ball->posX <= player[1].posX+player[1].width
        && (ball->posY == player[1].posY-player[1].height
        ||  ball->posY-ball->height == player[1].posY);
    }

    // check collision with top and bottom screen borders 
    collisionY += (ball->posY >= SCREEN_HEIGHT);
    collisionY += (ball->posY <= 0);
    
    // collision with screen borders
    leftBorder = (ball->posX <= 0);
    rightBorder = (ball->posX >= SCREEN_WIDTH);

    // update score if a player loses
    if (leftBorder || rightBorder)
    {
        player[0].score += rightBorder;
        player[1].score += leftBorder;
        ball->posX = SCREEN_WIDTH/2;
        ball->posY = SCREEN_HEIGHT/2;
        ball->speedX = leftBorder - rightBorder;
        ball->speedY = -ball->speedY;
        game->gameSpeed = 1;
    }

    // update touch counter and game speed
    ball->score += collisionX;
    if (collisionX && ball->score%3 == 2)
        game->gameSpeed += (game->gameSpeed < 7);

    // change ball direction if a collision is detected
    if (collisionX)
        ball->speedX = -ball->speedX;
    if (collisionY)
        ball->speedY = -ball->speedY;

    // update ball position
    ball->posX += ball->speedX;
    ball->posY += ball->speedY;

    SDL_Delay(10-game->gameSpeed);
}
