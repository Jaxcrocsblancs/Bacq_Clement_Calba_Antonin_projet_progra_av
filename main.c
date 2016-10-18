/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main(int argc, char *argv[])
{
  freopen("CON", "w", stdout);
  freopen("CON", "r", stdin);
  freopen("CON", "w", stderr);

  if (SDL_Init (SDL_INIT_EVERYTHING))
	  fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());

    const SDL_VideoInfo *videoInfo;
    int maxW, maxH;
    videoInfo=SDL_GetVideoInfo();
    maxW=videoInfo->current_w;
    maxH=videoInfo->current_h;

    printf("w %d h %d\n", maxW, maxH);
  /* create window */
  SDL_Surface *screen = NULL;
    SDL_Rect coord;
  SDL_Event event;
   image image;
  perso perso;
  liste_point L;
  sol sol[COL][LIG];
  int seed, tic, zoom, buttx, butty, cond, done, click, action;
  L = l_vide();
  tic = 0;

  printf("donner la graine: \n");
 // scanf("%d",&seed);
  seed=1;

  int hauteur, largeur;
    largeur = LIG * taille;
    hauteur = COL * taille;

  if ( maxW < hauteur)
    hauteur = maxW ;

  if ( maxH < largeur)
    largeur = maxH ;

    hauteur = hauteur/(4*taille)*(4*taille);
    largeur = largeur/(4*taille)*(4*taille);
  screen = SDL_SetVideoMode(hauteur, largeur, 24, 0);
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
  L = l_vide();

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
		 case SDLK_1:
			 action = 1;
			 break;
		 case SDLK_2:
			 action = 2;
			 break;
		 case SDLK_3:
			 action = 3;
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
			   }
		       }
		     break;
		     }
	       case SDLK_DOWN:
             if (-(zoom)*(LIG*taille) + largeur < coord.y)
             {
                coord.y-=taille*zoom;
             }
             break;
	       case SDLK_UP:
             if (coord.y<0)
             {
                coord.y+=taille*zoom;
             }
             break;
	       case SDLK_LEFT:
             if (coord.x<0)
               {
                coord.x+=taille*zoom;
                }
             break;
	       case SDLK_RIGHT:
           if  (-(zoom)*(COL*taille)+ hauteur < coord.x)
               {
                coord.x-=taille*zoom;
               }
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
            buttx = event.motion.x / (taille*zoom) - coord.x/ (taille*zoom);
		    butty = event.motion.y / (taille*zoom) - coord.y/ (taille*zoom);
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
	  affichage_map(sol, screen, zoom, image, coord, hauteur, largeur);
	  perso = actionMenu(action,sol,screen,perso,&L,buttx,butty,&cond,zoom,&click);
	  perso.rcDest.x = perso.pos.x * taille * zoom + coord.x;
	  perso.rcDest.y = perso.pos.y * taille * zoom + coord.y;
      perso = cherche_action (sol, perso, &cond, action);
      SDL_BlitSurface(perso.perso, &perso.rcSens, screen, &perso.rcDest);
	  SDL_UpdateRect(screen, 0, 0, 0, 0);
	  SDL_Delay(50);
	}

  return 0;
}
