#ifndef AFFICHAGE_H
#define AFFICHAGE_H

struct image
{
  SDL_Surface* chene;
  SDL_Surface* pommier;
  SDL_Surface* fraisier;
  SDL_Surface* ble;
  SDL_Surface* herbe;
};
typedef struct image image;

void affichage_tab(int tab[COL][LIG]);
void affichage_screen(int tab[COL][LIG], SDL_Surface* screen, float zoom, image image, SDL_Rect coord_init);
image zoom_image(image image, float zoom);
image image_init();








#endif
