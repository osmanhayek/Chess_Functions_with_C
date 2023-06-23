#ifndef CHESS_H
# define CHESS_H
#include <stdio.h>
#include <stdlib.h>

typedef struct s_chess_piece
{
    char    type;
    int     x;
    int     y;
    int     num_can_attack;
    int     **can_attack;
}chess_piece;

int	    check_rock(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k);
int	    check_bichop(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k);
int	    check_pawn(int size, int x, int y, int x_k, int y_k);
int	    check_queen(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k);
int	    in_coor(int x, int y, int **coor, int size);
int	    ft_strlen(char *str);
int     **set_attack_for_rock(chess_piece *rock, int **coor, int coor_size, int size);
int     **set_attack_for_bichop(chess_piece *bishop, int **coor, int coor_size, int size);
void    set_attack_for_queen(chess_piece *queen, int **coor, int coor_size, int size);
void    set_attack_for_pawn(chess_piece *pawn, int **coor, int coor_size);
int     in_the_collection(int size,int **coll, int x, int y);
int     is_check_mate(chess_piece *pieces, int board_size, int num_of_pieces ,int x_k, int y_k);
int     **can_attack_collection(chess_piece *pieces, int num_of_pieces, int *new_size);

#endif