/*************************/
/* main.c                */
/* auteur : Bacp Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main(int argc, char *argv[])
{
  SDL_Surface* screen;
  SDL_Rect coord;
  image image;
  map_objt sol[COL][LIG];
  int seed, tic;
  int zoom=1;
  tic=1;

  printf("donner la graine: \n");
  scanf("%d",&seed);
  srand (seed);
  generation_procedural(sol);

  affichage_tab(sol);
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* create window */
  screen = SDL_SetVideoMode(COL*32, LIG*32, 0, 0);

  image = image_init();
  coord.x = 0;
  coord.y = 0;


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
	      case SDLK_z:
		{
		if (zoom==1)
		  {
		    printf("z1\n");
		    zoom=2;
		    image=zoom_image(image, zoom);
		  }
		else
		  {
		    printf("z2\n");
		    image=image_init();
		    zoom=1;
		    coord.x=0;
		    coord.y=0;
		  }
		break;
		case SDLK_UP:
		  printf("%d %d\n",-(zoom-1)*LIG*32, coord.y);
		  if (-(zoom-1)*LIG*32 < coord.y) 
		    coord.y-=32*zoom;
		  break;
		case SDLK_DOWN:
		  if (coord.y<0)
		    coord.y+=32*zoom;
		  break;
		case SDLK_RIGHT:
		  if (coord.x<0)
		    coord.x+=32*zoom;
		  break;
		case SDLK_LEFT:
		  if  (-(zoom-1)*COL*32 < coord.x) 
		    coord.x-=32*zoom;
		  break;
		}
	      }
	  }
	}
      tic+=1;
      SDL_Flip(screen);
    }
  return 0;
}
