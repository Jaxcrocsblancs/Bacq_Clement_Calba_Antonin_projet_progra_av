#include "include.h"

void handle(SDL_Event *event, perso perso[NB_Perso], image *image, int *action,int *done, int *p, int *zoom, SDL_Rect *coord, int hauteur, int largeur, int  *gauche_maintenu_x, int *gauche_maintenu_y, int *gauche_maintenu, int *buttx, int *butty)
{
    int i;
    SDL_PollEvent(event);
    switch (event->type)
	{
    default:
        break;
	case SDL_QUIT:
	  *done = 1;
	  break;
	case SDL_KEYDOWN:
	  {
	    switch (event->key.keysym.sym)
	      {
	      default:
            break;
	      case SDLK_ESCAPE:
            *done = 1;
            break;
	      case SDLK_q:
            *done = 1;
            break;
	      case SDLK_F1:
	          if (*action == 0)
                {
                *action = 10;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 1;
                  }
            break;
	      case SDLK_F2:
             if (*action == 0)
                {
                *action = 20;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 2;
                  }
            break;
            break;
	      case SDLK_F3:
             if (*action == 0)
                {
                *action = 30;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 3;
                  }
            break;
	      case SDLK_F4:
             if (*action == 0)
                {
                *action = 40;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 4;
                  }
            break;
	      case SDLK_F5:
            if (*action == 0)
                {
                *action = 50;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 5;
                  }
            break;
	      case SDLK_F6:
             if (*action == 0)
                {
                *action = 60;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 6;
                  }
            break;
	      case SDLK_F7:
             if (*action == 0)
                {
                *action = 70;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 7;
                  }
            break;
	      case SDLK_F8:
             if (*action == 0)
                {
                *action = 80;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 8;
                  }
            break;
	      case SDLK_F9:
             if (*action == 0)
                {
                *action = 90;
                }
             else
                  {
                    if (*action % 10 == 0)
                        *action -= 10;
                    *action = *action/10*10 + 9;
                  }
            break;
	      case SDLK_F10:
            if (*action == 0)
                {
                *action = 100;
                }
             else
                  {
                    *action = 0;
                  }
            SDL_Delay(100);
            break;
	      case SDLK_p:
            if (p)
              *p=0;
            else
              *p=1;
            SDL_Delay(100);
            break;
	      case SDLK_z:
            {
              if (*zoom == 1)
                {
                  *zoom = 2;
                  *image = zoom_image(*image, (float)*zoom);
                  for (i=0; i<NB_Perso; i++)
                  {
                  perso[i] = zoom_perso(perso[i], (float)*zoom);
                  perso[i].rcSens.h = taille *2;
                  perso[i].rcSens.w = taille *2;
                  }
                  coord->x = coord->x*2;
                  coord->y = coord->y*2;
                }
              else
                {
                      *image = image_init();
                      for (i=0; i<NB_Perso; i++)
                      {
                        perso[i].perso = SDL_LoadBMP ("image/test.bmp");
                        SDL_SetColorKey(perso[i].perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso[i].perso->format, 255, 0, 255));
                      }
                      *zoom = 1;
                      for (i=0; i<NB_Perso; i++)
                        {
                      perso[i].rcSens.x = 0;
                      perso[i].rcSens.y = 0;
                      perso[i].rcSens.w = taille;
                      perso[i].rcSens.h = taille;
                        }

                      coord->x = coord->x/2;
                      coord->y = coord->y/2;
                      // test a rajouter pour revenir dans l'ecran quand on dezoom
                }
              SDL_Delay(75);
              break;
            }
        case SDLK_DOWN:
            if (-(*zoom)*(LIG*taille) + hauteur < coord->y)
              {
                coord->y-=taille* (*zoom);
              }
            break;
	      case SDLK_UP:
		if (coord->y<0)
		  {
		    coord->y+=taille*(*zoom);
		  }
		break;
	      case SDLK_LEFT:
		if (coord->x<0)
		  {
		    coord->x+=taille*(*zoom);
		  }
		break;
	      case SDLK_RIGHT:
		if  (-(*zoom)*(COL*taille)+ largeur< coord->x)
		  {
		    coord->x-=taille*(*zoom);
		  }
		break;
	      }
	    break;
	  }
	case SDL_MOUSEBUTTONDOWN:
	  {
	    switch (event->button.button)
	      {
	      default:
            {
              break;
            }
	      case SDL_BUTTON_LEFT:
            {
                if ((event->motion.x > (largeur/2-505/2)) && (event->motion.x < (largeur/2-505/2+505)) && (event->motion.y > (hauteur)))
                  {
                    if((event->motion.y > (hauteur+17)) && (event->motion.y < (hauteur+47)))
                    {
						if (*action == 0)
						{
							if ((event->motion.x > (largeur/2-505/2+17)) && (event->motion.x < (largeur/2-505/2+ 17 + 32)))
							  *action = 10;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 1)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 1+ 32)))
							  *action = 20;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 2)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 2+ 32)))
							  *action = 30;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 3)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 3+ 32)))
							  *action = 40;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 4)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 4+ 32)))
							  *action = 50;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 5)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 5+ 32)))
							  *action = 60;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 6)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 6+ 32)))
							  *action = 70;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 7)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 7+ 32)))
							  *action = 80;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 8)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 8+ 32)))
							  *action = 90;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 9)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 9+ 32)))
							  *action = 100;
							SDL_Delay(50);
					  }
					  else
					  {
						  if (*action % 10 == 0)
								*action -= 10;

							if ((event->motion.x > (largeur/2-505/2+17)) && (event->motion.x < (largeur/2-505/2+ 17 + 32)))
								*action = *action/10*10 + 1;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 1)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 1+ 32)))
								*action = *action/10*10 + 2;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 2)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 2+ 32)))
								*action = *action/10*10 + 3;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 3)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 3+ 32)))
								*action = *action/10*10 + 4;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 4)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 4+ 32)))
								*action = *action/10*10 + 5;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 5)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 5+ 32)))
								*action = *action/10*10 + 6;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 6)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 6+ 32)))
								*action = *action/10*10 + 7;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 7)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 7+ 32)))
								*action = *action/10*10 + 8;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 8)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 8+ 32)))
								*action = *action/10*10 + 9;
							if ((event->motion.x > (largeur/2-505/2+ 17 + 48* 9)) && (event->motion.x < (largeur/2-505/2+ 17 + 48* 9+ 32)))
								*action = 0;

							printf("*action: %d\n", *action);
							SDL_Delay(100);
					  }
                    }
                  }
                else
                    if (*gauche_maintenu == 0)
                        {
                          *gauche_maintenu = 1;
                          *gauche_maintenu_x = event->motion.x / (taille*(*zoom)) - coord->x/ (taille*(*zoom));
                          *gauche_maintenu_y = event->motion.y / (taille*(*zoom)) - coord->y/ (taille*(*zoom));
                          *buttx = *gauche_maintenu_x;
                          *butty = *gauche_maintenu_y;
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
            if (*gauche_maintenu == 1)
                {
                  *buttx = event->motion.x / (taille*(*zoom)) - coord->x/ (taille*(*zoom));
                  *butty = event->motion.y / (taille*(*zoom)) - coord->y/ (taille*(*zoom));
                }
            break;
          }
	case SDL_MOUSEBUTTONUP:
	  {
	    switch (event->button.button)
	      {
              default:
                {
                  break;
                }
              case SDL_BUTTON_LEFT:
                {
                  *gauche_maintenu = 0;
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
	return;
}


void tour(unsigned int *temps_ennemi, perso ennemi[NB_ennemi],SDL_Rect coord, liste_point *plantation, perso perso[NB_Perso], int gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *buttx, int *butty, int action, sol sol[COL][LIG], SDL_Surface *screen, liste_stockpile *stockPile, int zoom, image image, int hauteur, int largeur, unsigned int *temps, int p)
{
   int i, j;
   rectangle(gauche_maintenu, gauche_maintenu_x, gauche_maintenu_y, buttx, butty, action, sol, stockPile);
   affichage_map(sol, screen, zoom, image, coord, hauteur, largeur,*stockPile);

   if (*temps != SDL_GetTicks()/100 && p)
   {
       printf("action %d\n", perso[0].action);
        /*if ( *temps_ennemi <=  SDL_GetTicks()/10000 || *temps_ennemi == 0)
        {
            *temps_ennemi = SDL_GetTicks()/10000 +1 ;
            for (i=0; i<NB_ennemi; i++)
            {
                ennemi[i] = init_ennemi();
            }
        }
       for (i=0; i<NB_ennemi; i++)
        for (j=0; j<NB_Perso; j++)
            if (ennemi[i].pv > 0)
            {
            cherche_ennemi(sol,ennemi[i],perso[j]);
            }*/

        for (i= 0; i<NB_Perso;i++)
        	if (perso[i].faim >0 && perso[i].pv > 0)
        	{
        	  //perso[i] = faim(perso[i]);
              cherche_action (sol, &perso[i]);
              perso[i] = actionPerso(ennemi, sol, perso[i], plantation ,stockPile);
              perso[i] = deplacement_personnage(sol , screen ,perso[i], perso[i].but.x, perso[i].but.y, zoom);
        	}

      /*  for (i=0; i<NB_Perso; i++)
            for (j=0; j<NB_Perso; j++)
            if (perso[i].pv > 0)
            {
            cherche_ennemi(sol,perso[i],ennemi[j]);
            }
        for (i= 0; i<NB_ennemi;i++)
        	if (ennemi[i].pv > 0)
        	{
              ennemi[i] = actionPerso(perso, sol, ennemi[i], plantation ,stockPile);
              ennemi[i] = deplacement_personnage(sol , screen ,ennemi[i], ennemi[i].but.x, ennemi[i].but.y, zoom);
        	}
*/

        *plantation = pousser(sol, *plantation);
        *temps = SDL_GetTicks()/100;
    }
       for (i= 0; i<NB_Perso;i++)
        {
            if (perso[i].pv >0)
            {
              perso[i].rcDest.x = perso[i].pos.x * taille * zoom + coord.x;
              perso[i].rcDest.y = perso[i].pos.y * taille * zoom + coord.y;
              SDL_BlitSurface(perso[i].perso, &perso[i].rcSens, screen, &perso[i].rcDest);
            }
        }

       /* for (i= 0; i<NB_ennemi;i++)
        {
            if (ennemi[i].pv >0)
            {
            ennemi[i].rcDest.x = ennemi[i].pos.x * taille * zoom + coord.x;
            ennemi[i].rcDest.y = ennemi[i].pos.y * taille * zoom + coord.y;
            SDL_BlitSurface(ennemi[i].perso, &ennemi[i].rcSens, screen, &ennemi[i].rcDest);
            }
        }
        for (i= 0; i<NB_ennemi-1;i++)
        {
            if (ennemi[i].pv<0)
            {
                ennemi[i]=ennemi[i+1];
            }
        }*/
       affichage_menu(screen, hauteur, largeur, image, action);
}
