/*
 * deplacement.h
 *
 *  Created on: 10 oct. 2016
 *      Author: cleme
 */
#include "include.h"
#ifndef DEPLACEMENT_H_
#define DEPLACEMENT_H_
perso deplacement_chemin(sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom, SDL_Rect coord);
perso deplacement_personnage(sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom, SDL_Rect coord);
perso ramasse_objets(sol tab[COL][LIG], perso perso, int zoom);
#endif /* DEPLACEMENT_H_ */
