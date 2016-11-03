#include <stdio.h>
#include <stdlib.h>
typedef enum action action;
enum action
{
    couper = 1, planter = 2, ramasser = 3
};


int main()
{
    action actio;
    actio = couper;
    printf("%c",actio);
    return 0;
}
