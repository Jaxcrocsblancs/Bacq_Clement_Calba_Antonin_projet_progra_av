#include "include.h"

void init_tab(sol tab[COL][LIG])
{
    int col,lig;
    for (col=0;col<COL;col++)
        for (lig=0;lig<LIG;lig++)
            {
                tab[col][lig].id=0;
                tab[col][lig].item.id=0;
                tab[col][lig].item.nb=0;
                tab[col][lig].item.nom="";
                tab[col][lig].ordre=0;
            }
}

void init_var(sol sol[COL][LIG], image *image, perso perso[NB_Perso], SDL_Rect *coord, int *zoom, int *done, int *action, int *gauche_maintenu, int *gauche_maintenu_x, int *gauche_maintenu_y, int *p, unsigned int *temps, liste_point *plantation, liste_stockpile *stockPile, int *buttx, int *butty)
{
    int i;
  init_tab(sol);

  generation_procedural(sol);
  *image = image_init();

  for (i=0; i<NB_Perso; i++)
    {
    perso[i] = init_perso();
    }
  coord->x = 0;
  coord->y = 0;
  *zoom = 1;
  *done = 0;

  *action = 0;

  *gauche_maintenu = 0;
  *gauche_maintenu_x = 0;
  *gauche_maintenu_y = 0;
  *buttx = 0;
  *butty = 0;

  *p=1;

  *stockPile = l_videS();
  *plantation = l_vide();
  *temps = 0;

}

image image_init()
{
  image image;
  image.herbe = SDL_LoadBMP ("image/herbe.bmp");
  image.plante = SDL_LoadBMP ("image/plante.bmp");
  image.alpha = SDL_LoadBMP ("image/attente.bmp");
  image.mine = SDL_LoadBMP ("image/porte_mine.bmp");
  image.menu = SDL_LoadBMP ("image/menu.bmp");
  image.mur = SDL_LoadBMP("image/test.bmp");
  image.ascii = SDL_LoadBMP("image/ascii.bmp");
  SDL_SetColorKey(image.plante, SDL_SRCCOLORKEY, SDL_MapRGB(image.plante->format, 255, 0, 255));
  SDL_SetColorKey(image.alpha, SDL_SRCCOLORKEY, SDL_MapRGB(image.alpha->format, 255, 0, 255));
  SDL_SetColorKey(image.mine, SDL_SRCCOLORKEY, SDL_MapRGB(image.mine->format, 255, 0, 255));
  SDL_SetColorKey(image.menu, SDL_SRCCOLORKEY, SDL_MapRGB(image.menu->format, 255, 0, 255));
  SDL_SetColorKey(image.ascii, SDL_SRCCOLORKEY, SDL_MapRGB(image.ascii->format, 255, 0, 255));
  SDL_SetAlpha(image.alpha,SDL_SRCALPHA, 128 );
  return image;
}

perso init_perso()
{
  perso p;
  SDL_Surface *image;
  SDL_Rect rcDest;
  SDL_Rect rcSens;

  rcDest.x = 0;
  rcDest.y = 0;
  rcDest.h = taille;
  rcDest.w = taille;

  rcSens.x = 0;
  rcSens.y = 0;
  rcSens.h = taille;
  rcSens.w = taille;

  image = SDL_LoadBMP ("image/test.bmp");
  SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255));
  p.rcDest = rcDest;
  p.rcSens = rcSens;
  p.perso = image;
  p.action = 0;

  p.item.id = 0;
  p.item.nb = 0;

  p.cptSens.x = 0;
  p.cptSens.y = 0;

  p.pos.x = 0;
  p.pos.y = 0;

  p.but.x = 0;
  p.but.y = 0;
  p.cond = 0;
  p.L = l_vide();
  p.faim = 200;

  int i;
  for (i=0;i<100;i++)
    p.travail[i]=i+1;
  return p;
}
