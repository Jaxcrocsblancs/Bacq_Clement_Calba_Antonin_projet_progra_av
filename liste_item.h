
#ifndef LISTE_ITEM_H_
#define LISTE_ITEM_H_

#include "include.h"

item remplis_item(int id, int nb, char c);
liste_item l_videI (void);
bool est_videI(liste_item L);
item premI(liste_item L);
liste_item resteI(liste_item L);
void ecrire_premI(item a, liste_item L);
void ecrire_resteI(liste_item R, liste_item L);
liste_item consI(item a, liste_item L);
int presenceRI(item a, liste_item L);
liste_item supprimerRI(item a, liste_item L);
void afficher_item_liste(liste_item L);
liste_item renverser_listeI(liste_item L);

#endif /* ACTIONMENU_H_ */


