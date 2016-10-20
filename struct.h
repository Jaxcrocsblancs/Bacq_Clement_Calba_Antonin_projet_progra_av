#ifndef STRUCT_H
#define STRUCT_H

typedef struct NODE NODE;
typedef struct item item;
typedef struct sol sol;
typedef struct image image;
typedef struct object object;
typedef struct point_cout point_cout;
typedef struct Liste_point *liste_point;
typedef struct perso perso;
typedef struct cptSens cptSens;

struct item
{
    int id;
    int nb;
    char nom;
};

struct sol
{
  int id;
  item item;
};

struct image
{
  SDL_Surface* herbe;
  SDL_Surface* plante;
  SDL_Surface* alpha;
};

struct object
{
  int chene;
  int salade;
  int fraisier;
  int ble;
};

struct point_cout
{
	int col;
	int lig;
	int f; // cout total
};

struct Liste_point
{
	point_cout premier;
	liste_point reste;
};

struct cptSens
{
    int x;
    int y;
};

struct perso
{
    SDL_Rect rcDest;
    SDL_Rect rcSens;
    cptSens cptSens;
    SDL_Surface *perso;
    item item;
    cptSens pos;
};

struct NODE
{
	int walkable; // si on a acc�s a la case

	int onopen; // liste ouverte
	int onclosed; // liste ferm�

	int g; // cout de l'op�ration a un temps t
	int h; // cout restant des op�ration a un temps t
	int f; // cout total

	int parentx;
	int parenty;
}; // tableau representant la map
#endif
