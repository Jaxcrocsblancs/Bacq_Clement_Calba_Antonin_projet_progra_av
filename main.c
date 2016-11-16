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
      handle(perso, &image, &action,&done, &p, &zoom, &coord, hauteur, largeur, &gauche_maintenu_x, &gauche_maintenu_y, &gauche_maintenu, &buttx, &butty);

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
      affichage_menu(screen, hauteur, largeur, image, action);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(100);
    }

  return 0;
}
