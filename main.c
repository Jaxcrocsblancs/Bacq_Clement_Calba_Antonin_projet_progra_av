/*************************/
/* main.c                */
/* auteur : Bacp Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main()
{
  SDL_Surface* screen;
  int tab[COL][LIG];
  int seed;
  printf("donner la graine: \n");
  scanf("%d",&seed);
  srand (seed);
  generation_procedural(tab);
  affichage_tab(tab);
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* create window */
  screen = SDL_SetVideoMode(COL*32, LIG*32, 0, 0);
 
  int done = 0;
  while (done == 0)
    {
      SDL_Event event;
      SDL_WaitEvent(&event);
      switch (event.type)
	{
	case SDL_QUIT:
	  done = 1;
	  break;
	case SDL_KEYDOWN:
	  {
	    switch (event.key.keysym.sym)
	      {
	      case SDLK_ESCAPE:
		done = 1;
		break;
	      case SDLK_q:
		done = 1;
		break;
	      }
	  }
	}
      SDL_Flip(screen);
    }
  return 0;
}
