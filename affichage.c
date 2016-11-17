/*************************/
/* procedural.c          */
/* Auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

void affichage_map(sol tab[COL][LIG],SDL_Surface *screen, int zoom, image image, SDL_Rect coord_init, int hauteur, int largeur, liste_stockpile stockPile)
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
      rcCaseDest.x = taille*zoom*col +coord_init.x;
      if (rcCaseDest.x >= 0 && rcCaseDest.x < -coord_init.x + largeur)
        {
          for(lig=0;lig<LIG;lig++)
            {
              rcCaseDest.y = taille*zoom*lig +coord_init.y;
              if (rcCaseDest.y >= 0 && rcCaseDest.y < -coord_init.y + hauteur+ 64)
                SDL_BlitSurface(image.herbe, &rcCase, screen, &rcCaseDest);
            }
        }
    }

  for(col=0;col<COL;col++)
    {
      rcCaseDest.x = taille*zoom*col + coord_init.x;
      if (rcCaseDest.x >= 0 && rcCaseDest.x < -coord_init.x + largeur)
        {
            for(lig=0;lig<LIG;lig++)
              {
                rcCaseDest.y= taille*zoom*lig + coord_init.y;
                if (rcCaseDest.y >= 0 && rcCaseDest.y < -coord_init.y + hauteur+ 64)
                {
                    switch (tab[col][lig].id)
                        {
                            case pousse_fraise:
                            {
                                rcCase.x = 0*taille*zoom;
                                rcCase.y = 0*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case fraise:
                            {
                                rcCase.x = 0*taille*zoom;
                                rcCase.y = 1*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case pousse_coton:
                            {
                                rcCase.x = 1*taille*zoom;
                                rcCase.y = 0*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case coton:
                            {
                                rcCase.x = 1*taille*zoom;
                                rcCase.y = 1*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case pousse_ble:
                            {
                                rcCase.x = 2*taille*zoom;
                                rcCase.y = 0*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                             case bles:
                            {
                                rcCase.x = 2*taille*zoom;
                                rcCase.y = 1*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                             case pousse_bois:
                            {
                                rcCase.x = 3*taille*zoom;
                                rcCase.y = 3*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case bois:
                            {
                                rcCase.x = 3*taille*zoom;
                                rcCase.y = 0*taille*zoom;
                                rcCase.h = 2*taille*zoom;
                                rcCaseDest.y = taille*zoom*(lig-1) + coord_init.y;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                rcCaseDest.y = taille*zoom*lig + coord_init.y;
                                rcCase.h = taille*zoom;
                                break;
                            }
                            case 21:
                                {
                                rcCase.x = 3*taille*zoom;
                                rcCase.y = 3*taille*zoom;
                                rcCase.h = 3*taille*zoom;
                                rcCase.w = 3*taille*zoom;
                                rcCaseDest.y = taille*zoom*(lig-1) + coord_init.y;
                                rcCaseDest.x = taille*zoom*(col-1) + coord_init.x;
                                SDL_BlitSurface(image.mine, &rcCase, screen, &rcCaseDest);
                                rcCaseDest.x = taille*zoom*col + coord_init.x;
                                rcCaseDest.y = taille*zoom*lig + coord_init.y;
                                rcCase.h = taille*zoom;
                                rcCase.w = taille*zoom;
                                break;
                                }
                            case 101:
                                {
                                rcCase.x = 5*taille*zoom;
                                rcCase.y = taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                                }
                            case 9:
                                {
                                rcCase.x = 4*taille*zoom;
                                rcCase.y = 0;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);

                                stockpile elem;
                                elem = rechercher_elem(col,lig,stockPile);
                                assert(elem.col == col && elem.lig == lig);
                                if(elem.nb > 0)
                                {
									switch(elem.id)
									{
										case bois:
										{
											rcCase.x = 3*taille*zoom;
											rcCase.y = 2*taille*zoom;
											SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
											break;
										}
									}
                                }
                                break;
                                }
                        }
                    switch (tab[col][lig].item.id)
                        {
                            case fraise:
                            {
                                rcCase.x = 0*taille*zoom;
                                rcCase.y = 2*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case coton:
                            {
                                rcCase.x = 1*taille*zoom;
                                rcCase.y = 2*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                             case bles:
                            {
                                rcCase.x = 2*taille*zoom;
                                rcCase.y = 2*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                             case bois:
                            {
                                rcCase.x = 3*taille*zoom;
                                rcCase.y = 2*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case 20:
                            {
                                rcCase.x = 0*taille*zoom;
                                rcCase.y = 4*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;
                            }
                            case 21:
                                {
                                rcCase.x = 1*taille*zoom;
                                rcCase.y = 4*taille*zoom;
                                SDL_BlitSurface(image.plante, &rcCase, screen, &rcCaseDest);
                                break;

                                }
                      }
                    if (tab[col][lig].ordre != 0 && tab[col][lig].id != 21)
                        {
                            rcCase.x = 0;
                            rcCase.y = 0;
                            if (tab[col][lig].ordre > 1000)
                                rcCase.x= taille * zoom;
                            SDL_BlitSurface(image.alpha, &rcCase, screen, &rcCaseDest);
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

perso affichage_perso(perso perso, liste_point L, int zoom)
{
  if(!est_vide(L))
    {
      if(prem(L).col * (taille * zoom) > perso.rcDest.x)
	{
	  perso.rcSens.x = (perso.cptSens.x + 4) * (taille * zoom);
	}
      if(prem(L).col * (taille * zoom) < perso.rcDest.x)
	{
	  perso.rcSens.x = (-perso.cptSens.x + 7) * (taille * zoom);
	}
      if(prem(L).lig * (taille * zoom) < perso.rcDest.y)
	{
	  perso.rcSens.x = (perso.cptSens.x + 2) * (taille * zoom);
	}
      if(prem(L).lig * (taille * zoom) > perso.rcDest.y)
	{
	  perso.rcSens.x = (perso.cptSens.x + 0) * (taille * zoom);
	}
      perso.rcSens.y = perso.cptSens.y * (taille * zoom);

      perso.cptSens.x += 1;

      if(perso.cptSens.x == 2)
	{
	  perso.cptSens.x = 0;
	  perso.cptSens.y += 1;
	  if(perso.cptSens.y == 2)
	    {
	      perso.cptSens.y = 0;
	    }
	}
    }
  return perso;
}



void affichage_tab(sol tab[COL][LIG])
{
  int col,lig;
  for (lig=0;lig<LIG;lig++)
    {
      for (col=0;col<COL;col++)
        printf("%d ",tab[col][lig].ordre);
      printf("\n");
    }
  printf("\n");
}

void affichage_tab_object(sol tab[COL][LIG])
{
  int col,lig;
  for (lig=0;lig<LIG;lig++)
    {
      for (col=0;col<COL;col++)
        printf("%d ",tab[col][lig].item.id);
      printf("\n");
    }
  printf("\n");
}




image zoom_image(image image, float zoom)
{
  image.herbe = rotozoomSurface(image.herbe, 0, zoom, 1);
  image.plante = rotozoomSurface(image.plante, 0, zoom, 1);
  image.alpha = rotozoomSurface(image.alpha, 0, zoom, 1);
  image.mine = rotozoomSurface(image.mine, 0, zoom, 1);
  SDL_SetColorKey(image.plante, SDL_SRCCOLORKEY, SDL_MapRGB(image.plante->format, 255, 0, 255));
  SDL_SetColorKey(image.alpha, SDL_SRCCOLORKEY, SDL_MapRGB(image.alpha->format, 255, 0, 255));
  SDL_SetColorKey(image.mine, SDL_SRCCOLORKEY, SDL_MapRGB(image.mine->format, 255, 0, 255));
  SDL_SetAlpha(image.alpha,SDL_SRCALPHA, 128 );
  return image;
}

perso zoom_perso(perso perso, float zoom)
{
  perso.perso = rotozoomSurface(perso.perso, 0, zoom, 1);
  return perso;
}

void affichage_menu(SDL_Surface *screen, int hauteur, int largeur, image image, int action)
{
  SDL_Rect rcCase, rcCaseDest;
  int col;
  rcCase.x = 0;
  rcCase.y = 0 ;
  rcCase.h = 2*taille;
  rcCase.w = 2*taille;

  rcCaseDest.x = largeur/2-505/2 ;
  rcCaseDest.y = hauteur;
  rcCaseDest.h = 2*taille;
  rcCaseDest.w = 2*taille;
  for (col = 0; col < largeur / (taille*2);col++)
    {
      SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);
      rcCase.x += taille*2;
      rcCaseDest.x += taille*2;
    }





  if (action == 0)
  {
    rcCase.x = 32 * 0 ;
    rcCase.y = 64+ 32 * 1;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 48* 1;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);
  }
  if ((action-1)/10 == 1)
  {
    rcCase.x = 32 * 1 ;
    rcCase.y = 64+ 32 * 1;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 49* 0;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);

    rcCase.x = 32 * 2 ;
    rcCase.y = 64+ 32 * 1;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 49* 1;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);

        rcCase.x = 32 * 3 ;
    rcCase.y = 64+ 32 * 1;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 49* 2;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);

    rcCase.x = 32 * 4 ;
    rcCase.y = 64+ 32 * 1;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 49* 3;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);

    rcCase.x = 32 * 5 ;
    rcCase.y = 64+ 32 * 1;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 49* 4;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);

    rcCase.x = 32 * 6 ;
    rcCase.y = 64+ 32 * 1;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 49* 5;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);
  }
    if (action != 0)
    {
    rcCase.x = 0;
    rcCase.y = 64;
    rcCase.h = 32;
    rcCase.w = 32;

    rcCaseDest.x = largeur/2-505/2 + 17 + 49 * 9;
    rcCaseDest.y = hauteur + 16;
    rcCaseDest.h = 32;
    rcCaseDest.w = 32;
    SDL_BlitSurface(image.menu, &rcCase, screen, &rcCaseDest);
    }
}

