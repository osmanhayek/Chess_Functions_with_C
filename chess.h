#ifndef CHESS_H
# define CHESS_H
#include <stdio.h>
#include <stdlib.h>

int	check_rock(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k);
int	check_bichop(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k);
int	check_pawn(int size, int x, int y, int x_k, int y_k);
int	check_queen(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k);
int	in_coor(int x, int y, int **coor, int size);
int	ft_strlen(char *str);

#endif