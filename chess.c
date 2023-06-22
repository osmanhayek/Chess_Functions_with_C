#include "chess.h"

int	in_coor(int x, int y, int **coor, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (x == coor[i][0] && y == coor[i][1])
			return (1);
	}
	return (0);
}

int	check_rock(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k)
{
	int	i;

	for (i = x; i < size; i++)
	{
		if (in_coor(i, y, coor, coor_size) && (i != x))
			break;
		if (i == x_k && y == y_k)
			return (1);
	}
	for (i = x; i >= 0; i--)
	{
		if (in_coor(i, y, coor, coor_size) && (i != x))
			break;
		if (i == x_k && y == y_k)
			return (1);
	}
	for (i = y; i < size; i++)
	{
		if (in_coor(x, i, coor, coor_size) && (i != y))
			break;
		if (x == x_k && i == y_k)
			return (1);
	}
	for (i = y; i >= 0; i--)
	{
		if (in_coor(x, i, coor, coor_size) && (i != y))
			break;
		if (x == x_k && i == y_k)
			return (1);
	}
	return (0);
}

int	check_pawn(int size, int x, int y, int x_k, int y_k)
{
	if (x - 1 == x_k && y - 1 == y_k)
		return (1);
	if (x - 1 == x_k && y + 1 == y_k)
		return (1);
	return (0);
}

int	check_bichop(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k)
{
	int	i;
	int	j;

	for (i = x, j = y; j < size && i < size; i++, j++)
	{
		if (in_coor(i, j, coor, coor_size) && (i != x && j != y))
			break;
		if (i == x_k && j == y_k)
			return (1);
	}
	for (i = x, j = y; j >= 0 && i >= 0; i--, j--)
	{
		if (in_coor(i, j, coor, coor_size) && (i != x && j != y))
			break;
		if (i == x_k && j == y_k)
			return (1);
	}
	for (i = x, j = y; j < size && i >= 0; i--, j++)
	{
		if (in_coor(i, j, coor, coor_size) && (i != x && j != y))
			break;
		if (i == x_k && j == y_k)
			return (1);
	}
	for (i = x, j = y; j >= 0 && i < size; i++, j--)
	{
		if (in_coor(i, j, coor, coor_size) && (i != x && j != y))
			break;
		if (i == x_k && j == y_k)
			return (1);
	}
	return (0);
}

int	check_queen(int size, int x, int y, int **coor, int coor_size, int x_k, int y_k)
{
	return (check_bichop(size ,x, y, coor, coor_size, x_k, y_k) || check_rock(size, x, y, coor, coor_size, x_k, y_k));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}