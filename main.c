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
  int seed, tic, zoom, buttx, butty, cond, done, action, click;

  L = l_vide();
  tic = 0;

  SDL_Surface *menu;
  SDL_Rect test, testD;
  menu = SDL_LoadBMP ("image/menu.bmp");
  SDL_SetColorKey(menu, SDL_SRCCOLORKEY, SDL_MapRGB(menu->format, 255, 0, 255));
  test.x = 0;
  test.y = 0;
  test.h = 32;
  test.w = 96;

  testD.x = ((COL / 2) - 1) *taille;
  testD.y = (LIG - 1)*taille;
  testD.h = 32;
  testD.w = 96;

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
  action = 1;
  click = 0;
  buttx = 0;
  butty = 0;
  
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
		 case SDLK_F1:
			 action = 1;
			 break;
		 case SDLK_F2:
			 action = 2;
			 break;
		 case SDLK_F3:
			 action = 3;
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
		    buttx = event.motion.x / (taille*zoom);
		    butty = event.motion.y / (taille*zoom);
			cond = 1;
			click = 1;
		    break;
		  }
		case SDL_BUTTON_RIGHT:
		  {
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
	  tic+=1;
	  affichage_map(sol, screen, zoom, image, coord);
	  perso = actionMenu(action,sol,screen,perso,&L,buttx,butty,&cond,zoom,&click);
	  SDL_BlitSurface(perso.perso, &perso.rcSens, screen, &perso.rcDest);
	  SDL_BlitSurface(menu, &test, screen, &testD);
	  SDL_UpdateRect(screen, 0, 0, 0, 0);
	  SDL_Delay(100);
	}
  return 0;
}
