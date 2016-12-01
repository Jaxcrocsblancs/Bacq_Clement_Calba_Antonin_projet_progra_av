/*
 * liste_point.h
 *
 *  Created on: 29 sept. 2016
 *      Author: cleme
 */
#include "include.h"

#ifndef LISTE_POINT_H_
#define LISTE_POINT_H_


liste_point l_vide () ;
bool est_vide (liste_point L) ;
point_cout prem(liste_point L);
liste_point reste (liste_point L) ;
void ecrire_prem (point_cout, liste_point L) ;
void ecrire_reste (liste_point R, liste_point L) ;
liste_point cons (point_cout a, liste_point L) ;
int presenceR(point_cout a, liste_point L);
liste_point supprimerR(point_cout a, liste_point L);
point_cout remplisPoint(int col,int lig,int f);
point_cout plusPetitF(point_cout max,liste_point L);
void afficher_point_liste(liste_point L);
liste_point renverser_liste(liste_point L);
void free_liste_point(liste_point L);

#endif /* LISTE_POINT_H_ */
