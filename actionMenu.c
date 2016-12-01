/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

void couper(sol tab[COL][LIG], perso perso)
{
    int dc, dl, nb;
    if (tab[perso.but.x][perso.but.y].id != 0)
	  if((perso.pos.x  == perso.but.x) && (perso.pos.y == perso.but.y))
	  {
        for (nb=1;nb>=0;nb--)
            for (dl=-nb; dl<nb+1; dl++)
              for (dc=-nb; dc<nb+1; dc++)
                {
                    if (abs(dl)+abs(dc) != nb) continue;
                    if (tab[perso.but.x+dc][perso.but.y+dl].item.id == tab[perso.but.x][perso.but.y].id)
                    {
                      tab[perso.but.x+dc][perso.but.y+dl].item.id = tab[perso.but.x][perso.but.y].id;
                      tab[perso.but.x][perso.but.y].id = 0;
                      tab[perso.but.x][perso.but.y].ordre = 0;
                      tab[perso.but.x+dc][perso.but.y+dl].item.nb += 4;
                      return;
                    }
                }
        for (nb=0;nb<10;nb++)
            for (dl=-nb; dl<nb+1; dl++)
              for (dc=-nb; dc<nb+1; dc++)
                {
                    if (abs(dl)+abs(dc) != nb) continue;
                    if (tab[perso.but.x+dc][perso.but.y+dl].item.id == 0)
                    {
                      tab[perso.but.x+dc][perso.but.y+dl].item.id = tab[perso.but.x][perso.but.y].id;
                      tab[perso.but.x][perso.but.y].id = 0;
                      tab[perso.but.x][perso.but.y].ordre = 0;
                      tab[perso.but.x+dc][perso.but.y+dl].item.nb += 4;
                      return;
                    }
                }
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

perso deposer(sol tab[COL][LIG], perso perso, int nb, liste_stockpile *stockPile)
{
  if((perso.pos.x == perso.but.x) && (perso.pos.y == perso.but.y))
  {
	  if(perso.item.nb > 0)
		  if(premS(*stockPile).id == perso.item.id)
		  {
			  int temp;
			  temp = max_stock - premS(*stockPile).nb;

			  if(perso.item.id >= temp)
			  {
				  *stockPile = ecrire_prem_nb(premS(*stockPile).nb + temp,*stockPile);
				  perso.item.nb -= temp;

//				  *stockPile = snoc_prem(*stockPile);
			  }
			  else
			  {
				  *stockPile = ecrire_prem_nb(premS(*stockPile).nb + nb,*stockPile);
				  perso.item.nb = 0;
			  }
			  tab[perso.but.x][perso.but.y].ordre = 0;
			  if(perso.item.nb == 0)
				  perso.item.id = 0;
		  }
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
			{
				if(perso.pos.x == perso.but.x + col  && perso.pos.y == perso.but.y + lig)
					if(perso.item.id == idi && perso.item.nb >= nbi)
					{
						tab[perso.but.x][perso.but.y].id = ido;
						perso.item.nb -= nbi;

						if(perso.item.nb == 0)
							perso.item.id = 0;
					}
				tab[perso.but.x][perso.but.y].ordre = 0;
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
	tab[buttx][butty].ordre = 0;
}


liste_stockpile chercheStockPile(sol tab[COL][LIG], perso perso, liste_stockpile stockPile)
{
	if(!est_videS(stockPile))
	{
		if(premS(stockPile).nb < max_stock)
		{
			perso = chercher_object(tab,perso,premS(stockPile).id);

			if(perso.item.nb > 0)
			{
				tab[premS(stockPile).col][premS(stockPile).lig].ordre = action_deposer;
			}
		}
		else
		{
			stockPile = snoc_prem(stockPile);
		}
	}
	return stockPile;
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
				  if (tab[perso.pos.x+dc][perso.pos.y+dl].item.id == id && id != 0)
				  {
					  tab[perso.pos.x+dc][perso.pos.y+dl].ordre = action_ramasser;
//					  return perso;
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
       if (tab[buttx][butty].item.id == 9)
            tab[buttx][butty].ordre = action;
      break;
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
    case action_stockpile_fraise:
        if(tab[buttx][butty].id == 0)
            creerStockPile(tab,stockPile,fraise,buttx,butty);
    	break;
    case action_stockpile_coton:
        if(tab[buttx][butty].id == 0)
            creerStockPile(tab,stockPile,coton,buttx,butty);
    	break;
    case action_stockpile_bles:
        if(tab[buttx][butty].id == 0)
            creerStockPile(tab,stockPile,bles,buttx,butty);
    	break;
    case action_stockpile_bois:
        if(tab[buttx][butty].id == 0)
            creerStockPile(tab,stockPile,bois,buttx,butty);
    	break;
    case action_mur_bois:
    	if(tab[buttx][butty].id == 0 && tab[buttx][butty].item.id == 0 && tab[buttx][butty].ordre == 0)
    		tab[buttx][butty].ordre = action;
    	break;
    case annuler:
        tab[buttx][butty].ordre = 0;
    }
 return;
}

perso actionPerso(sol tab[COL][LIG],perso perso, liste_point *plantation, liste_stockpile *stockPile)
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
        	perso  = deposer(tab,perso,perso.item.nb,stockPile);
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
        case action_miner:
          miner(tab, perso);
          break;
        case action_manger:
          perso = manger(tab, perso);
          break;
        case action_stockpile:
          *stockPile = chercheStockPile(tab,perso,*stockPile);
          break;
        case action_mur_bois:
        	perso = construire(tab,perso,mur_bois,2,bois);
        	break;
    }
  return perso;
}

void cherche_action(sol tab[COL][LIG], perso perso[NB_Perso])
{
  int nb, dl, dc, action, id_perso, col, lig, act, vide;
  int action_tab[100];

  vide = 0;
  for (act = 0; act <100; act++)
    action_tab[act] = 0;

  for (col = 0; col < COL; col++)
    for (lig = 0; lig <LIG; lig++)
        for (act = 1; act <100; act++)
            if (tab[col][lig].ordre == act)
            {
            action_tab[act] += 1;
            vide = 1;
            }

    if (vide ==0)
    {
    	for (id_perso = 0;id_perso <NB_Perso; id_perso++)
    	      if (perso[id_perso].cond == 0)
    	      {
    	    	  perso[id_perso].action = action_stockpile;
    	      }
        return;
    }


  for (id_perso = 0;id_perso <NB_Perso; id_perso++)
      if (perso[id_perso].cond == 0)
      {
        if (perso[id_perso].faim > 100)// test nourriture
            {
            perso[id_perso].action = action_stockpile;
            for (action = 0; action <100; action++)
                if (action_tab[perso[id_perso].travail[action]] > 0 )
                {
                    action_tab[perso[id_perso].travail[action]] -= 1;
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

                            perso[id_perso].but.x = perso[id_perso].pos.x+dc;
                            perso[id_perso].but.y = perso[id_perso].pos.y+dl;
                            perso[id_perso].cond = 1;

                            perso[id_perso].action = perso[id_perso].travail[action];
                            dc = nb;
                            dl = nb;
                            nb = (COL-1)+(LIG-1)-1;
                            action = 100-1;
                          }
                }
            }
            else
            {
            	assert(0);
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
                                perso[id_perso].cond = 1;
                                perso[id_perso].action = action_manger;
                                dc = nb;
                                dl = nb;
                                nb = (COL-1)+(LIG-1)-1;
                                }
                         }
            }
      }
}

void rectangle(int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, int action, sol sol[COL][LIG], liste_stockpile *stockPile)
{
  int x, y;
  //printf("rect: %d, %d, %d, %d\n", *gauche_maintenu_x,*gauche_maintenu_y, *buttx, *butty);
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
