/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/

#include "include.h"

perso deplacement_chemin(sol tab[COL][LIG], SDL_Surface *screen, perso perso, int buttx, int butty, int zoom)
{
  int dx, dy;
  if(!est_vide(perso.L))
    {
      dx = prem(perso.L).col;
      dy = prem(perso.L).lig;
	  perso = affichage_perso(perso,perso.L,zoom);
      if(tab[dx][dy].id < 100)
	{
	  perso.pos.x = dx;
	  perso.pos.y = dy;
	  perso.L = reste(perso.L);
	}
      else
	{
	  perso.L = Astar(tab,perso.pos.x,perso.pos.y,buttx,butty);
	  deplacement_chemin(tab, screen, perso, buttx ,butty,zoom);
	  return perso;
	}
    }
  else
    {
      perso.rcSens.x = 0;
      perso.cond = 0;
    }
  return perso;
}


perso deplacement_personnage(sol tab[COL][LIG], SDL_Surface *screen,perso perso, int buttx, int butty, int zoom)
{
  if(perso.cond > 0)
    {
      if(perso.cond == 1)
        {
          perso.L = Astar(tab,perso.pos.x,perso.pos.y,buttx,butty);
          perso.cond = 2;
        }
      return deplacement_chemin(tab,screen, perso, buttx, butty, zoom);
    }
  return perso;
}


