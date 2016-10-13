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

#endif
