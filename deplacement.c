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
    }
  return perso;
}

perso ramasse_objets(sol tab[COL][LIG], perso perso, int zoom)
{
    int memid, memnb;
    if (tab[perso.rcDest.x/(taille*zoom)][perso.rcDest.y/(taille*zoom)].item.id == perso.id && perso.id !=0)
    {
      perso.nb += tab[perso.rcDest.x/(taille*zoom)][perso.rcDest.y/(taille*zoom)].item.nb;
      tab[perso.rcDest.x/(taille*zoom)][perso.rcDest.y/(taille*zoom)].item.id = 0;
    }

    else
    {
        memid = tab[perso.rcDest.x/(taille*zoom)][perso.rcDest.y/(taille*zoom)].item.id;
        memnb = tab[perso.rcDest.x/(taille*zoom)][perso.rcDest.y/(taille*zoom)].item.nb;
        tab[perso.rcDest.x/(taille*zoom)][perso.rcDest.y/(taille*zoom)].item.id = perso.id;
        tab[perso.rcDest.x/(taille*zoom)][perso.rcDest.y/(taille*zoom)].item.nb = perso.nb;
        perso.id = memid;
        perso.nb = memnb;
    }
    return perso;
}

