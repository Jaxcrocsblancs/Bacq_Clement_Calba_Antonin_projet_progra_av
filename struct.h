#ifndef STRUCT_H
#define STRUCT_H

struct item
{
    int id;
    int nb;
    char nom;
};
typedef struct item item;

struct sol
{
  int id;
  item item;
};
typedef struct sol sol;

struct image
{
  SDL_Surface* herbe;
  SDL_Surface* plante;
};
typedef struct image image;

struct object
{
  int chene;
  int salade;
  int fraisier;
  int ble;
};
typedef  struct object object;

struct point_cout
{
	int col;
	int lig;
	int f; // cout total
};
typedef struct point_cout point_cout;

typedef struct Liste_point *liste_point;
struct Liste_point
{
	point_cout premier;
	liste_point reste;
};


struct perso
{
    SDL_Rect rcDest;
    SDL_Rect rcSens;
    SDL_Surface *perso;
};
typedef struct perso perso;

#endif
