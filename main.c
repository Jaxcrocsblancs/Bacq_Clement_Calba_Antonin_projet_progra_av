/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main(int argc, char *argv[])
{
  /*freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);*/

  /* initialize SDL */  
  if (SDL_Init (SDL_INIT_EVERYTHING)) 
    fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());

  /* create window */
  SDL_Surface *screen = NULL;
  SDL_Rect coord;
  SDL_Event event;
  image image;
  sol sol[COL][LIG];
  int seed, tic;
  int zoom;
  int done = 0;

  printf("donner la graine: \n");
  //scanf("%d",&seed);
  seed=1;

  screen = SDL_SetVideoMode(COL*taille, LIG*taille, 24, 0);
  if (!screen) 
    fprintf(stderr,"SetVideoMode error: %s\n", SDL_GetError()); 

  srand (seed);
  init_tab(sol);
  generation_procedural(sol);

  image = image_init();
  coord.x = 0;
  coord.y = 0;
  zoom=1;

  while (done == 0)
    {
      if (SDL_PollEvent(&event))
	{
	  switch (event.type)
	    {
	    default:
	      break;
	    case SDL_QUIT:
	      done = 1;
	      break;
	    case SDL_KEYDOWN:
	      {
		switch (event.key.keysym.sym)
		  {
		  default:
		    break;
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
			  zoom=2;
			  image=zoom_image(image, (float)zoom);
			}
		      else
			{
			  if (zoom==2)
			    {
			      image=zoom_image(image, (float)zoom);
			      zoom=4;
			    }
			  else
			    {
			      image=image_init();
			      zoom=1;
			      coord.x=0;
			      coord.y=0;
			    }
			}
		      break;
		    }
		  case SDLK_DOWN:
		    if (-(zoom-1)*LIG*taille < coord.y)
		      coord.y-=taille*zoom;
		    break;
		  case SDLK_UP:
		    if (coord.y<0)
		      coord.y+=taille*zoom;
		    break;
		  case SDLK_LEFT:
		    if (coord.x<0)
		      coord.x+=taille*zoom;
		    break;
		  case SDLK_RIGHT:
		    if  (-(zoom-1)*COL*taille < coord.x)
		      coord.x-=taille*zoom;
		    break;
		  }
	      }
	    case SDL_MOUSEMOTION:
	      {

		break;
	      }

	    case SDL_MOUSEBUTTONDOWN:
	      {
		switch (event.button.button)
		  {
		  default:
		    {
		      break;
		    }
		  case SDL_BUTTON_LEFT:
		    {
		      if (sol[(-coord.y+event.motion.y)/(taille*zoom)][(-coord.x+event.motion.x)/(taille*zoom)].id)
			{
			  sol[(-coord.y+event.motion.y)/(taille*zoom)][(-coord.x+event.motion.x)/(taille*zoom)].item.id = sol[(-coord.y+event.motion.y)/(taille*zoom)][(-coord.x+event.motion.x)/(taille*zoom)].id;
			  sol[(-coord.y+event.motion.y)/(taille*zoom)][(-coord.x+event.motion.x)/(taille*zoom)].id = 0;
			  break;
			}
		    }
		  case SDL_BUTTON_RIGHT:
		    {
		      printf("%d %d\n", (-coord.x+event.motion.x)/(taille*zoom), (-coord.y+event.motion.y)/(taille*zoom));
		      printf("droite bas\n");
		      break;
		    }
		  }
		break;
	      }
	    case SDL_MOUSEBUTTONUP:
	      {
		switch (event.button.button)
		  {
		  default:
		    break;
		  case SDL_BUTTON_LEFT:
		    {
		      printf("%d %d\n", (-coord.x+event.motion.x)/(taille*zoom), (-coord.y+event.motion.y)/(taille*zoom));
		      printf("haut\n");
		      break;
		    }
		  case SDL_BUTTON_RIGHT:
		    {
		      printf("%d %d\n", (-coord.x+event.motion.x)/(taille*zoom), (-coord.y+event.motion.y)/(taille*zoom));
		      printf("haut droite\n");
		      break;
		    }
		  }
		break;
	      }
	    }
	}
      affichage_map(sol,screen, zoom, image, coord);
      SDL_Flip(screen);
    }
  return 0;
}
