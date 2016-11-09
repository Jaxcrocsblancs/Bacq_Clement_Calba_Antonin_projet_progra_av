/*
 * actionMenu.h
 *
 *  Created on: 15 oct. 2016
 *      Author: cleme
 */

#ifndef ACTIONMENU_H_
#define ACTIONMENU_H_

#include "include.h"
void actionMenu(int action, sol tab[COL][LIG], int buttx, int butty, liste_stockpile *stockPile);
perso actionPerso(sol tab[COL][LIG],perso perso, liste_point *plantation, liste_stockpile *stockPile, int *cond);
void couper(sol tab[COL][LIG], perso perso);
perso ramasser(sol tab[COL][LIG], perso perso);
perso deposer(sol tab[COL][LIG], perso perso, int nb, int buttx, int butty, liste_stockpile *stockPile);
void cherche_action(sol tab[COL][LIG], perso perso[NB_Perso], int cond[NB_Perso]);
void miner(sol tab[COL][LIG], perso perso);
liste_point pousser(sol tab[COL][LIG], liste_point plantation);
void rectangle(int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, int action, sol sol[COL][LIG], liste_stockpile *stockPile);
perso construire(sol tab[COL][LIG], perso perso, int ido, int nbi, int idi);
perso faim(perso perso);
perso manger(sol tab[COL][LIG], perso perso);
perso chercher_object(sol tab[COL][LIG], perso perso, int id);
void creerStockPile(sol tab[COL][LIG], liste_stockpile *stockPile, int id, int buttx, int butty);
perso chercheStockPile(sol tab[COL][LIG], perso perso, liste_stockpile *stockPile);


#endif /* ACTIONMENU_H_ */
