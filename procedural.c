/*************************/
/* procedural.c          */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/

#include "include.h"

object proba_object(int nb, object procedu, int dist)
{
  int plus;
  if (dist == 1)
    plus = 15;
  if (dist == 2)
    plus = 10;
  if (dist == 3)
    plus = 5;
  if (dist == 4)
    plus = 1;

  if (nb == 8)
    procedu.chene += plus;
  if (nb == 4)
    procedu.salade += plus;
  if (nb == 2)
    procedu.fraisier += plus;
  if (nb == 6)
    procedu.ble += plus;
  return procedu;
}

int proba(object procedu)
{
  int a;
  a = rand()%100;
  if (a<procedu.chene)
    return 8;
  a-=procedu.chene;
  if (a<procedu.salade)//ble
    return 4;
  a-=procedu.salade;
  if (a<procedu.fraisier)
    return 2;
  a-=procedu.fraisier;
  if (a<procedu.ble)
    return 6;
  a-=procedu.ble;
  return 0;
}


void generation_procedural(sol tab[COL][LIG])
{
  int col, lig, dc, dl;
  object procedu;
  for (col=1;col<COL-1;col++)
    for (lig=1;lig<LIG-1;lig++)
      {
	tab[col][lig].id=0;
	//initialisation variable structure object
	procedu.chene=10;
	procedu.salade=10;
	procedu.fraisier=10;
	procedu.ble=10;
	for (dl=-2; dl<3; dl++)
	  for (dc=-2; dc<3; dc++)
	    {
	      if (!dl || !dc) continue; // on traite pas la case elle meme
	      if (col+dc < 0 || col+dc > COL-1) continue; // on veut pas sortir du tableau
	      if (lig+dl < 0 || lig+dl > LIG-1) continue;
	      procedu=proba_object(tab[col+dc][lig+dl].id,procedu, abs(dc)+abs(dl));
	      tab[col][lig].id=proba(procedu);
	    }
      }


  for (col=COL-2;col>=1;col--)
    for (lig=LIG-2;lig>=1;lig--)
      {
	tab[col][lig].id=0;
	//initialisation variable structure object
	procedu.chene=0;
	procedu.salade=0;
	procedu.fraisier=0;
	procedu.ble=0;
	for (dl=-2; dl<3; dl++)
	  for (dc=-2; dc<3; dc++)
	    {
	      if (!dl || !dc) continue; // on traite pas la case elle meme
	      if (col+dc < 0 || col+dc > COL-1) continue; // on veut pas sortir du tableau
	      if (lig+dl < 0 || lig+dl > LIG-1) continue;
	      procedu=proba_object(tab[col+dc][lig+dl].id,procedu, abs(dc)+abs(dl));
	      tab[col][lig].id=proba(procedu);
	    }
      }

    /* MINE A SUPPRIMER */
    tab[2][2].id = 120;
    tab[2][3].id = 120;
    tab[2][4].id = 120;
    tab[3][2].id = 120;
    tab[3][3].id = 21;
    tab[3][4].id = 22;
    tab[4][2].id = 120;
    tab[4][3].id = 120;
    tab[4][4].id = 120;
    tab[3][3].ordre = action_miner;

}

