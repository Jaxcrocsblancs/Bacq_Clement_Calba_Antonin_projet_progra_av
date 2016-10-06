/*************************/
/* main.c                */
/* auteur : Bacp Clement */
/* et Calba Antonin      */
/*************************/
#include "include.h"

int main(int argc, char *argv[])
{
  freopen("CON", "w", stdout);
  freopen("CON", "r", stdin);
  freopen("CON", "w", stderr);
  SDL_Surface* screen;
  SDL_Rect coord;
  image image;
  map_objt sol[COL][LIG];
  int seed, tic;
  int zoom;
  tic=0;
  image=image_init();

  printf("donner la graine: \n");
  scanf("%d",&seed);
  srand (seed);
  generation_procedural(sol);
  affichage_tab(sol);

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* create window */
  screen = SDL_SetVideoMode(COL*16, LIG*16, 0, 0);

  image = image_init();
  coord.x = 0;
  coord.y = 0;
  zoom=1;

  mise_image_struct_tableau(sol,image);
  int done = 0;
  while (done == 0)
    {
      SDL_Event event;
      SDL_WaitEvent(&event);
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
                    if (zoom==1)
                      {
                        printf("z1\n");
                        zoom=2;
                        image=zoom_image(image, (float)zoom);
                        mise_image_struct_tableau(sol,image);
                      }
                    else
                      {
                        if (zoom==2)
                        {
                            printf("z2\n");
                            image=zoom_image(image, (float)zoom);
                            zoom=4;
                            mise_image_struct_tableau(sol,image);
                        }
                        else
                        {
                            printf("z4\n");
                            image=image_init();
                            mise_image_struct_tableau(sol,image);
                            zoom=1;
                            coord.x=0;
                            coord.y=0;
                        }
                      }
                        break;
                    }
                case SDLK_UP:
                  printf("%d %d\n",-(zoom-1)*LIG*16, coord.y);
                  if (-(zoom-1)*LIG*16 < coord.y)
                    coord.y-=16*zoom;
                  break;
                case SDLK_DOWN:
                  if (coord.y<0)
                    coord.y+=16*zoom;
                  break;
                case SDLK_RIGHT:
                  if (coord.x<0)
                    coord.x+=16*zoom;
                  break;
                case SDLK_LEFT:
                  if  (-(zoom-1)*COL*16 < coord.x)
                    coord.x-=16*zoom;
                  break;
                }
              }
          }

      tic+=1;
      affichage_map(sol,screen, zoom, image, coord);
      SDL_Flip(screen);
    }
  return 0;
}
