#include "include.h"

void affichage_map(map_objt tab[COL][LIG],SDL_Surface *screen, int zoom, image image, SDL_Rect coord_init)
{
	SDL_Rect rcCase, rcCaseDest;

	rcCase.x = 0;
	rcCase.y = 0;
	rcCase.h = 16*zoom;
	rcCase.w = 16*zoom;

	rcCaseDest.x = 0;
	rcCaseDest.y = 0;
	rcCaseDest.h = 16*zoom;
	rcCaseDest.w = 16*zoom;
	int col,lig;
	for(col=0;col<COL;col++)
	  {
	    rcCaseDest.y = 16*zoom*col +coord_init.y;
	    for(lig=0;lig<LIG;lig++)
	      {
            rcCaseDest.x = 16*zoom*lig +coord_init.x;
           // printf("col:%d lig:%d \n",col, lig);
            SDL_BlitSurface(tab[col][lig].s, &rcCase, screen, &rcCaseDest);
	      }
	  }
}

void affichage_surface(SDL_Surface *screen, SDL_Surface *s,SDL_Rect rcCase, SDL_Rect rcCaseDest)
{
  SDL_BlitSurface(s, &rcCase, screen, &rcCaseDest);
}

void mise_image_struct_tableau(map_objt tab[COL][LIG], image image)
{
    int col,lig;
    for (col=0;col<COL;col++)
        for (lig=0;lig<LIG;lig++)
            {
                tab[col][lig].s = image.herbe;
                if (tab[col][lig].a==1)
                    tab[col][lig].s = image.chene;
                if (tab[col][lig].a==3)
                    tab[col][lig].s = image.fraisier;
                if (tab[col][lig].a==4)
                    tab[col][lig].s = image.ble;
                                }
}

/*void affichage_perso(SDL_Surface *screen, SDL_Surface *perso,SDL_Rect rcDepla, SDL_Rect rcDeplaS,liste_point L,int cpt)
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
	  rcDeplaS.x = (0+cpt)*32;a
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
*/

void affichage_tab(map_objt tab[COL][LIG])
{
  int col,lig;
  for (col=0;col<COL;col++)
    {
      for (lig=0;lig<LIG;lig++)
	printf("%d ",tab[col][lig].a);
      printf("\n");
    }
  printf("\n");
}

image image_init()
{
  image image;
  image.chene = SDL_LoadBMP ("image/chene.bmp");
  image.fraisier = SDL_LoadBMP ("image/fraisier.bmp");
  image.ble = SDL_LoadBMP ("image/ble.bmp");
  image.herbe = SDL_LoadBMP ("image/herbe.bmp");
  return image;
}

image zoom_image(image image, float zoom)
{
  image.herbe = rotozoomSurface(image.herbe, 0, zoom, 1);
  image.fraisier = rotozoomSurface(image.fraisier, 0, zoom, 1);
  image.chene = rotozoomSurface(image.chene, 0, zoom, 1);
  image.ble = rotozoomSurface(image.ble, 0, zoom, 1);
  return image;
}
