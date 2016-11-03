/*
 * actionMenu.h
 *
 *  Created on: 15 oct. 2016
 *      Author: cleme
 */
#include "include.h"

#ifndef ACTIONMENU_H_
#define ACTIONMENU_H_

void actionMenu(int action, sol tab[COL][LIG],perso perso, int buttx, int butty, liste_stockpile *stockPile);
perso actionPerso(sol tab[COL][LIG],perso perso, liste_point *plantation,liste_stockpile *stockPile);
void couper(sol tab[COL][LIG], perso perso);
perso ramasser(sol tab[COL][LIG], perso perso);
perso deposer(sol tab[COL][LIG], perso perso, int nb, int buttx, int butty, liste_stockpile *stockPile);
perso cherche_action(sol tab[COL][LIG], perso perso, int *cond);
void miner(sol tab[COL][LIG], perso perso);
liste_point pousser(sol tab[COL][LIG], liste_point plantation);
perso rectangle(int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, perso perso, int action, sol sol[COL][LIG], liste_stockpile *stockPile);
perso construire(sol tab[COL][LIG], perso perso, int ido, int nbi, int idi);
perso chercher_object(sol tab[COL][LIG], perso perso, int id);
perso chercheStockPile(sol tab[COL][LIG], perso perso, liste_stockpile *stockPile);
#endif /* ACTIONMENU_H_ */
