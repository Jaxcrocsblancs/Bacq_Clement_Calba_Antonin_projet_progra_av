/*
 * map.c
 *
 *  Created on: 26 sept. 20taille
 *      Author: cleme
 */

#include "include.h"

void remplisTab(int tab[COL][LIG])
{
	int col,lig;
	for(col=0;col<COL;col++)
	{
		for(lig=0;lig<LIG;lig++)
		{
			tab[col][lig] = 0;
		}
	} // end for
	tab[1][0] = 1;
	tab[1][1] = 1;
	tab[1][2] = 1;
	tab[2][1] = 1;
	tab[2][3] = 1;
	tab[4][2] = 1;
	tab[4][3] = 1;

	tab[0][0] =  2;
	tab[5][0] =  3;
}

void afficherTab(int tab[COL][LIG])
{
	int col,lig;
	for(lig=0;lig<LIG;lig++)
	{
		for(col=0;col<COL;col++)
		{
			printf(",%d",tab[col][lig]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

int Walkable(sol tab[COL][LIG], int col, int lig)
{
	if(tab[col][lig].id == 1)
	{
		return 0;
	}
	return 1;
}


void initnodes(sol tab[COL][LIG], NODE node[COL][LIG])
{
	int x,y;
	for(x=0;x<COL;x++)
	{
		for(y=0;y<LIG;y++)
		{
			node[x][y].walkable = Walkable(tab,x,y);
			node[x][y].onopen = false;
			node[x][y].onclosed = false;
			node[x][y].g = 0;
			node[x][y].h = 0;
			node[x][y].f = 0;
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

	node[startx][starty].onclosed = true; // ajoute un noeud de node a la liste ouverte
	pStart = remplisPoint(startx, starty, 0);
	LF = cons(pStart,LF);


	//s'arrete quand quand le quand la position actuelle est egal a l arrivee
	while((currentx != endx) || (currenty != endy))
	{
		cptRetour = 0;
		// recherche le plus petit F des noeuds en liste ouverte
		for(x=-1;x<=1;x++)
		{
			for(y=-1;y<=1;y++)
			{
				if( ((x == 0)&&(y != 0)) || ((y == 0)&&(x != 0)))
				{
					if((currentx + x >= 0) && (currenty + y >= 0) && (currentx + x < COL) && (currenty + y < LIG) )
					{
						if(node[currentx + x][currenty + y].walkable && !node[currentx + x][currenty + y].onclosed)
						{
							// augment le cout de l operation (g)
							node[currentx + x][currenty + y].g = node[currentx][currenty].g + 1;

							//cout restant avec MANHATTAN (h)
							node[currentx + x][currenty + y].h = abs(endx - (currentx + x)) + abs(endy - (currenty + y));

							//cout total (f)
							node[currentx + x][currenty + y].f = node[currentx + x][currenty + y].g + node[currentx + x][currenty + y].h;

							//cree et met le point dans la liste ouverte
							pNode = remplisPoint(currentx + x,currenty + y,node[currentx + x][currenty + y].f);
							LO = cons(pNode,LO);

							//ajoute le parent
							node[currentx + x][currenty + y].parentx = currentx;
							node[currentx + x][currenty + y].parenty = currenty;
						}
						else
						{
							cptRetour += 1;
						}
					} // END if ((currentx + x < 0) || (currenty + y < 0) || (currentx + x >= COL) || (currenty + y >= LIG) )
					else
					{
						cptRetour += 1;
					}
				} //END if ((x == 0) || (y == 0))
			}
		} // END for

		if(est_vide(LO))
		{
			printf("Gros FAIL\n");
			printf("currentx = %d, currenty = %d\n",currentx,currenty);
		}

		if(!est_vide(LO))
		{
		pLF = plusPetitF(prem(LO),reste(LO));
		LF = cons(pLF,LF);
		currentx = pLF.col;
		currenty = pLF.lig;
		LO = supprimerR(pLF,LO);
		node[currentx][currenty].onclosed = true;
		}


	}//END while

	LF = triPath(LF,node);
	return renverser_liste(LF);
} //END function


liste_point Astar(sol tab[COL][LIG], NODE node[COL][LIG],int startx, int starty, int endx, int endy)
{
	initnodes(tab,node);
//	afficherNode(node);
	return findpath(startx,starty,endx,endy,node);
}


