/*
 * actionMenu.c
 *
 *  Created on: 15 oct. 2016
 *      Author: cleme
 */
#include "include.h"
#include <assert.h>

void couper(sol tab[COL][LIG],int buttx, int butty, perso perso, int zoom, int *click, SDL_Rect coord)
{
	if((perso.rcDest.x / (taille*zoom) + coord.x/(taille*zoom)== buttx) && (perso.rcDest.y / (taille*zoom)+ coord.y/(taille*zoom) == butty))
	{
	    if (tab[buttx][butty].id > 0) // ne marche pas avec le zoom
	    {
	    	tab[buttx][butty].item.id = tab[buttx][butty].id;
	    	tab[buttx][butty].id = 0;
	    }
	    *click = 0;
	}
}

perso ramasser(sol tab[COL][LIG], perso perso, int buttx, int butty, int zoom, int *click, SDL_Rect coord)
{
	if((perso.rcDest.x / (taille*zoom)+ coord.x/(taille*zoom) == buttx) && (perso.rcDest.y / (taille*zoom)+ coord.y/(taille*zoom) == butty))
	{
		if(tab[buttx][butty].item.id == perso.item.id || perso.item.id == 0)
		{
			perso.item.id = tab[buttx][butty].item.id;
			perso.item.nb += tab[buttx][butty].item.nb;
			tab[buttx][butty].item.id = 0;
			tab[buttx][butty].item.nb = 0;
			assert(perso.item.nb < 5);
		}
		*click = 0;
	}
	return perso;
}

perso deposer(sol tab[COL][LIG], perso perso, int buttx, int butty, int zoom, int *click, SDL_Rect coord)
{
	if((perso.rcDest.x / (taille*zoom) + coord.x/(taille*zoom)== buttx) && (perso.rcDest.y / (taille*zoom)+ coord.y/(taille*zoom) == butty))
	{
		if((tab[buttx][butty].item.id == perso.item.id || tab[buttx][butty].item.id == 0) && perso.item.id != 0)
		{
			tab[buttx][butty].item.id  = perso.item.id;
			tab[buttx][butty].item.nb = perso.item.nb;
			perso.item.id = 0;
			perso.item.nb = 0;
		}
		*click = 0;
	}
	return perso;
}

perso actionMenu(int action, sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom, int *click, SDL_Rect coord)
{
	perso = deplacement_personnage(tab,screen,perso,L,buttx,butty,cond,zoom,coord);
	if(*click != 0)
	{
		switch(action)
		{
		case 1:
			couper(tab,buttx,butty,perso,zoom,click, coord);
			break;
		case 2:
			perso = ramasser(tab,perso,buttx,butty,zoom,click, coord);
			break;
		case 3:
			perso = deposer(tab,perso,buttx,butty,zoom,click, coord);
			break;
		}
	}
	return perso;
}


