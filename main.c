#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "snakeAPI.h"

int sizeX, nbWalls, sizeY, walls, state_game, monmove;
char gameName[50];
char gameType[50];
t_move* move;
//gameName = "Training <BOT>";
// sizeX = 20;
// sizeY = 20;
// nbWalls = 50;
int main()
{
        // closeConnection();
    connectToServer("localhost", 1234,"potato");
    //déroulement du jeu
    state_game = 1;
    monmove = 0;
    while(state_game==1){

        waitForSnakeGame("TRAINING SUPER_PLAYER",gameName, &sizeX, &sizeY, &nbWalls);
        getSnakeArena(&walls);
        printArena();
        if(getMove(move)== LOSING_MOVE || sendMove(monmove)== LOSING_MOVE){
            state_game = 0;
        }
        sendMove(monmove);


    }

    closeConnection();
}