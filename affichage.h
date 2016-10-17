#include "struct.h"
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void affichage_tab(sol tab[COL][LIG]);
image zoom_image(image image, float zoom);
perso zoom_perso(perso perso, float zoom);
void affichage_map(sol tab[COL][LIG],SDL_Surface *screen, int zoom, image image, SDL_Rect coord_init);
image image_init();
void affichage_tab_object(sol tab[COL][LIG]);
perso init_perso();
perso affichage_perso(perso perso, liste_point L, int zoom);
#endif
