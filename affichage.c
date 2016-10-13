/*************************/
/* procedural.c          */
/* Auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
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
            SDL_BlitSurface(image.herbe, &rcCase, screen, &rcCaseDest);
	      }
	  }

	for(col=0;col<COL;col++)
	  {
	    rcCaseDest.y = taille*zoom*col + coord_init.y;
	    if (rcCaseDest.y> -taille*zoom)
            for(lig=0;lig<LIG;lig++)
              {
                rcCaseDest.x = taille*zoom*lig + coord_init.x;
                if (rcCaseDest.x> -taille*zoom)
                {
                switch (tab[col][lig].id)
                    {
                        case 1:
                        {
                            rcCase.x = 5*taille*zoom;
                            rcCase.y = 0*taille*zoom;
                            rcCase.h = 2*taille*zoom;
                            rcCaseDest.y = taille*zoom*(col-1) + coord_init.y;
                            SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                            rcCaseDest.y = taille*zoom*col + coord_init.y;
                            rcCase.h = taille*zoom;
                            break;
                        }
                        case 2:
                        {
                            rcCase.x = 6*taille*zoom;
                            rcCase.y = 2*taille*zoom;
                            SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                            break;
                        }
                       case 3:
                        {
                            rcCase.x = 4*taille*zoom;
                            rcCase.y = 2*taille*zoom;
                            SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                            break;
                        }
                        case 4:
                        {
                            rcCase.x = 5*taille*zoom;
                            rcCase.y = 2*taille*zoom;
                            SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                            break;
                        }
                    }
                switch (tab[col][lig].item.id)
                    {
                    case 1:
                    {
                        rcCase.x = 2*taille*zoom;
                        rcCase.y = 2*taille*zoom;
                        SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                        break;
                    }
                    case 2:
                    {
                        rcCase.x = 6*taille*zoom;
                        rcCase.y = 3*taille*zoom;
                        SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                        break;
                    }
                    case 3:
                    {
                        rcCase.x = 7*taille*zoom;
                        rcCase.y = 3*taille*zoom;
                        SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                        break;
                    }
                    case 4:
                    {
                        rcCase.x = 6*taille*zoom;
                        rcCase.y = 4*taille*zoom;
                        SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                        break;
                    }
                  }
                }
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
    image.herbe = SDL_LoadBMP ("image/herbe.bmp");
    image.plante = SDL_LoadBMP ("image/plante.bmp");
    SDL_SetColorKey(image.plante, SDL_SRCCOLORKEY, SDL_MapRGB(image.plante->format, 255, 0, 255));
    return image;
}

perso init_perso()
{
    perso p;
    SDL_Surface *image;
    SDL_Rect rcDest;
    SDL_Rect rcSens;

    rcDest.x = 0;
    rcDest.y = 0;
    rcDest.h = 32;
    rcDest.w = 32;

    rcSens.x = 0;
    rcSens.y = 0;
    rcSens.h = 32;
    rcSens.w = 32;

    image = SDL_LoadBMP ("image/plante.bmp");

    p.rcDest = rcDest;
    p.rcSens = rcSens;
    p.perso = image;

    return p;
}

image zoom_image(image image, float zoom)
{
  image.herbe = rotozoomSurface(image.herbe, 0, zoom, 1);
  image.plante = rotozoomSurface(image.plante, 0, zoom, 1);
  SDL_SetColorKey(image.plante, SDL_SRCCOLORKEY, SDL_MapRGB(image.plante->format, 255, 0, 255));
  return image;
}
