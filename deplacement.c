/*
 * deplacement.c
 *
 *  Created on: 3 oct. 2016
 *      Author: cleme
 */

#include "include.h"

void deplacement_chemin(sol tab[COL][LIG], SDL_Surface *screen,SDL_Rect *rcDepla, SDL_Rect rcDeplaS, liste_point *L,
                        int buttx, int butty, NODE node[COL][LIG], int *cond, int zoom)
{
	int dx,dy;

	if(!est_vide(*L))
	{
		dx = prem(*L).col;
		dy = prem(*L).lig;

		if(node[dx][dy].walkable == 0)
		{
			rcDepla->x = dx * taille*zoom;
			rcDepla->y = dy * taille*zoom;
			*L = reste(*L);
		}
		else
		{
            printf("bloquer %d %d %D\n", tab[dx][dy].id, dx, dy);
			*L = Astar(tab,node,rcDepla->x/taille,rcDepla->y/taille,buttx,butty);
			deplacement_chemin(tab,screen,rcDepla,rcDeplaS,L,buttx,butty,node,cond,zoom);
		}
	}
	else
	{
		*cond = 0;
	}
}


void deplacement_personnage(sol tab[COL][LIG], SDL_Surface *screen, SDL_Rect *rcDepla,
		SDL_Rect rcDeplaS, liste_point *L, int buttx, int butty, NODE node[COL][LIG], int *cond, int zoom)
{
	if(*cond > 0)
	{
		if(*cond == 1)
		{
			*L = Astar(tab,node,rcDepla->x/taille,rcDepla->y/taille,buttx,butty);
			*cond = 2;
			afficherNode(node);
            afficher_point_liste(*L);
		}
		deplacement_chemin(tab,screen,rcDepla,rcDeplaS,L,buttx,butty,node,cond, zoom);
	}
}

void constr_chemin(sol tab[COL][LIG], SDL_Surface *screen,SDL_Rect *rcDepla, SDL_Rect rcDeplaS, int buttx, int butty,
                    NODE node[COL][LIG],int *condBuild, liste_point *L, int zoom)
{
    int dx,dy;

    if(!est_vide(*L))
    {
        if(est_vide(reste(*L)))
		{
			tab[prem(*L).col][prem(*L).lig].id = 0;
			*L = l_vide();
			*condBuild = 0;
			return;
		}
		dx = prem(*L).col;
		dy = prem(*L).lig;

		if(tab[dx][dy].id == 1)
		{
			rcDepla->x = dx * 32;
			rcDepla->y = dy * 32;
			*L = reste(*L);
		}
		else
		{
			*L = Astar(tab,node,rcDepla->x/32,rcDepla->y/32,buttx,butty);
			deplacement_constr(tab,screen,rcDepla,rcDeplaS,buttx,butty,node,condBuild,L, zoom);
		}
	}
	else
    {
        *condBuild = 0;
        return;
    }
}

void deplacement_constr(sol tab[COL][LIG], SDL_Surface *screen,SDL_Rect *rcDepla,
		SDL_Rect rcDeplaS, int buttx, int butty, NODE node[COL][LIG],int *condBuild, liste_point *L, int zoom)
{
	if(*condBuild > 0 && tab[buttx][butty].id != 0)
	{
		if(*condBuild == 1)
		{
			*L = Astar(tab,node,rcDepla->x/32,rcDepla->y/32,buttx,butty);
			*condBuild = 2;
		}
		constr_chemin(tab, screen, &rcDepla, rcDeplaS, buttx, butty, node, condBuild, L, zoom);
	}
}
