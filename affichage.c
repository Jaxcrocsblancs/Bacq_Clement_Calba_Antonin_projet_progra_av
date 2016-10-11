#include "include.h"

void affichage_map(sol tab[COL][LIG],SDL_Surface *screen, int zoom, image image, SDL_Rect coord_init)
{
	SDL_Rect rcCase, rcCaseDest;

	rcCase.x = 0;
	rcCase.y = 0;
	rcCase.h = taille*zoom;
	rcCase.w = taille*zoom;

	rcCaseDest.x = 0;
	rcCaseDest.y = 0;
	rcCaseDest.h = taille*zoom;
	rcCaseDest.w = taille*zoom;
	int col,lig;
	for(col=0;col<COL;col++)
	  {
	    rcCaseDest.y = taille*zoom*col +coord_init.y;
	    for(lig=0;lig<LIG;lig++)
	      {
            rcCaseDest.x = taille*zoom*lig +coord_init.x;
                if (tab[col][lig].id==0)
                     SDL_BlitSurface(image.herbe, &rcCase, screen, &rcCaseDest);
                if (tab[col][lig].id==1)
                     SDL_BlitSurface(image.chene, &rcCase, screen, &rcCaseDest);
                if (tab[col][lig].id==3)
                    SDL_BlitSurface(image.fraisier, &rcCase, screen, &rcCaseDest);
                if (tab[col][lig].id==4)
                    SDL_BlitSurface(image.ble, &rcCase, screen, &rcCaseDest);/*
                if (tab[col][lig].id==10)
                     SDL_BlitSurface(image.bois_1, &rcCase, screen, &rcCaseDest);
                if (tab[col][lig].id==11)
                    SDL_BlitSurface(image.bois_2, &rcCase, screen, &rcCaseDest);
                if (tab[col][lig].id==12)
                    SDL_BlitSurface(image.bois, &rcCase, screen, &rcCaseDest);*/

                if (tab[col][lig].item.id==1)
                    SDL_BlitSurface(image.bois_1, &rcCase, screen, &rcCaseDest);
	      }
	  }
}

void affichage_surface(SDL_Surface *screen, SDL_Surface *s,SDL_Rect rcCase, SDL_Rect rcCaseDest)
{
  SDL_BlitSurface(s, &rcCase, screen, &rcCaseDest);
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
*/

void affichage_tab(sol tab[COL][LIG])
{
  int col,lig;
  for (col=0;col<COL;col++)
    {
      for (lig=0;lig<LIG;lig++)
        printf("%d ",tab[col][lig].id);
      printf("\n");
    }
  printf("\n");
}

void affichage_tab_object(sol tab[COL][LIG])
{
  int col,lig;
  for (col=0;col<COL;col++)
    {
      for (lig=0;lig<LIG;lig++)
        printf("%d ",tab[col][lig].item.id);
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
    image.bois_1 = SDL_LoadBMP ("image/1_bois.bmp");
    image.bois_2 = SDL_LoadBMP ("image/2_3_bois.bmp");
    image.bois = SDL_LoadBMP ("image/bois.bmp");
    return image;
}

image zoom_image(image image, float zoom)
{
  image.herbe = rotozoomSurface(image.herbe, 0, zoom, 1);
  image.fraisier = rotozoomSurface(image.fraisier, 0, zoom, 1);
  image.chene = rotozoomSurface(image.chene, 0, zoom, 1);
  image.ble = rotozoomSurface(image.ble, 0, zoom, 1);
  image.bois_1 = rotozoomSurface(image.bois_1, 0, zoom, 1);
  image.bois_2 = rotozoomSurface(image.bois_2, 0, zoom, 1);
  image.bois = rotozoomSurface(image.bois, 0, zoom, 1);
  return image;
}
