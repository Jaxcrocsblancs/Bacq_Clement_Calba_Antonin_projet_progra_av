#include "struct.h"
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void affichage_tab(sol tab[COL][LIG]);
image zoom_image(image image, float zoom);
perso zoom_perso(perso perso, float zoom);
void affichage_map(sol tab[COL][LIG],SDL_Surface *screen, int zoom, image image, SDL_Rect coord_init, int hauteur, int largeur, liste_stockpile stockPile);
image image_init();
void affichage_tab_object(sol tab[COL][LIG]);
perso affichage_perso(perso perso, liste_point L, int zoom);
void affichage_menu(SDL_Surface *screen, int hauteur, int largeur, image image, int action);

void affichage_text(int zoomint, int nb, int col, int lig, int zoom, image image, SDL_Surface *screen);
#endif
