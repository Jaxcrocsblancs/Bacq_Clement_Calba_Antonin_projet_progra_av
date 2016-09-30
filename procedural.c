/*************************/
/* procedural.c          */
/* auteur : Bacp Clement */
/* et Calba Antonin      */
/*************************/

#include "include.h"

struct object
{
  int chene;
  int pommier;
  int fraisier;
  int ble;
};


object proba_object(int nb, object procedu, int dist)
{
  int plus;
  if (dist == 1)
    plus = 12;
  if (dist == 2)
    plus = 7;
  if (dist == 3)
    plus = 4;
  if (dist == 4)
    plus = 1;

  if (nb == 1)
    procedu.chene += plus;
  if (nb == 2) 
    procedu.pommier += plus;
  if (nb == 3)
    procedu.fraisier += plus;
  if (nb == 4)
    procedu.ble += plus;
  return procedu;
}

int proba(object procedu)
{
  int a;
  a = rand()%100;
  if (a<procedu.chene)
    return 1;
  a-=procedu.chene;
  
  if (a<procedu.pommier)
    return 2;
  a-=procedu.pommier;
  if (a<procedu.fraisier)
    return 3;
  a-=procedu.fraisier;
  if (a<procedu.ble)
    return 4;
  a-=procedu.ble;
  return 0;
}

 
void generation_procedural(int tab[COL][LIG])
{
  int col, lig;
  object procedu;
  for (col=0;col<COL;col++)
    for (lig=0;lig<LIG;lig++)
      {
	tab[col][lig]=0;
	//initialisation variable structure object
	procedu.chene=10;
	procedu.pommier=10;
	procedu.fraisier=10;
	procedu.ble=10;

	if (col>1)
	  {
	    if (lig>1)
	      procedu=proba_object(tab[col-2][lig-2],procedu, 4);
	    if (lig>0)
	      procedu=proba_object(tab[col-2][lig-1],procedu, 3);
	    proba_object(tab[col-2][lig],procedu, 2);
	    if (lig<LIG-2)
	      procedu=proba_object(tab[col-2][lig+1],procedu, 3);
	    if (lig<LIG-1)
	      procedu=proba_object(tab[col-2][lig+2],procedu, 4);
	  }

	if (col>0)
	  {
	    if (lig>1)
	      procedu=proba_object(tab[col-1][lig-2],procedu, 3);
	    if (lig>0)
	      procedu=proba_object(tab[col-1][lig-1],procedu, 2);
	    proba_object(tab[col-1][lig],procedu, 1);
	    if (lig<LIG-2)
	      procedu=proba_object(tab[col-1][lig+1],procedu, 2);
	    if (lig<LIG-1)
	      procedu=proba_object(tab[col-1][lig+2],procedu, 3);
	  }

	if (lig>1)
	  procedu=proba_object(tab[col][lig-2],procedu, 2);
	if (lig>0)
	  procedu=proba_object(tab[col][lig-1],procedu, 1);
	if (lig<LIG-2)
	  procedu=proba_object(tab[col][lig+1],procedu, 1);
	if (lig<LIG-1)
	  procedu=proba_object(tab[col][lig+2],procedu, 2);

	if (col<COL-2)
	  {
	    if (lig>1)
	      procedu=proba_object(tab[col+1][lig-2],procedu, 3);
	    if (lig>0)
	      procedu=proba_object(tab[col+1][lig-1],procedu, 2);

	    proba_object(tab[col+1][lig],procedu, 1);

	    if (lig<LIG-2)
	      procedu=proba_object(tab[col+1][lig+1],procedu, 2);
	    if (lig<LIG-1)
	      procedu=proba_object(tab[col+1][lig+2],procedu, 3);
	  }

	if (col<COL-1)
	  {
	    if (lig>1)
	      procedu=proba_object(tab[col+2][lig-2],procedu, 4);
	    if (lig>0)
	      procedu=proba_object(tab[col+2][lig-1],procedu, 3);
	    proba_object(tab[col+2][lig],procedu, 2);
	    if (lig<LIG-2)
	      procedu=proba_object(tab[col+2][lig+1],procedu, 3);
	    if (lig<LIG-1)
	      procedu=proba_object(tab[col+2][lig+2],procedu, 4);
	  }
	tab[col][lig]=proba(procedu);
      }
  
  //Dans l'autre sens
  for (col=COL;col>0;col--)
    for (lig=LIG;lig>0;lig--)
      {

	//initialisation variable structure object
	procedu.chene=0;
	procedu.pommier=0;
	procedu.fraisier=0;
	procedu.ble=0;
	if (tab[col][lig]!=0)
	  {
	    if (col>1)
	      {
		if (lig>1)
		  procedu=proba_object(tab[col-2][lig-2],procedu, 4);
		if (lig>0)
		  procedu=proba_object(tab[col-2][lig-1],procedu, 3);
		proba_object(tab[col-2][lig],procedu, 2);
		if (lig<LIG-2)
		  procedu=proba_object(tab[col-2][lig+1],procedu, 3);
		if (lig<LIG-1)
		  procedu=proba_object(tab[col-2][lig+2],procedu, 4);
	      }

	    if (col>0)
	      {
		if (lig>1)
		  procedu=proba_object(tab[col-1][lig-2],procedu, 3);
		if (lig>0)
		  procedu=proba_object(tab[col-1][lig-1],procedu, 2);
		proba_object(tab[col-1][lig],procedu, 1);
		if (lig<LIG-2)
		  procedu=proba_object(tab[col-1][lig+1],procedu, 2);
		if (lig<LIG-1)
		  procedu=proba_object(tab[col-1][lig+2],procedu, 3);
	      }

	    if (lig>1)
	      procedu=proba_object(tab[col][lig-2],procedu, 2);
	    if (lig>0)
	      procedu=proba_object(tab[col][lig-1],procedu, 1);
	    if (lig<LIG-2)
	      procedu=proba_object(tab[col][lig+1],procedu, 1);
	    if (lig<LIG-1)
	      procedu=proba_object(tab[col][lig+2],procedu, 2);

	    if (col<COL-2)
	      {
		if (lig>1)
		  procedu=proba_object(tab[col+1][lig-2],procedu, 3);
		if (lig>0)
		  procedu=proba_object(tab[col+1][lig-1],procedu, 2);

		proba_object(tab[col+1][lig],procedu, 1);

		if (lig<LIG-2)
		  procedu=proba_object(tab[col+1][lig+1],procedu, 2);
		if (lig<LIG-1)
		  procedu=proba_object(tab[col+1][lig+2],procedu, 3);
	      }

	    if (col<COL-1)
	      {
		if (lig>1)
		  procedu=proba_object(tab[col+2][lig-2],procedu, 4);
		if (lig>0)
		  procedu=proba_object(tab[col+2][lig-1],procedu, 3);
		proba_object(tab[col+2][lig],procedu, 2);
		if (lig<LIG-2)
		  procedu=proba_object(tab[col+2][lig+1],procedu, 3);
		if (lig<LIG-1)
		  procedu=proba_object(tab[col+2][lig+2],procedu, 4);
	      }
	    tab[col][lig]=proba(procedu);
	  }
      }

}
