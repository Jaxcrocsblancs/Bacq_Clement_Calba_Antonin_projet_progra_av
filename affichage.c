#include "include.h"

void affichage_tab(int tab[COL][LIG])
{
  int col,lig;
  for (col=0;col<COL;col++)
    {
      for (lig=0;lig<LIG;lig++)
	printf("%d ",tab[col][lig]);
      printf("\n");
    } 
  printf("\n");
}
image image_init()
{
  image image;
  image.chene = SDL_LoadBMP ("image/chene.bmp");
  image.pommier = SDL_LoadBMP ("image/pommier.bmp");
  image.fraisier = SDL_LoadBMP ("image/fraisier.bmp");
  image.ble = SDL_LoadBMP ("image/ble.bmp");
  image.herbe = SDL_LoadBMP ("image/herbe.bmp");
  return image;
}

image zoom_image(image image, float zoom)
{
  image.herbe = rotozoomSurface(image.herbe, 0, zoom, 1);
  image.pommier = rotozoomSurface(image.pommier, 0, zoom, 1);
  image.fraisier = rotozoomSurface(image.fraisier, 0, zoom, 1);
  image.chene = rotozoomSurface(image.chene, 0, zoom, 1);
  image.ble = rotozoomSurface(image.ble, 0, zoom, 1);
  return image;
}

void affichage_screen(int tab[COL][LIG], SDL_Surface* screen, float zoom, image image, SDL_Rect coord_init)
{
  SDL_Rect coord;
  int col,lig;
  

  for (col=0;col<COL;col++)
    {
      for (lig=0;lig<LIG;lig++)
      {
	SDL_BlitSurface(image.herbe,0, screen, &coord);
	if (tab[col][lig] == 1)
	  SDL_BlitSurface(image.chene,0, screen, &coord);
	if (tab[col][lig] == 2)
	  SDL_BlitSurface(image.pommier,0, screen, &coord);
	if (tab[col][lig] == 3)
	  SDL_BlitSurface(image.fraisier,0, screen, &coord);
	if (tab[col][lig] == 4)
	  SDL_BlitSurface(image.ble,0, screen, &coord);
	coord.y = coord_init.y + lig * 32 * (int)zoom;
      }
      coord.x = coord_init.x + col * 32 * (int)zoom;
    }
}
