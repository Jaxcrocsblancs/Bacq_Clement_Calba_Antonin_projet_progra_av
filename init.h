#include "include.h"
#ifndef INIT_H
#define INIT_H

void init_tab(sol tab[COL][LIG]);
void init_var(sol sol[COL][LIG], image *image, perso perso[NB_Perso], SDL_Rect *coord, int *zoom, int *done, int *action, int *gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *p, unsigned int *temps, liste_point *plantation, liste_stockpile *stockPile, int *buttx, int *butty);
perso init_perso();
image image_init();
perso init_ennemi();
#endif
