/*
 * liste_stockpile.c
 *
 *  Created on: 31 oct. 2016
 *      Author: cleme
 */

#include "include.h"

stockpile remplis_stockpile(int id, int nb, int col, int lig)
{
  stockpile s ;

  s.id = id;
  s.nb = nb;
  s.col = col;
  s.lig = lig;

  return s;
}

liste_stockpile l_videS(void)
{
  return NULL;
}

int est_videS(liste_stockpile L)
{
	if(L == NULL)
		return 1;
	return 0;
}

stockpile premS(liste_stockpile L)
{
	return L->premier;
}
liste_stockpile resteS(liste_stockpile L)
{
  return L->reste;
}

void ecrire_premS(stockpile a, liste_stockpile L)
{
  L->premier = a ;
}

void ecrire_resteS(liste_stockpile R, liste_stockpile L)
{
  L->reste = R ;
}

liste_stockpile consS(stockpile a, liste_stockpile L)
{
  liste_stockpile M ;

  // Reservation de la place memoire neccessaire pour une cellule :
  M = malloc (sizeof (*M)) ;

  ecrire_premS(a,M);
  ecrire_resteS(L,M);
  return M;
}

liste_stockpile supprimerS(stockpile a, liste_stockpile L)
{
  if(est_videS(L))
    {
      return l_videS();
    }

  if((a.col == premS(L).col && a.lig == premS(L).lig) )
    {
      return supprimerS(a,resteS(L));
    }
  return consS(premS(L),supprimerS(a,resteS(L))) ;
}

void afficher_stockpile_liste(liste_stockpile L)
{
  if(est_videS(L))
    {
      printf("l_vide\n");
      return;
    }
  printf("(col: %d, lig: %d, id:%d, nb:%d)\n",premS(L).col, premS(L).lig ,premS(L).id,premS(L).nb);
  return afficher_stockpile_liste(resteS(L));
}

liste_stockpile changer_elem(int col, int lig, int nb, liste_stockpile L)
{
	if(!est_videS(L))
	{
		if(premS(L).col == col && premS(L).lig == lig)
		{
			stockpile temp;
			temp = premS(L);
			temp.nb = nb;
			ecrire_premS(temp,L);
			return L;
		}
		return changer_elem(col,lig,nb,resteS(L));
	}
}

liste_stockpile ecrire_prem_nb(int nb, liste_stockpile L)
{
	L->premier.nb = nb;
	return L;
}

stockpile rechercher_elem(int col, int lig, liste_stockpile L)
{
	if(!est_videS(L))
	{
		if(premS(L).col == col && premS(L).lig == lig)
			return premS(L);
		return rechercher_elem(col,lig,resteS(L));
	}
}

liste_stockpile renverser_listeS(liste_stockpile L)
{
  liste_stockpile R, M ;
  R = l_videS() ;
  M = L ;
  while (!est_videS(M))
    {
      R = consS(premS(M), R) ;
      M = resteS(M) ;
    }
  return R ;
}

liste_stockpile snoc_prem(liste_stockpile L) //passe le premier element de la liste a la fin de la liste
{
	if(est_videS(L))
		return l_videS();

	L = snocS(premS(L),L);
	L = resteS(L);
	return L;
}


liste_stockpile snocS(stockpile a, liste_stockpile L)// insere un element a la fin de la liste;
{
	if(est_videS(L))
		return consS(a,l_videS());

	return consS(premS(L),snocS(a,resteS(L)));
}

void free_liste_stockpile(liste_stockpile L)
{
    if (est_videS(L))
        return;
    free_liste_stockpile(resteS(L));
    free(L); // MAGIC MARCEAU
}

liste_stockpile copy(liste_stockpile L)
{
    if(est_videS(L))
		return l_videS();
	return consS(premS(L),copy(resteS(L)));
}

