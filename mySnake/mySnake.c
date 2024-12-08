#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "mySnake.h"
#include "../gameInterface/snakeAPI.h"
#include "arbre.h"



void placer_mur(int* walls,cases** tab_cases,int sizeX,int sizeY,int nbWalls){

    //placer les bordures de l'arène
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){

            if(i == 0) tab_cases[i][j].mur_gauche = 1;

            if(i == (sizeX - 1)) tab_cases[i][j].mur_droit = 1;

            if(j == 0) tab_cases[i][j].mur_haut = 1;

            if(j == (sizeY - 1)) tab_cases[i][j].mur_bas = 1;
            
            
        }
    }

    //Puis prendre en compte l'emplacement des murs
    for(int i = 0; i < nbWalls*4; i+=4){
        // walls contient l'emplacement des mur sous cette forme: (case1.x, case1.y, case2.x, case2.y)
        if((walls[i] - walls[i + 2]) == -1){
            tab_cases[walls[i]][walls[i + 1]].mur_droit = 1; //par rapport à la case 1
            tab_cases[walls[i + 2]][walls[i + 3]].mur_gauche = 1; //case 2
        } 
        if((walls[i] - walls[i + 2]) == 1){
            tab_cases[walls[i]][walls[i + 1]].mur_gauche = 1; 
            tab_cases[walls[i + 2]][walls[i + 3]].mur_droit = 1;
        } 
        if((walls[i + 1] - walls[i + 3]) == -1){
            tab_cases[walls[i]][walls[i + 1]].mur_bas = 1; 
            tab_cases[walls[i + 2]][walls[i + 3]].mur_haut = 1;
        } 
        if((walls[i + 1] - walls[i + 3]) == 1){
            tab_cases[walls[i]][walls[i + 1]].mur_haut = 1; 
            tab_cases[walls[i + 2]][walls[i + 3]].mur_bas = 1;
        } 
    }

//initialisation des autres éléments
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            if(tab_cases[i][j].mur_bas != 1) tab_cases[i][j].mur_bas = 0;
            if(tab_cases[i][j].mur_haut != 1) tab_cases[i][j].mur_haut = 0;
            if(tab_cases[i][j].mur_droit != 1) tab_cases[i][j].mur_droit = 0;
            if(tab_cases[i][j].mur_gauche != 1) tab_cases[i][j].mur_gauche = 0;
            tab_cases[i][j].serpent = 0;
        }
    }
}


