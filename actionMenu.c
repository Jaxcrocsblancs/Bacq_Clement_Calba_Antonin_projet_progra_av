/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

void couper(sol tab[COL][LIG], perso perso)
{
  if (tab[perso.but.x][perso.but.y].id > 0 && tab[perso.but.x][perso.but.y].id<20) // ne marche pas avec le zoom
    if((perso.pos.x  == perso.but.x) && (perso.pos.y == perso.but.y))
      {
	tab[perso.but.x][perso.but.y].item.id = tab[perso.but.x][perso.but.y].id;
	tab[perso.but.x][perso.but.y].id = 0; 
	tab[perso.but.x][perso.but.y].item.nb = 4;
	tab[perso.but.x][perso.but.y].ordre = 0;
      }
}

perso ramasser(sol tab[COL][LIG], perso perso)
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
	}
    }
  return perso;
}

perso deposer(sol tab[COL][LIG], perso perso, int action)
{
  if((perso.pos.x== perso.but.x) && (perso.pos.y== perso.but.y))
    {
      tab[perso.but.x][perso.but.y].item.id  = perso.item.id;
      tab[perso.but.x][perso.but.y].item.nb = perso.item.nb;
      perso.item.id = 0;
      perso.item.nb = 0;
      tab[perso.but.x][perso.but.y].ordre = 0;
    }
  return perso;
}

void miner(sol tab[COL][LIG], perso perso)
{
  int random_minerai;
  if (perso.but.x == perso.pos.x && perso.but.y == perso.pos.y && tab[perso.but.x][perso.but.y].id == 21 )
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
    }

}

void planter(sol tab[COL][LIG], perso perso, int action, liste_point *plantation)
{
  if ((perso.but.x == perso.pos.x) && (perso.but.y == perso.pos.y) && tab[perso.but.x][perso.but.y].ordre !=0)
    {
      point_cout Case;
      tab[perso.but.x][perso.but.y].id = action;
      tab[perso.but.x][perso.but.y].ordre = 0;
      Case = remplisPoint(perso.but.x, perso.but.y, 0);
      *plantation = cons(Case, *plantation);
    }
}

liste_point pousser(sol tab[COL][LIG], liste_point plantation)
{
  point_cout mem;
  if (est_vide(plantation))
    return l_vide();
  if (prem(plantation).f > 100)
    {
      tab[prem(plantation).col][prem(plantation).lig].id -= 4;
      return pousser(tab,reste(plantation));
    }
  mem = prem(plantation);
  mem.f += 1;
  ecrire_prem(mem,plantation);
  return cons(prem(plantation), pousser(tab, reste(plantation)));
}

void actionMenu(int action, sol tab[COL][LIG],perso perso, int buttx, int butty)
{
 if (buttx <1 || buttx > COL-2 || butty <1 || butty > LIG-2) return;
  switch(action)
    {
    case 1:
        if (tab[buttx][butty].id > 0 && tab[buttx][butty].id < 20 && tab[buttx][butty].ordre <1000) // ne marche pas avec le zoom
            tab[buttx][butty].ordre = action;
        break;
    case 2:
      if (tab[buttx][butty].item.id > 0 && (tab[buttx][butty].item.id == perso.item.id || perso.item.id == 0)) // ne marche pas avec le zoom
        tab[buttx][butty].ordre = action;
      break;
    case 3:
     if (tab[buttx][butty].item.id == 0  || tab[buttx][butty].item.id == perso.item.id) // ne marche pas avec le zoom
       tab[buttx][butty].ordre = action;
      break;
    case 5:
      if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
        tab[buttx][butty].ordre = action;
      break;
    case 6:
        if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
            tab[buttx][butty].ordre = action;
        break;
    case 7:
        if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
            tab[buttx][butty].ordre = action;
        break;
    case 8:
      if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
	tab[buttx][butty].ordre = action;
      break;
    }
 return;
}

perso actionPerso(sol tab[COL][LIG],perso perso, liste_point *plantation)
{

    switch(perso.action)
    {
        case 1:
          couper(tab,perso);
          break;
        case 2:
          perso = ramasser(tab,perso);
          break;
        case 3:
          perso = deposer(tab,perso, perso.action);
          break;
        case 5:
          planter(tab, perso, perso.action, plantation);
          break;
        case 6:
          planter(tab, perso,  perso.action, plantation);
          break;
        case 7:
          planter(tab, perso,  perso.action, plantation);
          break;
        case 8:
          planter(tab, perso, perso.action, plantation);
          break;
        case 9:
          miner(tab, perso);
          break;
    }
  return perso;
}

perso cherche_action(sol tab[COL][LIG], perso perso, int *cond)
{
  int nb, dl, dc, action;
  if (*cond == 0)
    for (action = 1; action <11; action++)
        for (nb=1;nb< (COL-1)+(LIG-1);nb++)
            for (dl=-nb; dl<nb+1; dl++)
                for (dc=-nb; dc<nb+1; dc++)
                {
                  if (perso.but.x != perso.pos.x && perso.but.y != perso.pos.y) continue;
                  if (abs(dl)+abs(dc) != nb) continue;
                  if (perso.pos.x+dc < 1 || perso.pos.x+dc > COL-2) continue; // on veut pas sortir du tableau
                  if (perso.pos.y+dl < 1 || perso.pos.y+dl > LIG-2) continue;
                  if (tab[perso.pos.x+dc][perso.pos.y+dl].id == 21) tab[perso.pos.x+dc][perso.pos.y+dl].ordre = 9;
                  if (tab[perso.pos.x+dc][perso.pos.y+dl].ordre != action) continue;
                  if (action == 2 && (tab[perso.pos.x+dc][perso.pos.y+dl].item.id != perso.item.id && perso.item.id != 0)) continue;
                  if (tab[perso.pos.x+dc][perso.pos.y+dl].ordre < 1000) tab[perso.pos.x+dc][perso.pos.y+dl].ordre += 1000;
                  perso.but.x = perso.pos.x+dc;
                  perso.but.y = perso.pos.y+dl;
                  *cond = 1;
                  perso.action = action;
                  return perso;
                }
  return perso;
}

perso rectangle(int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, perso perso, int action, sol sol[COL][LIG])
{
  int x, y;
  if (gauche_maintenu == 0)
    {
      if (*gauche_maintenu_x - *buttx < 0)
	for (x = *gauche_maintenu_x; x <=  *buttx ; x++)
	  if (*gauche_maintenu_y - *butty <0 )
	    for (y = *gauche_maintenu_y; y <=  *butty ; y++)
	      actionMenu(action,sol,perso,x,y);
	  else
	    for (y = *gauche_maintenu_y; y >=  *butty ; y--)
	      actionMenu(action,sol,perso,x,y);
      else
	for (x = *gauche_maintenu_x; x >=  *buttx ; x--)
	  if (*gauche_maintenu_y - *butty <0 )
	    for (y = *gauche_maintenu_y; y <=  *butty ; y++)
	      actionMenu(action,sol,perso,x,y);
	  else
	    for (y = *gauche_maintenu_y; y >=  *butty ; y--)
	      actionMenu(action,sol,perso,x,y);
      *gauche_maintenu_x = 0;
      *gauche_maintenu_y = 0;
      *buttx = 0;
      *butty = 0;
    }
  return perso;
}
