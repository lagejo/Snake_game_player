#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdbool.h>

#include "mySnake.h"

#include "../gameInterface/clientAPI.h"
#include "../gameInterface/snakeAPI.h"

typedef int contenu;

//la position des serpents est stockée dans une liste doublement chaînée afin d'y naviguer plus facilement
//elle aurait pu être simplement chaînée
typedef struct file{
    struct file* precedent;
    struct file* suivant;
    contenu position[2];
}elem_file;

typedef elem_file* file;

file init_file(int x, int y);

//rajoute un nouvel élément en tête de file et renvoie la position de la nouvelle tête
file empiler(file serpent, int x,int y);

void depiler(file* serpent, cases** tab_cases);

void afficher_serpent(file serpent);

file agrandir_serpent(file serpent, t_move move,int nb_tour, int* taille_serpent, cases** tab_cases);

//place les serpents au début de la partie
file initialiser_serpent(int tour,int sizeX, int sizeY, cases** tab_cases);

void free_serpent(file* serpent);


#endif
