#include "dame.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern struct game *new_game(int xsize, int ysize)
{
    int i = 0, j = 0;
    int height = 0;
    struct game* jeu = NULL;

    if(xsize < 4 || ysize < 4)
    {
        fprintf(stderr, "ERREUR : le plateau doit au moins etre de 4 sur 4");
        return NULL;
    }

    jeu = malloc(sizeof(struct game));
    jeu->board = malloc(xsize*sizeof(int*));

    for(i = 0 ; i < xsize ; i++)
    {
        jeu->board[i] = malloc(ysize*sizeof(int));
    }

    height = (xsize-2)/2;

    for(i = 0 ; i < xsize ; i++)
    {
        for(j = 0 ; j < ysize ; j++)
        {
            if(i < height && (i+j)%2 == 1)
            {
                jeu->board[i][j] = 1;
            }
            else if(i > xsize-height-1 && (i+j)%2 == 1)
            {
                jeu->board[i][j] = 5;
            }
            else
            {
                jeu->board[i][j] = 0;
            }
        }
    }

    jeu->xsize = xsize;
    jeu->ysize = ysize;
    jeu->moves = NULL;
    jeu->cur_player = PLAYER_WHITE;

    return jeu;
}

extern struct game *load_game(int xsize, int ysize, const int **board, int cur_player)
{
    struct game* jeu = malloc(sizeof(struct game));
    jeu->xsize = xsize;
    jeu->ysize = ysize;
    jeu->moves = NULL;
    jeu->board = board;
    jeu->cur_player = cur_player;

    return jeu;
}

extern void free_game(struct game *game)
{
    int i = 0;

    for(i = 0 ; i < game->xsize ; i++)
    {
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}

extern int apply_moves(struct game *game, const struct move *moves)
{
    return 0;
}

extern int is_move_seq_valid(const struct game *game, const struct move_seq *seq, const struct move_seq *prev, struct coord *taken)
{
    int i = 0, j = 0;

    if (game->board[seq->c_new.x][seq->c_new.y] != 0)
        return 0;

    if(abs(seq->c_old.y-seq->c_new.y) == 1)
    {
        if(game->cur_player == PLAYER_WHITE && seq->c_old.x-seq->c_new.x == (2*game->cur_player)-1)
            return 1;
        else
            return 0;
    }
    else if(abs(seq->c_old.y-seq->c_new.y) == 2)
    {
        if(abs(seq->c_old.x-seq->c_new.x) != 2)
            return 0;
        else
        {
            i = seq->c_old.x + (seq->c_new.x-seq->c_old.x)/2;
            j = seq->c_old.y + (seq->c_new.y-seq->c_old.y)/2;

            if(game->board[i][j] == 5 - (4*game->cur_player))
            {
                taken->x  = i;
                taken->y = j;
                return 2;
            }
            else
                return 0;
        }
    }
    else
    {
        return 0;
    }
}
