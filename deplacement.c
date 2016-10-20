/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/

#include "include.h"

perso deplacement_chemin(sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom)
{
  int dx, dy;
  if(!est_vide(*L))
    {
      dx = prem(*L).col;
      dy = prem(*L).lig;
      perso = affichage_perso(perso,*L,zoom);
      if(tab[dx][dy].id < 100)
	{
	  perso.pos.x = dx;
	  perso.pos.y = dy;
	  *L = reste(*L);
	}
      else
	{
	  *L = Astar(tab,perso.pos.x,perso.pos.y,buttx,butty);
	  deplacement_chemin(tab, screen, perso, L, buttx ,butty ,cond ,zoom);
	  return perso;
	}
    }
  else
    {
      perso.rcSens.x = 0;
      *cond = 0;
    }
  return perso;
}


perso deplacement_personnage(sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom)
{
  if(*cond > 0)
    {
      if(*cond == 1)
        {
          *L = Astar(tab,perso.pos.x,perso.pos.y,buttx,butty);
          *cond = 2;
        }
      return deplacement_chemin(tab,screen, perso, L, buttx, butty, cond, zoom);
    }
  return perso;
}
