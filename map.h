/*
 * map.h
 *
 *  Created on: 3 oct. 2016
 *      Author: cleme
 */

#ifndef MAP_H_
#define MAP_H_

#include "liste_point.h"
#include <SDL.h>

#define COL 20
#define LIG 20

struct map_objt
{
	SDL_Surface s;
	int a;
};
typedef struct map_objt map_objt;

struct NODE
{
	int walkable; // si on a accès a la case

	int g; // cout de l'opération a un temps t
	int h; // cout restant des opération a un temps t
	int f; // cout total
	int onclosed;
	int parentx;
	int parenty;
}; // tableau representant la map

typedef struct NODE NODE;

liste_point chemin(map_objt tab[COL][LIG],int startx, int starty, int endx, int endy);

liste_point findpath(int startx, int starty, int endx, int endy,NODE node[COL][LIG]);
liste_point triPath(liste_point L,NODE node[COL][LIG]);
void initnodes(map_objt tab[COL][LIG],NODE node[COL][LIG]);
int Walkable(map_objt tab[COL][LIG],int col, int lig);
void remplisTab(map_objt tab[COL][LIG]);
liste_point Astar(map_objt tab[COL][LIG], NODE node[COL][LIG],int startx, int starty, int endx, int endy);


#endif /* MAP_H_ */
