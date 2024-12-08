#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "arbre.h"


#include "../gameInterface/clientAPI.h"
#include "../gameInterface/snakeAPI.h"

arbre creer_noeud(int x, int y){

    arbre a = (arbre)malloc(sizeof(elem_arbre_4));
    if(a==NULL) printf("Mem fail\n");
    a->bas = NULL;
    a->haut = NULL;
    a->droit = NULL;
    a->gauche = NULL;
    a->parent = NULL;
    a->profondeur = 0;
    a->position[0] = x; a->position[1] = y;

    return a;

}

void creer_fils(arbre* a, int x, int y, type_fils fils, int profondeur){

    switch (fils){
        case HAUT:
            (*a)->haut = creer_noeud(x,y);
            (*a)->haut->position[0] = x;
            (*a)->haut->position[1] = y;
            (*a)->haut->profondeur = profondeur;
            (*a)->haut->parent = *a;
            break;

        case BAS:
            (*a)->bas = creer_noeud(x,y);
            (*a)->bas->position[0] = x;
            (*a)->bas->position[1] = y;
            (*a)->bas->profondeur = profondeur;
            (*a)->bas->parent = *a;
            break;

        case GAUCHE:
            (*a)->gauche = creer_noeud(x,y);
            (*a)->gauche->position[0] = x;
            (*a)->gauche->position[1] = y;
            (*a)->gauche->profondeur = profondeur;
            (*a)->gauche->parent = *a;
            break;

        case DROIT:
            (*a)->droit = creer_noeud(x,y);
            (*a)->droit->position[0] = x;
            (*a)->droit->position[1] = y;
            (*a)->droit->profondeur = profondeur;
            (*a)->droit->parent = *a;
            break;

        default:
            printf("Mauvaise valeur de fils rentrée !\n");
    }
}

arbre rechercher_noeud(arbre a, int x, int y){

    if(a == NULL)  return NULL;

    if((a->position[0] == x) && (a->position[1]) == y) return a;

    arbre resultat;
    resultat = rechercher_noeud(a->parent, x, y);

    if(resultat != NULL) return resultat;
    
}

void free_arbre(arbre* a){

    if((*a) != NULL){
        free_arbre(&((*a)->bas));
        free_arbre(&((*a)->haut));
        free_arbre(&((*a)->droit));
        free_arbre(&((*a)->gauche));
        (*a) = NULL;
        free((*a));

    }

}

void afficher_arbre(arbre* a){

    if((*a) != NULL){  
        afficher_arbre(&(*a)->bas);
        afficher_arbre(&(*a)->haut);
        afficher_arbre(&(*a)->droit);
        afficher_arbre(&(*a)->gauche);

        printf("x = %d y = %d \n",(*a)->position[0], (*a)->position[1]);
    }
}

void afficher_chemin(arbre destination){

    if(destination->parent != NULL) afficher_chemin(destination->parent);

    printf("%d %d --> ",destination->position[0],destination->position[1]);
}


int prochain_coup(file final, cases** tab_cases){

    int prochain = 12;
    int coord[2];
    int x = final->precedent->precedent->position[0]; int y = final->precedent->precedent->position[1];
    coord[0] = final->precedent->position[0]; coord[1] = final->precedent->position[1]; //tete

    if((coord[0] - x) == -1)  prochain = 1; //east

    if((coord[0] - x) == 1)   prochain = 3; //west
    
    if((coord[1] - y) == -1)  prochain = 2; //south

    if((coord[1] - y) == 1)  prochain = 0; //north


    return prochain;

}

//en se basant sur une feuille de l'arbre vérifie qu'il n'y a pas de parent dans lequel
//la valeur a déjà été stcockée, permet d'éviter de tourner en rond
bool verif_presence(arbre a, int x, int y){

    int valeur = 0;
    arbre temp = (arbre)malloc(sizeof(elem_arbre_4));
    temp = a;
    while(temp != NULL){
        if((temp->position[0]==x) && (temp->position[1] == y)) valeur = 1;
        temp = temp->parent;
    }
    free_arbre(&temp);
    return valeur;
}

//fonction de coloriage qui génère un arbre des possibilités, x et y sont les coordonées de départ
//les critères d'arrêt sont la profondeur, la présence de murs et des deux serpents
void creer_arbre(int x, int y, arbre* a, cases** tab_cases, int sizeX, int sizeY,int profondeur){

    if((profondeur < PROFONDEUR_MAX)){    

        if((tab_cases[x][y].mur_bas != 1) && (tab_cases[x][y + 1].serpent != 1) && (verif_presence(*a,x,y + 1) != 1) ){

            creer_fils(a, x, y + 1, BAS,profondeur);
            creer_arbre(x, y + 1, &((*a)->bas), tab_cases,sizeX,sizeY, profondeur + 1);

        }

        //possible d'aller en haut ?
        if((tab_cases[x][y].mur_haut != 1) && (tab_cases[x][y - 1].serpent != 1) && (verif_presence(*a,x,y - 1) != 1)){

            creer_fils(a, x, y - 1, HAUT,profondeur);
            creer_arbre(x, y - 1, &((*a)->haut), tab_cases,sizeX,sizeY,profondeur + 1);

        }

        //possible d'aller à droite ?
        if((tab_cases[x][y].mur_droit != 1) && (tab_cases[x + 1][y].serpent != 1) && (verif_presence(*a,x + 1,y) != 1)){

            creer_fils(a, x + 1, y, DROIT,profondeur);
            creer_arbre(x + 1, y, &((*a)->droit), tab_cases,sizeX,sizeY, profondeur + 1);

        }

        //possible d'aller à gauche ?
        if((tab_cases[x][y].mur_gauche != 1) && (tab_cases[x - 1][y].serpent != 1) && (verif_presence(*a,x - 1,y) != 1)){

            creer_fils(a, x - 1, y, GAUCHE,profondeur);
            creer_arbre(x - 1, y, &((*a)->gauche), tab_cases,sizeX,sizeY,profondeur + 1);

        }
    }
}


int meilleur_coup(arbre complet, int profondeur, cases** tab_cases){

    int meuilleur; 

    arbre final = rechercher_profondeur(complet,profondeur);

    //tant que la recherche n'a pas donné de résultat, relance la recherche à une profondeur différente
    int reduction = 0;
    while((final== NULL) && (reduction < profondeur)){

        final = rechercher_profondeur(complet,profondeur - reduction);
        reduction++;
    }

    if(final != NULL){

        file bon_final = arbre_final(final);
        meuilleur = prochain_coup(bon_final,tab_cases);
        free_serpent(&bon_final); free_arbre(&final);

    }
    else{

        printf("echec de la recherche...\n");

        meuilleur = secour(tab_cases,complet->position[0],complet->position[1]);
        }

    return meuilleur;
}


arbre rechercher_profondeur(arbre a,int profondeur){

        if(a == NULL)  return NULL;

        if((a->profondeur) == profondeur) return a;

        arbre resultat;
        resultat = rechercher_profondeur(a->bas, profondeur);
        if(resultat == NULL) resultat = rechercher_profondeur(a->haut,profondeur);
        if(resultat == NULL) resultat = rechercher_profondeur(a->droit,profondeur);
        if(resultat == NULL) resultat = rechercher_profondeur(a->gauche,profondeur);
        if(resultat != NULL) return resultat;

}

file arbre_final(arbre destination){

    arbre temp = (arbre)malloc(sizeof(elem_arbre_4));
    file file_temp = (file)malloc(sizeof(elem_file));

    temp = destination;
    file final = init_file(destination->position[0],destination->position[1]);

    while(temp->parent != NULL){
        temp = temp->parent;
        file_temp = empiler(final,temp->position[0],temp->position[1]);
        final = file_temp;
    }

    free_arbre(&temp); free_serpent(&file_temp);

    return final;
}
