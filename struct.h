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
  //sol
  int id;
  item item;
};
typedef struct sol sol;

struct image
{
  SDL_Surface* chene;
  SDL_Surface* salade;
  SDL_Surface* fraisier;
  SDL_Surface* ble;
  SDL_Surface* herbe;
  SDL_Surface* bois_1;
  SDL_Surface* bois_2;
  SDL_Surface* bois;
};
typedef struct image image;

struct object
{
  int chene;
  int pommier;
  int fraisier;
  int ble;
};
typedef  struct object object;


struct perso
{
	SDL_Rect rcSens;
	SDL_Rect rcDest;
	SDL_Surface *perso;

#endif
