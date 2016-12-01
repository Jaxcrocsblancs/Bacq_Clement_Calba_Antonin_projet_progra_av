
#ifndef HANDLE_H
#define HANDLE_H

#include "include.h"

void handle(SDL_Event *event, perso perso[NB_Perso], image *image, int *action,int *done, int *p, int *zoom, SDL_Rect *coord, int hauteur, int largeur, int  *gauche_maintenu_x, int *gauche_maintenu_y, int *gauche_maintenu, int *buttx, int *butty);
void tour(unsigned int *temps_ennemi, perso ennemi[NB_ennemi], SDL_Rect coord, liste_point *plantation, perso perso[NB_Perso], int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, int action, sol sol[COL][LIG], SDL_Surface *screen, liste_stockpile *stockPile, int zoom, image image, int hauteur, int largeur, unsigned int *temps, int p);
#endif
