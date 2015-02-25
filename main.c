#include <stdio.h>
#include <stdlib.h>
#include "dame.h"
#include "programme.h"

int main()
{
    struct game *jeu = new_game(7, 7);
    struct game *jeu2 = load_game(jeu->xsize, jeu->ysize, jeu->board, jeu->cur_player);
    afficher(jeu2);
    free_game(jeu);
    free(jeu2);
    return 0;
}
