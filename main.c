/*************************/
/* main.c                */
/* auteur : Bacq Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main(/*int argc, char *argv[]*/)
{
  /* freopen("CON", "w", stdout);
     freopen("CON", "r", stdin);
     freopen("CON", "w", stderr);*/

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
  liste_point L, plantation;
  sol sol[COL][LIG];
  int seed, zoom, buttx, butty, cond, done, action, gauche_maintenu,gauche_maintenu_x, gauche_maintenu_y, p;
  unsigned int  temps;
  L = l_vide();
  plantation = l_vide();
  temps = 0;

  printf("donner la graine: \n");
  // scanf("%d",&seed);
  seed=1;

  int hauteur, largeur;

  largeur = LIG * taille;
  hauteur = COL * taille;

  if ( maxW < hauteur)
    hauteur = maxW - 4*taille ;

  if ( maxH < largeur)
    largeur = maxH - 4*taille;

  hauteur = hauteur/(4*taille)*(4*taille);
  largeur = largeur/(4*taille)*(4*taille);
  screen = SDL_SetVideoMode(hauteur, largeur+2*taille, 24, 0);
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

  gauche_maintenu = 0;
  gauche_maintenu_x = 0;
  gauche_maintenu_y = 0;
  p=1;
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
	      case SDLK_F1:
		action = 1;
		break;
	      case SDLK_F2:
		action = 2;
		break;
	      case SDLK_F3:
		action = 3;
		break;
	      case SDLK_F4:
		action = 4;
		break;
	      case SDLK_F5:
		action = 5;
		break;
	      case SDLK_F6:
		action = 6;
		break;
	      case SDLK_F7:
		action = 7;
		break;
	      case SDLK_F8:
		action = 8;
		break;
	      case SDLK_F9:
		action = 9;
		break;
	      case SDLK_p:
		if (p)
		  p=0;
		else
		  p=1;
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
			  perso.perso = SDL_LoadBMP ("image/test.bmp");
			  SDL_SetColorKey(perso.perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso.perso->format, 255, 0, 255));;
			  zoom=1;
			  coord.x=0;
			  coord.y=0;
			  perso.rcSens.x = 0;
			  perso.rcSens.y = 0;
			  perso.rcSens.w = taille;
			  perso.rcSens.h = taille;
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
		  if (event.motion.x < largeur)
		      if (gauche_maintenu == 0)
			{
			  gauche_maintenu = 1;
			  gauche_maintenu_x = event.motion.x / (taille*zoom) - coord.x/ (taille*zoom);
			  gauche_maintenu_y = event.motion.y / (taille*zoom) - coord.y/ (taille*zoom);
			}
		  break;
		}
	      case SDL_BUTTON_RIGHT:
		{
		  break;
		}
	      }
	  }
	case SDL_MOUSEMOTION:
          { 
	    if (event.motion.x < largeur)
	      if (gauche_maintenu == 1)
		{
		  buttx = event.motion.x / (taille*zoom) - coord.x/ (taille*zoom);
		  butty = event.motion.y / (taille*zoom) - coord.y/ (taille*zoom);
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
                  gauche_maintenu = 0;
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
      perso = rectangle(gauche_maintenu, &gauche_maintenu_x, &gauche_maintenu_y, &buttx, &butty, perso, action, sol);
      affichage_map(sol, screen, zoom, image, coord, hauteur, largeur);

      if (temps != SDL_GetTicks()/100 && p)
        {
          perso = cherche_action (sol, perso, &cond);
          perso = deplacement_personnage(sol , screen ,perso,  &L, perso.but.x ,perso.but.y, &cond,  zoom);
          perso = actionPerso(sol,perso, &plantation);
          plantation = pousser(sol, plantation);
          temps = SDL_GetTicks()/100;
        }
      perso.rcDest.x = perso.pos.x * taille * zoom + coord.x;
      perso.rcDest.y = perso.pos.y * taille * zoom + coord.y;
      if (sol[perso.pos.x][perso.pos.y].id != 21)
        SDL_BlitSurface(perso.perso, &perso.rcSens, screen, &perso.rcDest);
      affichage_menu(screen, hauteur, largeur, image);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
//      SDL_Delay(100);

    }

  return 0;
}
