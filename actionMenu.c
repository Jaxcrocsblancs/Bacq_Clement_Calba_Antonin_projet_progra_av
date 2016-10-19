/*
 * actionMenu.c
 *
 *  Created on: 15 oct. 2016
 *      Author: cleme
 */
#include "include.h"
#include <assert.h>

void couper(sol tab[COL][LIG],int buttx, int butty, perso perso, int zoom, int *click,int action)
{
    if (tab[perso.but.x][perso.but.y].id > 0 && tab[perso.but.x][perso.but.y].id<20) // ne marche pas avec le zoom
	    {
    if((perso.pos.x  == perso.but.x) && (perso.pos.y == perso.but.y))
        {
	   	tab[perso.but.x][perso.but.y].item.id = tab[perso.but.x][perso.but.y].id;
	   	tab[perso.but.x][perso.but.y].id = 0;
	   	tab[perso.but.x][perso.but.y].ordre = 0;
	   	*click = 0;
	    }
	    }
}

perso ramasser(sol tab[COL][LIG], perso perso, int buttx, int butty, int zoom, int *click,int action)
{
    if(tab[perso.but.x][perso.but.y].item.id == perso.item.id || perso.item.id == 0 )
		{
        if((perso.pos.x == perso.but.x) && (perso.pos.y == perso.but.y))
            {
                perso.item.id = tab[perso.but.x][perso.but.y].item.id;
                perso.item.nb += tab[perso.but.x][perso.but.y].item.nb;
                tab[perso.but.x][perso.but.y].item.id = 0;
                tab[perso.but.x][perso.but.y].item.nb = 0;
                tab[perso.but.x][perso.but.y].ordre = 0;
                *click = 0;
            }
	}
	return perso;
}

perso deposer(sol tab[COL][LIG], perso perso, int buttx, int butty, int zoom, int *click,int action)
{
    if((tab[buttx][butty].item.id == perso.item.id || tab[buttx][butty].item.id == 0) && perso.item.id != 0  )
		{
            tab[buttx][butty].ordre = action;
            if((perso.pos.x== buttx) && (perso.pos.y== butty))
                {
                    tab[buttx][butty].item.id  = perso.item.id;
                    tab[buttx][butty].item.nb = perso.item.nb;
                    perso.item.id = 0;
                    perso.item.nb = 0;
                    tab[buttx][butty].ordre = 0;
                    *click = 0;
                }
        }
	return perso;
}

void miner(sol tab[COL][LIG], perso perso, int buttx, int butty, int *click,int action)
{
    int random_minerai;
     if (perso.but.x == perso.pos.x && perso.but.y == perso.pos.y && tab[buttx][butty].id == 21 )
     {
        random_minerai = rand()%2+20;
        if(tab[perso.pos.x][perso.pos.y+2].item.id == random_minerai || tab[perso.pos.x][perso.pos.y+2].item.id == 0)
        {
            tab[perso.pos.x][perso.pos.y+2].item.nb += 4;
            tab[perso.pos.x][perso.pos.y+2].item.id = random_minerai;
        }
        else
        {
            if(tab[perso.pos.x-1][perso.pos.y+2].item.id == random_minerai  || tab[perso.pos.x-1][perso.pos.y+2].item.id == 0)
                {
                    tab[perso.pos.x-1][perso.pos.y+2].item.nb += 4;
                    tab[perso.pos.x-1][perso.pos.y+2].item.id = random_minerai;
                }
            else
                {
                if(tab[perso.pos.x+1][perso.pos.y+2].item.id == random_minerai  || tab[perso.pos.x+1][perso.pos.y+2].item.id == 0)
                            {
                                tab[perso.pos.x+1][perso.pos.y+2].item.nb += 4;
                                tab[perso.pos.x+1][perso.pos.y+2].item.id = random_minerai;
                            }
                }
        }

        printf("minerai: %d\n", random_minerai);
     }

}

perso actionMenu(int action, sol tab[COL][LIG], SDL_Surface *screen,perso perso, liste_point *L, int buttx, int butty, int *cond, int zoom, int *click)
{

		switch(action)
		{
		case 1:
            if (tab[buttx][butty].id > 0 && tab[buttx][butty].id < 20 && tab[buttx][butty].ordre <1000) // ne marche pas avec le zoom
                {
                tab[buttx][butty].ordre = action;
                }
			couper(tab,buttx,butty,perso,zoom,click,action);
			break;
		case 2:
            if (tab[buttx][butty].item.id > 0 && (tab[buttx][butty].item.id == perso.item.id || perso.item.id == 0)) // ne marche pas avec le zoom
                {
                tab[buttx][butty].ordre = action;
                }
			perso = ramasser(tab,perso,buttx,butty,zoom,click,action);
			break;
		case 3:
			perso = deposer(tab,perso,buttx,butty,zoom,click,action);
			break;
        case 5:
            if (tab[buttx][butty].id == 21)
                {
                tab[buttx][butty].ordre = action;
                }
            miner(tab, perso, buttx, butty, click, action);
            break;
		}
	return perso;
}


perso cherche_action(sol tab[COL][LIG], perso perso, int *cond, int action)
{
    int nb, dl, dc;
    if (*cond == 0)
    for (nb=1;nb< COL-1;nb++)
        for (dl=-nb; dl<nb+1; dl++)
            for (dc=-nb; dc<nb+1; dc++)
            {
                if (perso.but.x != perso.pos.x && perso.but.y != perso.pos.y) continue;
                if (abs(dl)+abs(dc) != nb) continue;
                if (perso.pos.x+dc < 0 || perso.pos.x+dc > COL-1) continue; // on veut pas sortir du tableau
                if (perso.pos.y+dl < 0 || perso.pos.y+dl > LIG-1) continue;
                if (tab[perso.pos.x+dc][perso.pos.y+dl].id == 21) tab[perso.pos.x+dc][perso.pos.y+dl].ordre = 5;
                if (tab[perso.pos.x+dc][perso.pos.y+dl].ordre != action) continue;
                if (action == 2 && (tab[perso.pos.x+dc][perso.pos.y+dl].item.id != perso.item.id && perso.item.id != 0)) continue;
                if (tab[perso.pos.x+dc][perso.pos.y+dl].ordre < 1000) tab[perso.pos.x+dc][perso.pos.y+dl].ordre += 1000;
                perso.but.x = perso.pos.x+dc;
                perso.but.y = perso.pos.y+dl;
                *cond = 1;
                return perso;
            }
    return perso;
}
