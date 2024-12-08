#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "gameInterface/snakeAPI.h"

#include "mySnake/mySnake.h"
#include "mySnake/arbre.h" 
#include "mySnake/annex.h"
#include "mySnake/file.h"

//Il y a beaucoup de variables globales
//Je n'ai pas voulu les mettre dans une sructure pour ne pas surcharger mon code
int sizeX, nbWalls, sizeY, tour;
char gameName[50];
char gameType[150]= "TRAINING SUPER_PLAYER";
int taille_serpent_ally, taille_serpent_ennemi, nb_tour = 0;
t_return_code move_adv,etat_joueur;
t_move move;

int main()
{
    printf("start \n");
    connectToServer("localhost", 3456,"Jo");

    int state_game = 1;

    //déroulement du jeu
    t_move monmove = SOUTH;
    waitForSnakeGame(gameType,gameName, &sizeX, &sizeY, &nbWalls);

    //Allocation dynamique du tableau contenant l'emplacement des mur, chaque mur a 4 coordonnées
    int* walls = (int*)malloc(sizeof(int)*nbWalls*4); 

    tour = getSnakeArena(walls);

    //création de la structure contenant l'emplacement des murs
    cases** tab_cases = creer_tab_2(sizeX,sizeY);
    placer_mur(walls,tab_cases,sizeX,sizeY,nbWalls); 

    //prise en compte de l'emplacement de départ des serpents alliés et ennemis
    file snake = initialiser_serpent(tour,sizeX,sizeY, tab_cases);
    file snake_ennemi =initialiser_serpent((tour^1),sizeX,sizeY, tab_cases); //toggle tour 


    while(state_game==1){
        printArena();

        //initialisation de l'arbre des possibilités à la tête du serpent
        arbre chemins = creer_noeud(snake->position[0],snake->position[1]);
        //création d'un parent pour pouvoir utiliser la fonction creer arbre, ce parent ne servira pas, -15, -15 est une valeur arbitraire
        chemins->parent = creer_noeud(-15,-15);

        //crée l'arbre des possibilités 
        creer_arbre(snake->position[0],snake->position[1],&chemins,tab_cases,sizeX,sizeY,0);  

        if(chemins == NULL) printf("chemins nul\n");

        //calcul du meilleur coup
        monmove = meilleur_coup(chemins,PROFONDEUR_MAX,tab_cases);
        
        //prise en compte de l'ordre des joueurs
        if(tour==1){
        move_adv = getMove(&move);
        etat_joueur = sendMove(monmove);
        }
        else{
            etat_joueur = sendMove(monmove);
            move_adv = getMove(&move);
        }

        //prise en compte de l'évolution de la taille des serpents
        file snake_temp = agrandir_serpent(snake,monmove,nb_tour,&taille_serpent_ally,tab_cases);
        snake = snake_temp;
        file snake_ennemi_temp = agrandir_serpent(snake_ennemi,move,nb_tour,&taille_serpent_ennemi,tab_cases);
        snake_ennemi = snake_ennemi_temp;


        if(etat_joueur== -1){
            printf("perdu...\n");

            state_game = 0;
            closeConnection();
        }
        if(move_adv == -1){
            printf("Gagné !!\n");

            state_game = 0;
            closeConnection();
        }

        nb_tour++;
        free_arbre(&chemins);
        free_serpent(&snake_ennemi_temp); free_serpent(&snake_temp);

    }

    free_arene(tab_cases,sizeX,walls,&snake,&snake_ennemi);
    closeConnection();
    exit(0);

}

