/*
 * liste_point.c
 *
 *  Created on: 29 sept. 2016
 *      Author: cleme
 */

#include "liste_point.h"


point_cout remplisPoint(int col, int lig, int f)
{
	  // Reservation de la place memoire neccessaire pour une cellule :
	  point_cout p ;

	  p.col = col;
	  p.lig = lig;
	  p.f = f;

	  return p;
}

liste_point l_vide (void)
{
	return NULL;
}

bool est_vide(liste_point L)
{
	return L == NULL;
}

point_cout prem(liste_point L)
{
	return L->premier;
}

liste_point reste(liste_point L)
{
	return L->reste;
}

void ecrire_prem (point_cout a, liste_point L)
{
  L->premier = a ;
}

void ecrire_reste (liste_point R, liste_point L)
{
  L->reste = R ;
}

liste_point cons(point_cout a, liste_point L)
{
  liste_point M ;

  // Reservation de la place memoire neccessaire pour une cellule :
  M = malloc (sizeof (*M)) ;

  ecrire_prem(a,M);
  ecrire_reste(L,M);
  return M;
}

int presenceR(point_cout a, liste_point L)
{
	if(est_vide(L))
	{
		printf("non present\n");
		return 0;
	}
	if( (prem(L).col == a.col) & (prem(L).lig == a.lig) )
	{
		printf("present\n");
		return 1;
	}
	return presenceR(a,reste(L));
}



liste_point supprimerR(point_cout a, liste_point L) // MERCI MARCEAU
{
	if(est_vide(L))
	{
		return l_vide();
	}

	if((a.col == prem(L).col) & (a.lig == prem(L).lig) )
	{
		return supprimerR(a,reste(L));
	}
	return cons(prem(L),supprimerR(a,reste(L))) ;
}

point_cout plusPetitF(point_cout max,liste_point L)
{
	if(est_vide(L))
	{
		return max;
	}
	if(prem(L).f < max.f)
	{
		max = prem(L);
	}
	return plusPetitF(max,reste(L));
}

void afficher_point_liste(liste_point L)
{
	if(est_vide(L))
	{
		return;
	}
	printf("(%d, %d)\n",prem(L).col,prem(L).lig);
	return afficher_point_liste(reste(L));
}

liste_point renverser_liste(liste_point L)
{
	  liste_point R, M ;
	  R = l_vide () ;
	  M = L ;
	  while (!est_vide(M))
	    {
	      R = cons (prem(M), R) ;
	      M = reste (M) ;
	    }
	  return R ;

}




