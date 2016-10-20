/*
 * actionMenu.h
 *
 *  Created on: 15 oct. 2016
 *      Author: cleme
 */

#ifndef ACTIONMENU_H_
#define ACTIONMENU_H_

#include "include.h"
void actionMenu(int action, sol tab[COL][LIG],perso perso, int buttx, int butty);
perso actionPerso(sol tab[COL][LIG],perso perso, liste_point *plantation);
void couper(sol tab[COL][LIG], perso perso);
perso ramasser(sol tab[COL][LIG], perso perso);
perso deposer(sol tab[COL][LIG], perso perso,  int action);
perso cherche_action(sol tab[COL][LIG], perso perso, int *cond);
void miner(sol tab[COL][LIG], perso perso);
liste_point pousser(sol tab[COL][LIG], liste_point plantation);
perso rectangle(int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, perso perso, int action, sol sol[COL][LIG]);
#endif /* ACTIONMENU_H_ */
