#include "include.h"

void affichage_tab(int tab[COL][LIG])
{
  int col,lig;
  for (col=0;col<COL;col++)
    {
      for (lig=0;lig<LIG;lig++)
	printf("%d ",tab[col][lig]);
      printf("\n");
    }
}
