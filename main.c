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
<<<<<<< HEAD
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

=======
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

>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
  printf("donner la graine: \n");
  //scanf("%d",&seed);
  seed=1;


  screen = SDL_SetVideoMode(COL*taille, LIG*taille, 24, 0);
  if (!screen)
    fprintf(stderr,"SetVideoMode error: %s\n", SDL_GetError());
<<<<<<< HEAD

=======
  
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
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
<<<<<<< HEAD
  action = 1;
  click = 0;
  buttx = 0;
  butty = 0;
=======
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
  
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
<<<<<<< HEAD
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
=======
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
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
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
<<<<<<< HEAD
		    buttx = event.motion.x / (taille*zoom);
		    butty = event.motion.y / (taille*zoom);
			cond = 1;
			click = 1;
=======
		    if (sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].id)
		      {
			sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].item.id = sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].id;
			sol[(-coord.x+event.motion.x)/(taille*zoom)][(-coord.y+event.motion.y)/(taille*zoom)].id = 0;
		      }
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
		    break;
		  }
		case SDL_BUTTON_RIGHT:
		  {
<<<<<<< HEAD
=======
		  
		    buttx = event.motion.x / (taille*zoom);
		    butty = event.motion.y / (taille*zoom);
		    if (sol[buttx][butty].id !=1)
		      cond = 1;
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
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
<<<<<<< HEAD

=======
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
		    break;
		  }
		case SDL_BUTTON_RIGHT:
		  {
		    break;
		  }
		}
<<<<<<< HEAD
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
=======
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
>>>>>>> 883f5c99e107cd40afcb916c82d59194a5a60dc4
  return 0;
}
