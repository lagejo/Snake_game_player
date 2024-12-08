#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "mySnake.h"
#include "file.h"
#include "../gameInterface/snakeAPI.h"
#include "arbre.h"

void test_placer_mur(int* walls,cases ** tab_cases){

    printf("bas :%d haut: %d gauche: %d droite: %d\n",tab_cases[walls[0]][walls[1]].mur_bas,tab_cases[walls[0]][walls[1]].mur_haut,tab_cases[walls[0]][walls[1]].mur_gauche,tab_cases[walls[0]][walls[1]].mur_droit);
    printf("2 eme case :");
    printf("bas :%d haut: %d gauche: %d droite: %d\n",tab_cases[walls[2]][walls[3]].mur_bas,tab_cases[walls[2]][walls[3]].mur_haut,tab_cases[walls[2]][walls[3]].mur_gauche,tab_cases[walls[2]][walls[3]].mur_droit);

}

void test_walls(int* walls, int nbWalls){

    int testnbwalls = 0;
    int inbWalls = nbWalls*4 ;
    for(int i = 0; i<inbWalls; i++){
            printf(" [");
            printf("%d ",walls[i]);
            testnbwalls += 1;
            printf("] ");
    }
    printf("nb walls :%d testwalls :%d",nbWalls,testnbwalls);
}

cases** creer_tab_2(int sizeX,int sizeY){

    cases ** tab_cases = (cases**)malloc(sizeof(cases*)*sizeX);
    for(int i = 0; i<sizeX; i++){
        tab_cases[i] = (cases*)malloc(sizeY * sizeof(cases));
    }

    if (tab_cases==NULL) printf("Memory allocation failed\n");

    return(tab_cases);
}

void free_arene(cases** tab_cases, int sizeX, int* walls,file* serpent1,file* serpent2){

    free_serpent(serpent1); free_serpent(serpent2);
        
    for(int i = 0;i<sizeX;i++) free(tab_cases[i]);
    
    free(tab_cases);

    free(walls);
}


void debug_tete(cases** tab_cases, int x, int y){

        printf("cases tete serpent\n");
        printf("potition tete : %d %d\n",x,y);
        printf("debug mur bas : %d\n",tab_cases[x][y].mur_bas);
        printf("debug mur haut : %d\n",tab_cases[x][y].mur_haut);
        printf("debug mur gauche : %d\n",tab_cases[x][y].mur_gauche);
        printf("debug mur droit : %d\n\n",tab_cases[x][y].mur_droit);
}

void debug_serpent(cases** tab_cases, int x, int y){

        printf("cases tete serpent\n");
        printf("potition tete : %d %d\n",x,y);
        printf("serpent droite : %d\n",tab_cases[x][y+1].serpent);
        printf("serpent gauche : %d\n",tab_cases[x - 1][y].serpent);
        printf("serpent haut : %d\n",tab_cases[x][y - 1].serpent);
        printf("serpent bas : %d\n\n",tab_cases[x][y + 1].serpent);
}

int secour(cases** tab_cases, int x, int y){

        //haut?
        if((tab_cases[x][y].mur_bas != 1) && (tab_cases[x][y + 1].serpent != 1)){

            return 2;
        }

        //bas ?
        if((tab_cases[x][y].mur_haut != 1) && (tab_cases[x][y - 1].serpent != 1)){

            return 0;
        }

        //droite ?
        if((tab_cases[x][y].mur_droit != 1) && (tab_cases[x + 1][y].serpent != 1)){

            return 1;
        }
        //gauche ?
        if((tab_cases[x][y].mur_gauche != 1) && (tab_cases[x - 1][y].serpent != 1)){

            return 3;
        }
        else{
            printf("bloqué!!\n");
        }

}