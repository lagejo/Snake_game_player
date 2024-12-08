#ifndef ANNEX_H
#define ANNEX_H

#include <stdio.h>
#include <stdbool.h>
#include "arbre.h"
#include "file.h"
#include "mySnake.h"

#include "../gameInterface/clientAPI.h"
#include "../gameInterface/snakeAPI.h"

void test_placer_mur(int* walls,cases ** tab_cases);

void test_walls(int* walls, int nbWalls);

cases** creer_tab_2(int sizeX,int sizeY);

void free_arene(cases** tab_cases, int sizeX, int* walls, file* serpent1, file* serpent2);

void debug_tete(cases** tab_cases, int x, int y);

void debug_serpent(cases** tab_cases, int x, int y);

int secour(cases** tab_cases, int x, int y);

#endif