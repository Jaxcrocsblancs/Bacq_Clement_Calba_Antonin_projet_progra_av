/*
 * liste_stockpile.h
 *
 *  Created on: 31 oct. 2016
 *      Author: cleme
 */
#include "include.h"

#ifndef LISTE_STOCKPILE_H_
#define LISTE_STOCKPILE_H_

stockpile remplis_stockpile(int id, int nb, int col, int lig);
liste_stockpile l_videS(void);
int est_videS(liste_stockpile L);
stockpile premS(liste_stockpile L);
liste_stockpile resteS(liste_stockpile L);
void ecrire_premS(stockpile a, liste_stockpile L);
void ecrire_resteS(liste_stockpile R, liste_stockpile L);
liste_stockpile consS(stockpile a, liste_stockpile L);
void afficher_stockpile_liste(liste_stockpile L);
liste_stockpile renverser_listeS(liste_stockpile L);
liste_stockpile supprimerS(stockpile a, liste_stockpile L);
stockpile rechercher_elem(int col, int lig, liste_stockpile L);
liste_stockpile changer_elem(int col, int lig, int nb, liste_stockpile L);


#endif /* LISTE_STOCKPILE_H_ */
