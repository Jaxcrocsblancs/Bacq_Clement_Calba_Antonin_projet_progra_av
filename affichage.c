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

void affichage_screen(int tab[COL][LIG], SDL_Surface* screen)
{
  SDL_Surface* chene = SDL_LoadBMP ("image/chene.bmp");
  SDL_Surface* pommier = SDL_LoadBMP ("image/pommier.bmp");
  SDL_Surface* fraisier = SDL_LoadBMP ("image/fraisier.bmp");
  SDL_Surface* ble = SDL_LoadBMP ("image/ble.bmp");
  SDL_Surface* herbe = SDL_LoadBMP ("image/herbe.bmp");
  SDL_Rect coord;
  int col,lig;
	      
  coord.y = 0;
  for (col=0;col<COL;col++)
    {
      coord.x=0;
      for (lig=0;lig<LIG;lig++)
      {
	SDL_BlitSurface(herbe,0, screen, &coord);
	if (tab[col][lig] == 1)
	  SDL_BlitSurface(chene,0, screen, &coord);
	if (tab[col][lig] == 2)
	  SDL_BlitSurface(pommier,0, screen, &coord);
	if (tab[col][lig] == 3)
	  SDL_BlitSurface(fraisier,0, screen, &coord);
	if (tab[col][lig] == 4)
	  SDL_BlitSurface(ble,0, screen, &coord);
	coord.x += 32;
      }
      coord.y+=32;
    }
}
