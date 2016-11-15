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
  liste_point L[NB_Perso], plantation;
  liste_stockpile stockPile;
  sol sol[COL][LIG];
  int seed, zoom, buttx, butty, cond[NB_Perso], done, action, gauche_maintenu,gauche_maintenu_x, gauche_maintenu_y, p;
  unsigned int  temps;
  stockPile = l_videS();
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

  action = 0;

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
	    	  action = 10;
	    	  break;
          case SDLK_F11:
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
                      buttx = gauche_maintenu_x;
                      butty = gauche_maintenu_y;
                    }
                }
              else
              {
                if ((event.motion.x > (largeur/2-505/2)) && (event.motion.x < (largeur/2-505/2+505)) && (event.motion.y > (hauteur+17)) && (event.motion.y < (hauteur+47)))
                  {
                    if (action == 0)
                    {
                        if ((event.motion.x > (largeur/2-505/2+17)) && (event.motion.x < (largeur/2-505/2+ 17 + 32)))
                          action = 10;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 1)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 1+ 32)))
                          action = 20;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 2)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 2+ 32)))
                          action = 30;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 3)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 3+ 32)))
                          action = 40;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 4)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 4+ 32)))
                          action = 50;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 5)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 5+ 32)))
                          action = 60;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 6)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 6+ 32)))
                          action = 70;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 7)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 7+ 32)))
                          action = 80;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 8)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 8+ 32)))
                          action = 90;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 9)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 9+ 32)))
                          action = 100;
                        printf("action: %d\n", action);
                        SDL_Delay(50);
                  }
                  else
                  {
                      if (action % 10 == 0)
                            action -= 10;

                        if ((event.motion.x > (largeur/2-505/2+17)) && (event.motion.x < (largeur/2-505/2+ 17 + 32)))
                            action = action/10*10 + 1;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 1)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 1+ 32)))
                            action = action/10*10 + 2;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 2)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 2+ 32)))
                            action = action/10*10 + 3;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 3)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 3+ 32)))
                            action = action/10*10 + 4;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 4)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 4+ 32)))
                            action = action/10*10 + 5;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 5)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 5+ 32)))
                            action = action/10*10 + 6;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 6)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 6+ 32)))
                            action = action/10*10 + 7;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 7)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 7+ 32)))
                            action = action/10*10 + 8;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 8)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 8+ 32)))
                            action = action/10*10 + 9;
                        if ((event.motion.x > (largeur/2-505/2+ 17 + 48* 9)) && (event.motion.x < (largeur/2-505/2+ 17 + 48* 9+ 32)))
                            action = 0;

                        printf("action: %d\n", action);
                        SDL_Delay(100);
                  }
                }
              }
              break;
            }
	      case SDL_BUTTON_RIGHT:
            {
              break;
            }
	      }
	    break;
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
      rectangle(gauche_maintenu, &gauche_maintenu_x, &gauche_maintenu_y, &buttx, &butty, action, sol, &stockPile);
      affichage_map(sol, screen, zoom, image, coord, hauteur, largeur);

      if (temps != SDL_GetTicks()/100 && p)
        {
        cherche_action (sol, perso, cond);
        for (i= 0; i<NB_Perso;i++)
         if (perso[i].faim >0)
         {
          //perso[i] = faim(perso[i]);
          perso[i] = deplacement_personnage(sol , screen ,perso[i],  &L[i], perso[i].but.x ,perso[i].but.y, &cond[i],  zoom);
          //printf("but.x: %d, pos.x: %d, but.y: %d, pos.y: %d, perso.action %d\n",perso[i].but.x, perso[i].pos.x, perso[i].but.y, perso[i].pos.y, perso[i].action);
          perso[i] = actionPerso(sol,perso[i], &plantation,&stockPile, &cond[i]);
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
      printf("temps: %d\n",SDL_GetTicks());
      affichage_menu(screen, hauteur, largeur, image, action);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(100);
    }

  return 0;
}
