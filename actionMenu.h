/*
 * actionMenu.h
 *
 *  Created on: 15 oct. 2016
 *      Author: cleme
 */

#ifndef ACTIONMENU_H_
#define ACTIONMENU_H_

#include "include.h"

perso actionMenu(int action, sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom, int *click);
void couper(sol tab[COL][LIG],int buttx, int butty, perso perso, int zoom, int *click);
perso ramasser(sol tab[COL][LIG], perso perso, int buttx, int butty, int zoom, int *click);
perso deposer(sol tab[COL][LIG], perso perso, int buttx, int butty, int zoom, int *click);

#endif /* ACTIONMENU_H_ */
