/*
 * deplacement.h
 *
 *  Created on: 10 oct. 2016
 *      Author: cleme
 */

#ifndef DEPLACEMENT_H_
#define DEPLACEMENT_H_

#include "include.h"

void deplacement_chemin(sol tab[COL][LIG], SDL_Surface *screen,SDL_Rect *rcDepla,
		SDL_Rect rcDeplaS, liste_point *L, int buttx, int butty, NODE node[COL][LIG], int *cond, int zoom);

void deplacement_personnage(sol tab[COL][LIG], SDL_Surface *screen,SDL_Rect *rcDepla,
		SDL_Rect rcDeplaS, liste_point *L, int buttx, int butty, NODE node[COL][LIG], int *cond, int zoom);

void deplacement_constr(sol tab[COL][LIG], SDL_Surface *screen,SDL_Rect *rcDepla,
		SDL_Rect rcDeplaS, int buttx, int butty, NODE node[COL][LIG],int *condBuild, liste_point *L, int zoom);


void constr_chemin(sol tab[COL][LIG], SDL_Surface *screen,SDL_Rect *rcDepla, SDL_Rect rcDeplaS, int buttx, int butty,
                    NODE node[COL][LIG],int *condBuild, liste_point *L, int zoom);
#endif /* DEPLACEMENT_H_ */
