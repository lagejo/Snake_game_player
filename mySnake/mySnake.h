#ifndef MYSNAKE_H
#define MYSNAKE_H
#define PROFONDEUR_MAX 14

#include <stdio.h>
#include <stdbool.h>


#include "../gameInterface/clientAPI.h"
#include "../gameInterface/snakeAPI.h"


typedef struct cases {
    bool mur_droit;
    bool mur_gauche;
    bool mur_haut;
    bool mur_bas;
    bool serpent;
}cases;

void placer_mur(int* walls,cases** tab_cases,int sizeX,int sizeY, int nbWalls);




#endif