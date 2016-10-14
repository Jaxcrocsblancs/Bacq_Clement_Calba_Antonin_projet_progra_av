/*
 * map.h
 *
 *  Created on: 3 oct. 2016
 *      Author: cleme
 */
#include "include.h"

#ifndef MAP_H_
#define MAP_H_


liste_point findpath(int startx, int starty, int endx, int endy,NODE node[COL][LIG]);
liste_point triPath(liste_point L,NODE node[COL][LIG]);
void initnodes(sol tab[COL][LIG],NODE node[COL][LIG]);
int Walkable(sol tab[COL][LIG],int col, int lig);
void remplisTab(int tab[COL][LIG]);
liste_point Astar(sol tab[COL][LIG], int startx, int starty, int endx, int endy);


#endif /* MAP_H_ */
