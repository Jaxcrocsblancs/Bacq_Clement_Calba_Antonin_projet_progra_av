#include "include.h"

void affichage_map(map_objt tab[COL][LIG],SDL_Surface *screen)
{
	SDL_Rect rcCase, rcCaseDest;

	rcCase.x = 0;
	rcCase.y = 0;
	rcCase.h = 32;
	rcCase.w = 32;

	rcCaseDest.x = 0;
	rcCaseDest.y = 0;
	rcCaseDest.h = 32;
	rcCaseDest.w = 32;

	int loc,gil;
	for(loc=0;loc<COL;loc++)
	{
		rcCaseDest.x = 32*loc;
		for(gil=0;gil<LIG;gil++)
		{
			rcCaseDest.y = 32*gil;
			SDL_BlitSurface(&tab[loc][gil].s, &rcCase, screen, &rcCaseDest);
			rcCaseDest.y += 32;
		}
	}
}

void affichage_surface(SDL_Surface *screen, SDL_Surface *s,SDL_Rect rcCase, SDL_Rect rcCaseDest)
{
	SDL_BlitSurface(s, &rcCase, screen, &rcCaseDest);
}

void affichage_perso(SDL_Surface *screen, SDL_Surface *perso,SDL_Rect rcDepla, SDL_Rect rcDeplaS,liste_point L,int cpt)
{
	if(!est_vide(L))
	{
		if(prem(L).col * 32 > rcDepla.x)
		{
			rcDeplaS.x = (4+cpt)*32;
		}
		if(prem(L).col * 32 < rcDepla.x)
		{
			rcDeplaS.x = (6+cpt)*32;
		}
		if(prem(L).lig * 32 < rcDepla.y)
		{
			rcDeplaS.x = (2+cpt)*32;
		}
		if(prem(L).lig * 32 > rcDepla.y)
		{
			rcDeplaS.x = (0+cpt)*32;
		}

		rcDepla.x = prem(L).col * 32;
		rcDepla.y = prem(L).lig * 32;
		SDL_BlitSurface(perso, &rcDeplaS, screen, &rcDepla);
		if(!est_vide(reste(L)))
		{
			L = reste(L);
		}
		cpt++;
		if(cpt == 2)
		{
			cpt = 0;
		}
	}
}






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
	coord.x = coord_init.x + lig * 32 * (int)zoom;
      }
      coord.y = coord_init.y + col * 32 * (int)zoom;
    }
}
