#ifndef AFFICHAGE_H
#define AFFICHAGE_H

struct map_objt
{
  SDL_Surface *s;
  int a;
};
typedef struct map_objt map_objt;

struct image
{
  SDL_Surface* chene;
  SDL_Surface* salade;
  SDL_Surface* fraisier;
  SDL_Surface* ble;
  SDL_Surface* herbe;
};
typedef struct image image;



void affichage_tab(map_objt tab[COL][LIG]);
image zoom_image(image image, float zoom);
void affichage_map(map_objt tab[COL][LIG],SDL_Surface *screen, int zoom, image image, SDL_Rect coord_init);
image image_init();
void mise_image_struct_tableau(map_objt tab[COL][LIG], image image);







#endif
