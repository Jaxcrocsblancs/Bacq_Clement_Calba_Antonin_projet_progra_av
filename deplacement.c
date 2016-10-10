/*
 * deplacement.c
 *
 *  Created on: 3 oct. 2016
 *      Author: cleme
 */

#include "SDL.h"
#include "include.h"
#include "map.h"
#include "chemin.c"
#include <assert.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define COL 20
#define LIG 20


void affichage_map(map_objt tab[COL][LIG],SDL_Surface *screen)
{
	SDL_Rect rcCase, rcCaseDest;

	rcCase.x = 0;
	rcCase.y = 0;
	rcCase.h = 32;
	rcCase.w = 32;

	rcCaseDest.x = 0;
	rcCaseDest.y = 0;
	rcCaseDest.h = 32;
	rcCaseDest.w = 32;

	int loc,gil;
	for(loc=0;loc<COL;loc++)
	{
		rcCaseDest.x = 32*loc;
		for(gil=0;gil<LIG;gil++)
		{
			rcCaseDest.y = 32*gil;
			SDL_BlitSurface(&tab[loc][gil].s, &rcCase, screen, &rcCaseDest);
		}
	}
}

void deplacement_chemin(map_objt tab[COL][LIG], SDL_Surface *screen, SDL_Surface *perso,SDL_Rect *rcDepla,
		SDL_Rect rcDeplaS, liste_point *L, int buttx, int butty, NODE node[COL][LIG], int *cond)
{
	int dx,dy;

	if(!est_vide(*L))
	{
		dx = prem(*L).col;
		dy = prem(*L).lig;

		if(tab[dx][dy].a == 1)
		{
			rcDepla->x = dx * 32;
			rcDepla->y = dy * 32;
			*L = reste(*L);
			SDL_Delay(100);
		}
		else
		{
			*L = Astar(tab,node,rcDepla->x/32,rcDepla->y/32,buttx,butty);
			deplacement_chemin(tab,screen,perso,rcDepla,rcDeplaS,L,buttx,butty,node,cond);
		}
	}
	else
	{
		*cond = 0;
	}
}


void deplacement_personnage(map_objt tab[COL][LIG], SDL_Surface *screen, SDL_Surface *perso,SDL_Rect *rcDepla,
		SDL_Rect rcDeplaS, liste_point *L, int buttx, int butty, NODE node[COL][LIG], int *cond)
{
	if(*cond > 0)
	{
		if(*cond == 1)
		{
			*L = Astar(tab,node,rcDepla->x/32,rcDepla->y/32,buttx,butty);
			*cond = 2;
		}
		deplacement_chemin(tab,screen,perso,rcDepla,rcDeplaS,L,buttx,butty,node,cond);
	}
}


//
//
//int main(int argc, char *argv[])
//{
//	SDL_Surface *temp, *perso, *CaseN, *CaseR, *screen;
//	SDL_Event event;
//	SDL_Rect  rcDepla, rcDeplaS;
//
//	freopen("CON", "w", stdout);
//	freopen("CON", "r", stdin);
//	freopen("CON", "w", stderr);
//
//	rcDeplaS.x = 0;
//	rcDeplaS.y = 0;
//	rcDeplaS.h = 32;
//	rcDeplaS.w = 32;
//
//	rcDepla.x = 16*32;
//	rcDepla.y = 2*32;
//	rcDepla.h = 32;
//	rcDepla.w = 32;
//
//	map_objt tab[COL][LIG];
//	NODE node[COL][LIG];
//
//  /* initialize SDL */
//	SDL_Init(SDL_INIT_VIDEO);
//
//  /* set the title bar */
//	SDL_WM_SetCaption("JEUX", "JEUX");
//
//  /* create window */
//	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
//
//  /* set keyboard repeat */
//	SDL_EnableKeyRepeat(70, 70);
//
//	temp   = SDL_LoadBMP("images/caseR.bmp");
//	CaseR = SDL_DisplayFormat(temp);
//	SDL_FreeSurface(temp);
//
//	temp  = SDL_LoadBMP("images/caseN.bmp");
//	CaseN = SDL_DisplayFormat(temp);
//	SDL_FreeSurface(temp);
//
//	temp  = SDL_LoadBMP("images/test.bmp");
//	perso = SDL_DisplayFormat(temp);
//	SDL_FreeSurface(temp);
//
//	//FONCTION REMPLIS
//	int col,lig;
//	for(col=0;col<COL;col++)
//	{
//		for(lig=0;lig<LIG;lig++)
//		{
//			tab[col][lig].s = *CaseN;
//			tab[col][lig].a = 1;
//		}
//	} // end for$
//
//
//	// FIN FONCTION REMPLIS
//
//	liste_point L;
//
//	int fermer,buttx,butty,cond;
//
//	buttx = rcDepla.x;
//	butty = rcDepla.y;
//
//	cond = 0;
//
//	fermer = 1;
//	while(fermer)
//	{
//
//		if (SDL_PollEvent(&event))
//		{
//			if(event.key.keysym.sym == SDLK_ESCAPE)
//			{
//				fermer = 0;
//			}
//			if(event.type == SDL_MOUSEBUTTONUP)
//			{
//				if(event.button.button == SDL_BUTTON_LEFT)
//				{
//					if(tab[event.button.x / 32][event.button.y / 32].a == 1)
//					{
//						buttx = (event.button.x / 32) * 32;
//						butty = (event.button.y /32) * 32;
//						cond = 1;
//					}
//				}
//				if(event.button.button == SDL_BUTTON_RIGHT)
//				{
//					tab[event.button.x/32][event.button.y/32].a = 0;
//					tab[event.button.x/32][event.button.y/32].s = *CaseR;
//				}
//				if(event.button.button == SDL_BUTTON_MIDDLE)
//				{
//					tab[event.button.x/32][event.button.y/32].a = 1;
//					tab[event.button.x/32][event.button.y/32].s = *CaseN;
//				}
//
//			}
//		}
//
//		affichage_map(tab,screen);
//		deplacement_personnage(tab,screen,perso,&rcDepla,rcDeplaS,&L,buttx/32,butty/32,node,&cond);
//		SDL_BlitSurface(perso, &rcDeplaS, screen, &rcDepla);
//		SDL_UpdateRect(screen, 0, 0, 0, 0);
//	}
//	SDL_Quit();
//	return 0;
//}


