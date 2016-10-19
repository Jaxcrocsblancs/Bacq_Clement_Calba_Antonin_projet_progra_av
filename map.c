/*
 * map.c
 *
 *  Created on: 26 sept. 2016
 *      Author: cleme
 */

#include "include.h"

int Walkable(sol tab[COL][LIG], int col, int lig)
{
	if(tab[col][lig].id < 100)
	{
		return 1;
	}
	return 0;
}

void initnodes(sol tab[COL][LIG], NODE node[COL][LIG])
{
	int x,y;
	for(x=0;x<COL;x++)
	{
		for(y=0;y<LIG;y++)
		{
			node[x][y].walkable = Walkable(tab,x,y);
			node[x][y].g = 0;
			node[x][y].h = 0;
			node[x][y].f = 0;
			node[x][y].onclosed = 0;
			node[x][y].parentx = NULL;
			node[x][y].parenty = NULL;
		}
	}
}

void afficherNode(NODE node[COL][LIG])
{
	int col,lig;
	for(lig=0;lig<LIG;lig++)
	{
		for(col=0;col<COL;col++)
		{
			printf(",%d",node[col][lig].walkable);
		}
		printf("\n");
	}
	printf("\n");
}

liste_point triPath(liste_point L, NODE node[COL][LIG])
{
	if(est_vide(reste(L)))
	{
		return l_vide();
	}
	if(node[prem(L).col][prem(L).lig].parentx == prem(reste(L)).col && node[prem(L).col][prem(L).lig].parenty == prem(reste(L)).lig)
	{

		return cons(prem(L),triPath(reste(L),node));
	}
	L = supprimerR(prem(reste(L)),L);
	return triPath(L,node);
}


liste_point findpath(int startx, int starty, int endx, int endy,NODE node[COL][LIG])
{
	int x,y; // for running through the nodes

	int cptRetour;


	point_cout pStart, pNode, pLF;
	liste_point LO, LF;
	LO = l_vide();
	LF = l_vide();


	int currentx, currenty; // pour les deplacement a traver les noeuds
	currentx = startx;
	currenty = starty;

	node[startx][starty].walkable = 0; // ajoute un noeud de node a la liste ouverte
	pStart = remplisPoint(startx, starty, 0);
	LF = cons(pStart,LF);


	//s'arrete quand quand le quand la position actuelle est egal a l arrivee
	while((currentx != endx) || (currenty != endy))
	  {
	    cptRetour = 0;
	    // recherche le plus petit F des noeuds en liste ouverte
	    for(x=-1;x<=1;x++)
	      for(y=-1;y<=1;y++)
		if( ((x == 0)&&(y != 0)) || ((y == 0)&&(x != 0)))
		  if((currentx + x >= 0) && (currenty + y >= 0) && (currentx + x < COL) && (currenty + y < LIG) )
		    if(node[currentx + x][currenty + y].walkable && !node[currentx + x][currenty + y].onclosed)
		      {
			// augment le cout de l operation (g)
			node[currentx + x][currenty + y].g = node[currentx][currenty].g + 1;

			//cout restant avec MANHATTAN (h)
			node[currentx + x][currenty + y].h = abs(endx - (currentx + x)) + abs(endy - (currenty + y));

			//cout total (f)
			node[currentx + x][currenty + y].f = node[currentx + x][currenty + y].g + node[currentx + x][currenty + y].h;

			//cree et met le point dans la liste ouverte
			pNode = remplisPoint(currentx + x,currenty + y, node[currentx + x][currenty + y].f);
			LO = cons(pNode,LO);

			//ajoute le parent
			node[currentx + x][currenty + y].parentx = currentx;
			node[currentx + x][currenty + y].parenty = currenty;
		      }
	    if(est_vide(LO))
	      {
		return l_vide();/// ATTENTION PEUT ETRE UN PROBLEME
	      }
	    if(!est_vide(LO))
	      {
		pLF = plusPetitF(prem(LO),reste(LO));
		LF = cons(pLF,LF);
		currentx = pLF.col;
		currenty = pLF.lig;
		LO = supprimerR(pLF,LO);
		node[currentx][currenty].onclosed = 1;
		node[currentx][currenty].walkable = 0;
	      }


	  }//END while
	LF = triPath(LF,node);
	return renverser_liste(LF);
} //END function


liste_point Astar(sol tab[COL][LIG] ,int startx, int starty, int endx, int endy)
{
  NODE node[COL][LIG];
  initnodes(tab,node);
  return findpath(startx,starty,endx,endy,node);
}
