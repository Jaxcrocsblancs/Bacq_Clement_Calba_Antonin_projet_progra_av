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
  perso perso[NB_Perso];
  liste_point L[NB_Perso], plantation, stockPile;
  sol sol[COL][LIG];
  int seed, zoom, buttx, butty, cond[NB_Perso], done, action, gauche_maintenu,gauche_maintenu_x, gauche_maintenu_y, p;
  unsigned int  temps;
	stockPile = l_vide();
  plantation = l_vide();
  temps = 0;

  printf("donner la graine: \n");
  //scanf("%d",&seed);
  seed=1;

  int hauteur, largeur;

  largeur = COL * taille;
  hauteur = LIG * taille;

  if ( maxH < hauteur)
    hauteur = maxH - 4*taille ;

  if ( maxW < largeur)
    largeur = maxW - 4*taille;

  hauteur = hauteur/(4*taille)*(4*taille);
  largeur = largeur/(4*taille)*(4*taille);
  screen = SDL_SetVideoMode(largeur, hauteur +2*taille, 24, 0);
  if (!screen)
    fprintf(stderr,"SetVideoMode error: %s\n", SDL_GetError());

  srand (seed);
  init_tab(sol);
  generation_procedural(sol);

  image = image_init();
  int i;
  for (i=0; i<NB_Perso; i++)
    {
    perso[i] = init_perso();
   cond[i] = 0;
   L[i] = l_vide();
    }
  coord.x = 0;
  coord.y = 0;
  zoom = 1;
  done = 0;

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
          case SDLK_F10:
            action = 0;
            break;
	      case SDLK_p:
            if (p)
              p=0;
            else
              p=1;
            SDL_Delay(100);
            break;
	      case SDLK_z:
            {
              if (zoom == 1)
                {
                  zoom = 2;
                  image = zoom_image(image, (float)zoom);
                  for (i=0; i<NB_Perso; i++)
                  {
                  perso[i] = zoom_perso(perso[i], (float)zoom);
                  perso[i].rcSens.h = taille *2;
                  perso[i].rcSens.w = taille *2;
                  }

                }
              else
                {
                  if (zoom==2)
                    {
                      image = zoom_image(image, (float)zoom);
                      for (i=0; i<NB_Perso; i++)
                        perso[i] = zoom_perso(perso[i], (float)zoom);
                      zoom = 4;
                      for (i=0; i<NB_Perso; i++)
                        {
                      perso[i].rcSens.h = taille *4;
                      perso[i].rcSens.w = taille *4;
                        }
                    }
                  else
                    {
                      image = image_init();
                      for (i=0; i<NB_Perso; i++)
                      {
                        perso[i].perso = SDL_LoadBMP ("image/test.bmp");
                        SDL_SetColorKey(perso[i].perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso[i].perso->format, 255, 0, 255));
                      }
                      zoom=1;
                      coord.x=0;
                      coord.y=0;
                      for (i=0; i<NB_Perso; i++)
                        {
                      perso[i].rcSens.x = 0;
                      perso[i].rcSens.y = 0;
                      perso[i].rcSens.w = taille;
                      perso[i].rcSens.h = taille;
                        }
                    }
                }
              SDL_Delay(25);
              break;
            }
        case SDLK_DOWN:
            if (-(zoom)*(LIG*taille) + hauteur < coord.y)
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
		if  (-(zoom)*(COL*taille)+ largeur< coord.x)
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
              if (event.motion.y < hauteur)
                {
                  if (gauche_maintenu == 0)
                    {
                      gauche_maintenu = 1;
                      gauche_maintenu_x = event.motion.x / (taille*zoom) - coord.x/ (taille*zoom);
                      gauche_maintenu_y = event.motion.y / (taille*zoom) - coord.y/ (taille*zoom);
                    }
                }
              else
              {
                // action= event.motion.x / (taille*2);
                if ((event.motion.x > (largeur/2-768/2)) && (event.motion.x < (largeur/2-768/2+768)) && (event.motion.y > (hauteur+13)) && (event.motion.y < (hauteur+50)))
                  {
                      printf("x: %d, y: %d\n",event.motion.x,event.motion.y);
                    if ((event.motion.x > (largeur/2-768/2+21)) && (event.motion.x < (largeur/2-768/2+75)))
                      action = 1;
                    if ((event.motion.x > (largeur/2-768/2+94)) && (event.motion.x < (largeur/2-768/2+149)))
                      action = 2;
                    if ((event.motion.x > (largeur/2-768/2+169)) && (event.motion.x < (largeur/2-768/2+224)))
                      action = 3;
                    if ((event.motion.x > (largeur/2-768/2+224)) && (event.motion.x < (largeur/2-768/2+299)))
                      action = 4;
                    if ((event.motion.x > (largeur/2-768/2+319)) && (event.motion.x < (largeur/2-768/2+373)))
                      action = 5;
                    if ((event.motion.x > (largeur/2-768/2+394)) && (event.motion.x < (largeur/2-768/2+448)))
                      action = 6;
                    if ((event.motion.x > (largeur/2-768/2+468)) && (event.motion.x < (largeur/2-768/2+528)))
                      action = 7;
                    if ((event.motion.x > (largeur/2-768/2+543)) && (event.motion.x < (largeur/2-768/2+598)))
                      action = 8;
                    if ((event.motion.x > (largeur/2-768/2+618)) && (event.motion.x < (largeur/2-768/2+673)))
                      action = 9;
                    if ((event.motion.x > (largeur/2-768/2+693)) && (event.motion.x < (largeur/2-768/2+748)))
                      action = 0;
                    printf("action: %d\n", action);
                  }

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
            if (event.motion.y < hauteur)
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
      rectangle(gauche_maintenu, &gauche_maintenu_x, &gauche_maintenu_y, &buttx, &butty, action, sol);
      affichage_map(sol, screen, zoom, image, coord, hauteur, largeur);

      if (temps != SDL_GetTicks()/100 && p)
        {
        cherche_action (sol, perso, cond);
        for (i= 0; i<NB_Perso;i++)
         if (perso[i].faim >0)
         {
          perso[i] = faim(perso[i]);
          perso[i] = deplacement_personnage(sol , screen ,perso[i],  &L[i], perso[i].but.x ,perso[i].but.y, &cond[i],  zoom);
          perso[i] = actionPerso(sol,perso[i], &plantation,&stockPile, &cond);
         }
          plantation = pousser(sol, plantation);
          temps = SDL_GetTicks()/100;

        }

       for (i= 0; i<NB_Perso;i++)
        {
          perso[i].rcDest.x = perso[i].pos.x * taille * zoom + coord.x;
          perso[i].rcDest.y = perso[i].pos.y * taille * zoom + coord.y;
          if (sol[perso[i].pos.x][perso[i].pos.y].id != 21)
            SDL_BlitSurface(perso[i].perso, &perso[i].rcSens, screen, &perso[i].rcDest);
        }
      printf("temps: %d\n,",SDL_GetTicks());
      affichage_menu(screen, hauteur, largeur, image);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
//      SDL_Delay(100);
    }

  return 0;
}
