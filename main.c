/*************************/
/* main.c                */
/* auteur : Bacp Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main()
{
  SDL_Surface* screen;
  int sol[COL][LIG];
  int block[COL][LIG]={0};
  int seed;
  float zoom=1.0;
  printf("donner la graine: \n");
  scanf("%d",&seed);
  srand (seed);
  generation_procedural(sol);
  
  affichage_tab(sol);
  affichage_tab(block);
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
	case SDL_BUTTON_WHEELUP:
	  zoom=1.0;
	  break;
	case SDL_BUTTON_WHEELDOWN:
	  zoom=2.0;
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
      affichage_screen(sol, screen);
      SDL_Flip(screen);
    }
  return 0;
}
