

#include "include.h"


item remplis_item(int id, int nb, char c)
{
  // Reservation de la place memoire neccessaire pour une cellule :
  item p ;

  p.id = id;
  p.nb = nb;
  p.nom = c;

  return p;
}

liste_item l_videI (void)
{
  return NULL;
}

bool est_videI(liste_item L)
{
  return L == NULL;
}

item premI(liste_item L)
{
  return L->premier;
}

liste_item resteI(liste_item L)
{
  return L->reste;
}

void ecrire_premI(item a, liste_item L)
{
  L->premier = a ;
}

void ecrire_resteI(liste_item R, liste_item L)
{
  L->reste = R ;
}

liste_item consI(item a, liste_item L)
{
  liste_item M ;

  // Reservation de la place memoire neccessaire pour une cellule :
  M = malloc (sizeof (*M)) ;

  ecrire_prem(a,M);
  ecrire_reste(L,M);
  return M;
}

int presenceRI(item a, liste_item L)
{
  if(est_vide(L))
    {
      printf("non present\n");
      return 0;
    }
  if( (prem(L).id == a.id) & (prem(L).nb == a.nb) )
    {
      printf("present\n");
      return 1;
    }
  return presenceRI(a,reste(L));
}


liste_item supprimerRI(item a, liste_item L)
{
  if(est_vide(L))
    {
      return l_vide();
    }

  if((a.id == prem(L).id) & (a.nb == prem(L).nb) )
    {
      return supprimerRI(a,reste(L));
    }
  return cons(prem(L),supprimerRI(a,reste(L))) ;
}

void afficher_item_liste(liste_item L)
{
  if(est_vide(L))
    {
      printf("l_vide\n");
      return;
    }
  printf("(id:%d, nb:%d)\n",prem(L).id,prem(L).nb);
  return afficher_item_liste(reste(L));
}

liste_item renverser_listeI(liste_item L)
{
  liste_item R, M ;
  R = l_vide () ;
  M = L ;
  while (!est_vide(M))
    {
      R = cons (prem(M), R) ;
      M = reste (M) ;
    }
  return R ;
}


