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
  int maxW, maxH, seed, zoom, buttx, butty, done, action, gauche_maintenu,gauche_maintenu_x, gauche_maintenu_y, p, hauteur, largeur, i;
  SDL_Surface *screen = NULL;
  SDL_Rect coord;
  SDL_Event event;
  image image;
  perso perso[NB_Perso], ennemi[NB_ennemi];
  liste_point plantation;
  liste_stockpile stockPile;
  sol sol[COL][LIG];
  unsigned int  temps, temps_ennemi;
  stockPile = l_videS();
  plantation = l_vide();
  temps = 0;
  temps_ennemi=0;
  videoInfo=SDL_GetVideoInfo();
  maxW=videoInfo->current_w;
  maxH=videoInfo->current_h;

  printf("donner la graine: \n");
  //scanf("%d",&seed);
  seed=1;
    srand(seed);
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

  init_var(sol, &image, perso, &coord, &zoom, &done, &action, &gauche_maintenu, &gauche_maintenu_x, &gauche_maintenu_y, &p, &temps, &plantation, &stockPile, &buttx, &butty);

  while (done == 0)
    {
      handle(&event, perso, &image, &action,&done, &p, &zoom, &coord, hauteur, largeur, &gauche_maintenu_x, &gauche_maintenu_y, &gauche_maintenu, &buttx, &butty);
      tour(&temps_ennemi, ennemi, coord, &plantation, perso, gauche_maintenu, &gauche_maintenu_x, &gauche_maintenu_y, &buttx, &butty,  action, sol ,screen, &stockPile, zoom, image, hauteur, largeur, &temps, p);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    SDL_FreeSurface(image.alpha);
    SDL_FreeSurface(image.ascii);
    SDL_FreeSurface(image.herbe);
    SDL_FreeSurface(image.mine);
    SDL_FreeSurface(image.plante);
    for (i=0; i<NB_Perso; i++)
        SDL_FreeSurface(perso[i].perso);
    for (i=0; i<NB_ennemi; i++)
        SDL_FreeSurface(ennemi[i].perso);
    SDL_Quit();
  return 0;
}
