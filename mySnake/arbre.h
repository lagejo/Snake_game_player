#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>

#include "annex.h"
#include "mySnake.h"
#include "file.h"

#include "../gameInterface/clientAPI.h"
#include "../gameInterface/snakeAPI.h"

typedef int contenu;

// Arbre des possibilités, rempli par la fonction de coloriage
//  Cet arbre à 4 branches aurait pu être à 3 branches uniquement, étant donné qu'il n'y a au maximum
// que trois possibilités de déplacement, mais je trouvais cela plus compréhensible pour me repérer dans mon arbre
// d'indiquer la direction du chemin à travers l'arbre.
typedef struct arbre_4{
    struct arbre_4* haut;
    struct arbre_4* bas;
    struct arbre_4* gauche;
    struct arbre_4* droit;
    struct arbre_4* parent;
    int profondeur;
    contenu position[2];        
    //la position est contenue sous la forme d'un tableau 1d de 2 éléments
    // en 0 x et en 1 y
}elem_arbre_4;

typedef elem_arbre_4* arbre;

typedef enum{
    HAUT = 0,
    BAS = 1,
    GAUCHE = 2,
    DROIT = 3
}type_fils;


arbre creer_noeud(int x, int y);

void free_arbre(arbre* a);

void afficher_arbre(arbre* a);

//utile dans la fonction chemin pour insérer des éléments à l'arbre, x et y étant la position de la case
void creer_fils(arbre* a, int x, int y,type_fils fils, int profondeur);


//trouve dans l'arbre le chemin pour atteindre la destination 
arbre rechercher_noeud(arbre a, int x, int y);


//Renvoie le premier coup pour s'y rendre, x et y coordonnées de départ
int prochain_coup(file final,cases** tab_cases);


//fonction de coloriage qui génère un arbre des possibilités, x et y sont les coordonées de départ
void creer_arbre(int x, int y, arbre* a, cases** tab_cases, int sizeX, int sizeY,int profondeur);


//vérifie la présence d'un noeud dans un arbre, permet à la fonction de coloriage de ne pas tourner en rond
bool verif_presence(arbre a, int x, int y);


//affiche tous les parents d'un noeud, utilisé pour vérifier la validité des autres programmes
void afficher_parent(arbre a);


//en se basant sur l'arbre des possibilités et la profondeur souhaitée, calcule le meilleur coup
int meilleur_coup(arbre complet, int profondeur, cases** tab_cases);


//dans l'abre issu de la fonction de coloriage, trouve un noeud à une profondeur voulue et le renvoie
arbre rechercher_profondeur(arbre a,int profondeur);


//traitement du résulat de la recherche en profondeur, le transforme en une file afin de traiter plus facilement les informations qu'il contient
file arbre_final(arbre destination);


#endif