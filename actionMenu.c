/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"
#include "assert.h"

void couper(sol tab[COL][LIG], perso perso)
{
    if (tab[perso.but.x][perso.but.y].id != 0)
	  if((perso.pos.x  == perso.but.x) && (perso.pos.y == perso.but.y))
	  {
		  tab[perso.but.x][perso.but.y].item.id = tab[perso.but.x][perso.but.y].id;
		  tab[perso.but.x][perso.but.y].id = 0;
		  tab[perso.but.x][perso.but.y].ordre = 0;
		  tab[perso.but.x][perso.but.y].item.nb = 4;
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

perso deposer(sol tab[COL][LIG], perso perso, int nb, int buttx, int butty, liste_stockpile *stockPile)
{
  if((perso.pos.x == buttx) && (perso.pos.y == butty))
	  if(perso.item.nb >= nb)
	  {
          *stockPile = changer_elem(buttx,butty,nb,*stockPile);
		  tab[buttx][butty].item.id  = perso.item.id;
		  tab[buttx][butty].item.nb += nb;
		  perso.item.nb -= nb;
		  tab[buttx][butty].ordre = 0;
		  if(perso.item.nb == 0)
			  perso.item.id = 0;
          perso.action = 0;
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
        perso.action = 0;
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

perso construire(sol tab[COL][LIG], perso perso, int ido, int nbi, int idi)
{
	int col,lig;
	for(col=-1;col<=1;col++)
		for(lig=-1;lig<=1;lig++)
			if( ((col == 0)&&(lig != 0)) || ((lig == 0)&&(col != 0)))
					if(perso.pos.x == perso.but.x + col  && perso.pos.y == perso.but.y + lig)
						if(perso.item.id == idi && perso.item.nb >= nbi)
						{
							tab[perso.but.x][perso.but.y].id = ido;
							tab[perso.but.x][perso.but.y].ordre = 0;
							perso.item.nb -= nbi;

							if(perso.item.nb == 0)
								perso.item.id = 0;
							return perso;
						}
	return perso;
}

void creerStockPile(sol tab[COL][LIG], liste_stockpile *stockPile, int id, int buttx, int butty)
{
	stockpile temp;
	tab[buttx][butty].id = 9;
	tab[buttx][butty].ordre = action_stockpile;
	temp = remplis_stockpile(id,0,buttx,butty);
	*stockPile = consS(temp,*stockPile);
}


perso chercheStockPile(sol tab[COL][LIG], perso perso, liste_stockpile *stockPile)
{
	if(!est_videS(*stockPile))
		if(premS(*stockPile).nb < 20)
		{
			perso = chercher_object(tab,perso,premS(*stockPile).id);

			if(perso.item.nb > 0)
			{
                tab[premS(*stockPile).col][premS(*stockPile).lig].ordre = action_deposer;
			}
		}
	return perso;
}

perso chercher_object(sol tab[COL][LIG], perso perso, int id)
{
	int nb, dl, dc;
	for (nb=0;nb< (COL-1)+(LIG-1);nb++)
	    for (dl=-nb; dl<nb+1; dl++)
	        for (dc=-nb; dc<nb+1; dc++)
	          {
	          if (perso.but.x != perso.pos.x && perso.but.y != perso.pos.y) continue;
	          if (abs(dl)+abs(dc) != nb) continue;
	          if (perso.pos.x+dc < 1 || perso.pos.x+dc > COL-2) continue; // on veut pas sortir du tableau
	          if (perso.pos.y+dl < 1 || perso.pos.y+dl > LIG-2) continue;
	          if (tab[perso.pos.x+dc][perso.pos.y+dl].item.id == id)
				  {
					  tab[perso.pos.x+dc][perso.pos.y+dl].ordre = action_ramasser;
				  }
	          }
	return perso;
}

liste_point pousser(sol tab[COL][LIG], liste_point plantation)
{
  point_cout mem;
  if (est_vide(plantation))
    return l_vide();
  if (prem(plantation).f > 100)
    {
      if (tab[prem(plantation).col][prem(plantation).lig].id != 0)
      {
        tab[prem(plantation).col][prem(plantation).lig].id += 1;
        tab[prem(plantation).col][prem(plantation).lig].ordre = action_couper;
      }
      return pousser(tab,reste(plantation));
    }
  mem = prem(plantation);
  mem.f += 1;
  ecrire_prem(mem,plantation);
  return cons(prem(plantation), pousser(tab, reste(plantation)));
}

perso faim(perso perso)
{
    perso.faim -= 1;
    return perso;
}

perso manger(sol tab[COL][LIG], perso perso)
{
    if((perso.pos.x  == perso.but.x) && (perso.pos.y == perso.but.y))
	  {
        while (tab[perso.but.x][perso.but.y].item.nb > 0 && perso.faim <550)
        {
        tab[perso.but.x][perso.but.y].item.nb -= 1;
        perso.faim += 50;
        if (tab[perso.but.x][perso.but.y].item.nb == 0)
            tab[perso.but.x][perso.but.y].item.id = 0;
        }
        perso.action = 0;
     }
     return perso;
}

void init_recette(recette recette[100])
{
    recette[0].composant_1.id = bois;
    recette[0].composant_1.nb = 12;
    recette[0].composant_2.id = coton;
    recette[0].composant_2.nb = 4;
}

perso fabrication(sol tab[COL][LIG], perso perso, int commande, workshop atelier, recette recette[100])
{
    int d1, d2, d3;

    for (d1=0; d1<3; d1++)
        if (recette[commande].composant_1.id == atelier.coffre[d1].id)
        {
            for (d2=0; d2<3; d2++)
                if (recette[commande].composant_2.id == atelier.coffre[d2].id)
                {
                    for (d3=0; d3<3; d3++)
                        if (recette[commande].composant_3.id == atelier.coffre[d3].id)
                        {
                            if((perso.pos.x  == perso.but.x) && (perso.pos.y == perso.but.y))
                                printf("test\n");
                        }
                        else
                        {
                            if ((perso.item.id == recette[commande].composant_3.id) && (perso.item.nb == recette[commande].composant_3.nb))
                                {
                                perso.action = action_deposer;
                                perso.but.x = atelier.x;
                                perso.but.y = atelier.y;
                                }
                            else
                            {
                                    perso = chercher_object(tab,perso,recette[commande].composant_3.id);
                            }
                        }
                }
                else
                {
                    if ((perso.item.id == recette[commande].composant_2.id) && (perso.item.nb == recette[commande].composant_2.nb))
                        {
                        perso.action = action_deposer;
                        perso.but.x = atelier.x;
                        perso.but.y = atelier.y;
                        }
                    else
                        {
                        perso = chercher_object(tab,perso,recette[commande].composant_2.id);
                        }
                }
        }
        else
        {
            if ((perso.item.id == recette[commande].composant_1.id) && (perso.item.nb == recette[commande].composant_1.nb))
                {
                perso.action = action_deposer;
                perso.but.x = atelier.x;
                perso.but.y = atelier.y;
                }
            else
                perso = chercher_object(tab,perso,recette[commande].composant_1.id);
        }
}

void actionMenu(int action, sol tab[COL][LIG], int buttx, int butty, liste_stockpile *stockPile)
{
 if (buttx <1 || buttx > COL-2 || butty <1 || butty > LIG-2) return;
  switch(action)
    {
    case action_couper_bois:
        if (tab[buttx][butty].id == bois && tab[buttx][butty].id < 20 && tab[buttx][butty].ordre <1000)
            tab[buttx][butty].ordre = action_couper;
        break;
    case action_couper_plante:
        if (((tab[buttx][butty].id == fraise) || (tab[buttx][butty].id == coton) || (tab[buttx][butty].id == bles)) && tab[buttx][butty].id < 20 && tab[buttx][butty].ordre <1000)
            tab[buttx][butty].ordre = action_couper;
        break;
    case action_ramasser:
      if (tab[buttx][butty].item.id > 0)
        tab[buttx][butty].ordre = action;
      break;
    case action_deposer:
       //if ((tab[buttx][butty].item.id == 0  || tab[buttx][butty].item.id == perso.item.id) && perso.item.id > 0 )
            tab[buttx][butty].ordre = action;
      break;
   /* case 4:
    	if(tab[buttx][butty].item.id == 0 && tab[buttx][butty].id < 100)
    		tab[buttx][butty].ordre = action;
    	break;*/
    case action_planter_fraise:
      if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
        tab[buttx][butty].ordre = action;
      break;
    case action_planter_coton:
        if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
            tab[buttx][butty].ordre = action;
        break;
    case action_planter_ble:
        if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
            tab[buttx][butty].ordre = action;
        break;
    case action_planter_bois:
      if(tab[buttx][butty].id == 0 && tab[buttx][butty].ordre == 0)
        tab[buttx][butty].ordre = action;
      break;
    case action_stockpile:
        if (tab[buttx][butty].id == 0)
    	creerStockPile(tab,stockPile,bois,buttx,butty);
    	break;
    case action_fabriquer:
        if (tab[buttx][butty].id == 0)
            tab[buttx][butty].id = 100;
    	break;
  /*  case action_fabriquer+1:
        if (tab[buttx][butty].id == 100)
            tab[buttx][butty].ordre = action_fabriquer;
    	break;*/
    case annuler:
        tab[buttx][butty].ordre = 0;
    }
 return;
}

perso actionPerso(sol tab[COL][LIG],perso perso, liste_point *plantation, liste_stockpile *stockPile, int *cond)
{
    switch(perso.action)
    {
        case action_couper:
          couper(tab,perso);
          break;
        case action_ramasser:
          perso = ramasser(tab,perso);
          break;
        case action_deposer:
        	perso  = deposer(tab,perso,perso.item.nb,perso.but.x,perso.but.y, stockPile);
          break;
		case 4 :
			perso = construire(tab,perso,101,2,1);
			break;
        case action_planter_fraise:
          planter(tab, perso, pousse_fraise, plantation);
          break;
        case action_planter_coton:
          planter(tab, perso, pousse_coton, plantation);
          break;
        case action_planter_ble:
          planter(tab, perso, pousse_ble, plantation);
          break;
        case action_planter_bois:
          planter(tab, perso, pousse_bois, plantation);
          break;
        case 9:
          miner(tab, perso);
          break;
        case action_manger:
          perso = manger(tab, perso);
          break;
        case action_stockpile:
          perso = chercheStockPile(tab,perso,stockPile);
          break;
       /* case action_fabriquer:
          perso = fabrication(tab,perso,0 , atelier, recette);
          break;*/
    }
  return perso;
}

void cherche_action(sol tab[COL][LIG], perso perso[NB_Perso], int cond[NB_Perso])
{

  int nb, dl, dc, action, id_perso, col, lig, act;
  int action_tab[100];
  for (act = 0; act <100; act++)
    action_tab[act] = 0;

  for (col = 0; col < COL; col++)
    for (lig = 0; lig <LIG; lig++)
        for (act = 0; act <100; act++)
            if (tab[col][lig].ordre == act)
                action_tab[act] = 1;

  for (id_perso = 0;id_perso <NB_Perso; id_perso++)
      if (cond[id_perso] == 0)
        if (perso[id_perso].faim > 100)// test nourriture
            {
            perso[id_perso].action = action_stockpile;
            for (action = 0; action <100; action++)
                if (action_tab[perso[id_perso].travail[action]] == 1)
                    for (nb=0; nb<(COL-1)+(LIG-1);nb++)
                        for (dl=-nb; dl<nb+1; dl++)
                            for (dc=-nb; dc<nb+1; dc++)
                            {
                            if (perso[id_perso].but.x != perso[id_perso].pos.x && perso[id_perso].but.y != perso[id_perso].pos.y) continue;
                            if (abs(dl)+abs(dc) != nb) continue;
                            if (perso[id_perso].pos.x+dc < 1 || perso[id_perso].pos.x+dc > COL-2) continue; // on veut pas sortir du tableau
                            if (perso[id_perso].pos.y+dl < 1 || perso[id_perso].pos.y+dl > LIG-2) continue;

                            if (tab[perso[id_perso].pos.x+dc][perso[id_perso].pos.y+dl].ordre != perso[id_perso].travail[action]) continue;
                            if (perso[id_perso].travail[action] == 2 && (tab[perso[id_perso].pos.x+dc][perso[id_perso].pos.y+dl].item.id != perso[id_perso].item.id && perso[id_perso].item.id != 0)) continue;
                            if (tab[perso[id_perso].pos.x+dc][perso[id_perso].pos.y+dl].ordre < 1000) tab[perso[id_perso].pos.x+dc][perso[id_perso].pos.y+dl].ordre += 1000;
                            if (tab[perso[id_perso].pos.x+dc][perso[id_perso].pos.y+dl].id == 100) tab[perso[id_perso].pos.x+dc][perso[id_perso].pos.y+dl].ordre = action_fabriquer;

                            perso[id_perso].but.x = perso[id_perso].pos.x+dc;
                            perso[id_perso].but.y = perso[id_perso].pos.y+dl;
                            cond[id_perso] = 1;

                            perso[id_perso].action = perso[id_perso].travail[action];
                            dc = nb;
                            dl = nb;
                            nb = (COL-1)+(LIG-1)-1;
                            action = 100-1;
                          }
            }
            else
            {
                for (nb=1;nb< (COL-1)+(LIG-1);nb++)
                    for (dl=-nb; dl<nb+1; dl++)
                         for (dc=-nb; dc<nb+1; dc++)
                         {
                            if (abs(dl)+abs(dc) != nb) continue;
                            if (perso[id_perso].pos.x+dc < 1 || perso[id_perso].pos.x+dc > COL-2) continue; // on veut pas sortir du tableau
                            if (perso[id_perso].pos.y+dl < 1 || perso[id_perso].pos.y+dl > LIG-2) continue;
                            if (tab[perso[id_perso].pos.x+dc][perso[id_perso].pos.y+dl].item.id == fraise)
                                {
                                perso[id_perso].but.x = perso[id_perso].pos.x+dc;
                                perso[id_perso].but.y = perso[id_perso].pos.y+dl;
                                cond[id_perso] = 1;
                                perso[id_perso].action = action_manger;
                                dc = nb;
                                dl = nb;
                                nb = (COL-1)+(LIG-1)-1;
                                }
                         }
            }

}

void rectangle(int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, int action, sol sol[COL][LIG], liste_stockpile *stockPile)
{
  int x, y;
  if (gauche_maintenu == 0)
    {
      if (*gauche_maintenu_x - *buttx < 0)
        for (x = *gauche_maintenu_x; x <=  *buttx ; x++)
          if (*gauche_maintenu_y - *butty <0 )
            for (y = *gauche_maintenu_y; y <=  *butty ; y++)
              actionMenu(action,sol,x,y,stockPile);
          else
            for (y = *gauche_maintenu_y; y >=  *butty ; y--)
              actionMenu(action,sol,x,y,stockPile);
      else
        for (x = *gauche_maintenu_x; x >=  *buttx ; x--)
          if (*gauche_maintenu_y - *butty <0 )
            for (y = *gauche_maintenu_y; y <=  *butty ; y++)
              actionMenu(action,sol,x,y,stockPile);
          else
            for (y = *gauche_maintenu_y; y >=  *butty ; y--)
              actionMenu(action,sol,x,y,stockPile);
      *gauche_maintenu_x = 0;
      *gauche_maintenu_y = 0;
      *buttx = 0;
      *butty = 0;
    }
}
