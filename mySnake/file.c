#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "file.h"

#include "../gameInterface/clientAPI.h"
#include "../gameInterface/snakeAPI.h"


#include "arbre.h"
#include "mySnake.h"

file init_file(int x, int y){

    file nouveau = (file)malloc(sizeof(elem_file));
    nouveau->position[0] = x; nouveau->position[1] = y;
    nouveau->suivant = NULL;
    nouveau->precedent = NULL;
    return nouveau;
}

file empiler(file serpent, int x,int y){

    file nouveau = init_file(x,y);
    serpent->suivant = nouveau;
    nouveau->precedent = serpent;
    return nouveau;

}


void depiler(file* serpent, cases** tab_cases){

    if((*serpent)->precedent != NULL) depiler(&((*serpent)->precedent),tab_cases);
    else{
        tab_cases[(*serpent)->position[0]][(*serpent)->position[1]].serpent = 0;
        (*serpent) = NULL;
        free((*serpent));
    }

}


void afficher_serpent(file serpent){
    if(serpent != NULL){
        printf("|x : %d y : %d| --> ",serpent->position[0],serpent->position[1]);
        afficher_serpent(serpent->precedent);
    }
    else{
        printf("queue\n");
    }
}

//le ​joueur 0 (qui joue le premier) commence à la position (2, H/2) et le ​joueur 1​ à la position ​(L-3, H/2)​
file initialiser_serpent(int tour,int sizeX, int sizeY, cases** tab_cases){
    
    if(tour == 0){ 
        tab_cases[2][sizeY/2].serpent = 1;
        return(init_file(2,sizeY/2));
        }

    if(tour == 1){ 
        tab_cases[sizeX - 3][sizeY/2].serpent = 1;
        return(init_file(sizeX - 3, sizeY/2));
        }

}

file agrandir_serpent(file serpent, t_move move,int nb_tour, int* taille_serpent, cases** tab_cases){

    file actuel = (file)malloc(sizeof(elem_file)); actuel = serpent;
    while(actuel->suivant != NULL){
        actuel = actuel->suivant;
    }

    int agrandi = (nb_tour / 10) + 1; //augmente tous les 10 tours, 
    //au début la taille est de 2 or le serpent a déja été initialisé (+1)

    int x,y;
    //nouvelle position du serpent
    if(move==SOUTH){
        x = actuel->position[0];
        y = actuel->position[1] + 1;
    }
    else if(move==NORTH){
        x = actuel->position[0];
        y = actuel->position[1] - 1;
    }
    else if(move==EAST){
        x = actuel->position[0] + 1;
        y = actuel->position[1];
    }
    else{
        x = actuel->position[0] - 1;
        y = actuel->position[1];
    }

    tab_cases[x][y].serpent = 1;
    actuel = empiler(serpent,x,y);


    if((*taille_serpent) < agrandi) (*taille_serpent)++;
    else{
        depiler(&actuel,tab_cases);
    }
    printf("voila\n");afficher_serpent(actuel);

    return actuel;

}

void free_serpent(file* serpent){

    if((*serpent) != NULL){
        free_serpent(&((*serpent)->suivant));
        (*serpent) = NULL;
        free(*serpent);
    }
}




