/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main(/*int argc, char *argv[]*/)
{
  /*freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);*/

  if (SDL_Init (SDL_INIT_EVERYTHING))
    fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());

  /* create window */
  SDL_Surface *screen = NULL;
  SDL_Rect coord;
  SDL_Event event;
  image image;
  perso perso;
  liste_point L;
  sol sol[COL][LIG];
  int seed, tic, zoom, buttx, butty, cond, done;

  L = l_vide();
  tic = 0;

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
  perso = init_perso();

  coord.x = 0;
  coord.y = 0;
  zoom = 1;
  done = 0;
  cond = 0;
  
  while (done == 0)
    {
      SDL_PollEvent(&event);
      
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
		  if (zoom == 1)
		    {
		      zoom = 2;
		      image = zoom_image(image, (float)zoom);
		      perso = zoom_perso(perso, (float)zoom);
		      perso.rcSens.h = taille *2;
		      perso.rcSens.w = taille *2;
		      perso.rcDest.h = taille *2;
		      perso.rcDest.w = taille *2;
		    }
		  else
		    {
		      if (zoom==2)
			{
			  image = zoom_image(image, (float)zoom);
			  perso = zoom_perso(perso, (float)zoom);
			  zoom = 4;
			  perso.rcSens.h = taille *4;
			  perso.rcSens.w = taille *4;
			  perso.rcDest.h = taille *4;
			  perso.rcDest.w = taille *4;
			}
		      else
			{
			  image = image_init();
			  perso = init_perso();
			  zoom=1;
			  coord.x=0;
			  coord.y=0;
			  perso.rcSens.x = 0;
			  perso.rcSens.y = 0;
			  perso.rcDest.h = 0;
			  perso.rcDest.w = 0;
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
		  if (sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].id)
		    {
		      sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].item.id = sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].id;
		      sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].id = 0;
		      sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].item.nb = 4;
		    }
		  break;
		}
	      case SDL_BUTTON_RIGHT:
		{
		  
		  buttx = event.motion.x / (taille*zoom);
		  butty = event.motion.y / (taille*zoom);
		    cond = 1;
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
		{
		  break;
		}
	      case SDL_BUTTON_LEFT:
		{
		  break;
		}
	      case SDL_BUTTON_RIGHT:
		{
		  break;
		}
	      }
	    break;
	  }
	}
      //deplacement_constr(sol,screen,&perso.rcDest,perso.rcSens,buttx,butty,node,&cond,&L);
      tic+=1;
      perso = deplacement_personnage(sol, screen,perso, &L, buttx, butty, &cond, zoom);
      affichage_map(sol, screen, zoom, image, coord);
      SDL_BlitSurface(perso.perso, &perso.rcSens, screen, &perso.rcDest);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
  return 0;
}
