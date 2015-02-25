#include "programme.h"

void afficher(struct game *game)
{
    int i = 0, j = 0;

    for(i = 0 ; i < game->xsize ; i++)
    {
        for(j = 0 ; j < game->ysize ; j++)
        {
            printf("%d", game->board[i][j]);
        }
        printf("\n");
    }
}
