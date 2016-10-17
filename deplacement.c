/*
 * deplacement.c
 *
 *  Created on: 3 oct. 2016
 *      Author: cleme
 */

#include "include.h"

perso deplacement_chemin(sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom)
{
  int dx, dy;
  if(!est_vide(*L))
    {
      dx = prem(*L).col;
      dy = prem(*L).lig;
<<<<<<< HEAD
	  perso = affichage_perso(perso,*L,zoom);
      if(tab[dx][dy].id < 100)
	{
	  perso.rcDest.x = dx * taille * zoom;
	  perso.rcDest.y = dy * taille * zoom;
	  *L = reste(*L);
	}
      else
	{
	  *L = Astar(tab,perso.rcDest.x,perso.rcDest.y,buttx,butty);
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
	  *L = Astar(tab,perso.rcDest.x/ (taille*zoom),perso.rcDest.y/ (taille*zoom),buttx,butty);
	  *cond = 2;
	}
      return deplacement_chemin(tab,screen, perso, L, buttx, butty, cond, zoom);
=======

      if(tab[dx][dy].id != 1)
	{
	  perso.rcDest.x = dx * taille * zoom;
	  perso.rcDest.y = dy * taille * zoom;
	  *L = reste(*L);
	}
      else
	{
	  *L = Astar(tab,perso.rcDest.x,perso.rcDest.y,buttx,butty);
	  deplacement_chemin(tab, screen, perso, L, buttx ,butty ,cond ,zoom);
	  return perso;
	}
    }
  else
    {
      *cond = 0;
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
    }
  return perso;
}


<<<<<<< HEAD

=======
perso deplacement_personnage(sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom)
{
  if(*cond > 0)
    {
      if(*cond == 1)
	{
	  *L = Astar(tab,perso.rcDest.x/ (taille*zoom),perso.rcDest.y/ (taille*zoom),buttx,butty);
	  *cond = 2;
	}
      return deplacement_chemin(tab,screen, perso, L, buttx, butty, cond, zoom);
    }
  return perso;
}
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
