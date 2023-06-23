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

int **can_attack_collection(chess_piece *pieces, int num_of_pieces, int *new_size)
{
	int	**result;
	int	size;
	int	index;

	size = 0;
	index = 0;
	for (int i = 0; i < num_of_pieces; i++)
		size += pieces[i].num_can_attack;
	result = (int **)malloc(sizeof(int *) * size);
	for (int i = 0; i < num_of_pieces; i++)
	{
		for (int j = 0; j < pieces[i].num_can_attack; j++)
		{
			result[index] = (int *)malloc(sizeof(int) * 2);
			result[index][0] = pieces[i].can_attack[j][0];
			result[index++][1] = pieces[i].can_attack[j][1];
		}
	}
	*new_size = index;
	return (result);
}

int in_the_collection(int size,int **coll, int x, int y)
{
	for (int i = 0; i < size; i++)
	{
		if (x == coll[i][0] && y == coll[i][1])
			return (1);
	}
	return (0);
}

int is_check_mate(chess_piece *pieces, int num_of_pieces ,int board_size, int x_k, int y_k)
{
	int **collection;
	int	size;
	
	collection = can_attack_collection(pieces, num_of_pieces,&size);
	//check if the king is in check 
	if (in_the_collection(size, collection, x_k, y_k))
	{
		if (!in_the_collection(size, collection, x_k + 1, y_k))
			return (0);
		if (!in_the_collection(size, collection, x_k, y_k + 1))
			return (0);
		if (!in_the_collection(size, collection, x_k - 1, y_k))
			return (0);
		if (!in_the_collection(size, collection, x_k, y_k - 1))
			return (0);
		if (!in_the_collection(size, collection, x_k - 1, y_k - 1))
			return (0);
		if (!in_the_collection(size, collection, x_k - 1, y_k + 1))
			return (0);
		if (!in_the_collection(size, collection, x_k + 1, y_k + 1))
			return (0);
		if (!in_the_collection(size, collection, x_k + 1, y_k - 1))
			return (0);
		return (1);
	}
	return (0);
}

int    **set_attack_for_rock(chess_piece *rock, int **coor, int coor_size, int size)
{
	int	i;
	int index;

	rock->can_attack = (int **)malloc(sizeof(int *) * (size * size));
	index = 0;
	for (i = rock->x; i < size; i++)
	{
		if (in_coor(i, rock->y, coor, coor_size) && (i != rock->x))
			break;
		rock->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		rock->can_attack[index][0] = i; rock->can_attack[index++][1] = rock->y;
	}
	for (i = rock->x; i >= 0; i--)
	{
		if (in_coor(i, rock->y, coor, coor_size) && (i != rock->x))
			break;
		rock->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		rock->can_attack[index][0] = i; rock->can_attack[index++][1] = rock->y;
	}
	for (i = rock->y; i < size; i++)
	{
		if (in_coor(rock->x, i, coor, coor_size) && (i != rock->y))
			break;
		rock->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		rock->can_attack[index][0] = rock->x ;rock->can_attack[index++][1] = i;
	}
	for (i = rock->y; i >= 0; i--)
	{
		if (in_coor(rock->x, i, coor, coor_size) && (i != rock->y))
			break;
		rock->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		rock->can_attack[index][0] = rock->x ;rock->can_attack[index++][1] = i;
	}
	rock->num_can_attack = index;
	return (rock->can_attack);
}

int    **set_attack_for_bichop(chess_piece *bishop, int **coor, int coor_size, int size)
{
	int	i;
	int	j;
	int	index;

	index = 0;
	bishop->can_attack = (int **)malloc(sizeof(int *) * (size * size));
	for (i = bishop->x, j = bishop->y; j < size && i < size; i++, j++)
	{
		if (in_coor(i, j, coor, coor_size) && (i != bishop->x && j != bishop->y))
			break;
		bishop->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		bishop->can_attack[index][0] = i;bishop->can_attack[index++][1] = j;
	}
	for (i = bishop->x, j = bishop->y; j >= 0 && i >= 0; i--, j--)
	{
		if (in_coor(i, j, coor, coor_size) && (i != bishop->x && j != bishop->y))
			break;
		bishop->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		bishop->can_attack[index][0] = i;bishop->can_attack[index++][1] = j;
	}
	for (i = bishop->x, j = bishop->y; j < size && i >= 0; i--, j++)
	{
		if (in_coor(i, j, coor, coor_size) && (i != bishop->x && j != bishop->y))
			break;
		bishop->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		bishop->can_attack[index][0] = i;bishop->can_attack[index++][1] = j;
	}
	for (i = bishop->x, j = bishop->y; j >= 0 && i < size; i++, j--)
	{
		if (in_coor(i, j, coor, coor_size) && (i != bishop->x && j != bishop->y))
			break;
		bishop->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		bishop->can_attack[index][0] = i;bishop->can_attack[index++][1] = j;
	}
	bishop->num_can_attack = index;
	return (bishop->can_attack);
}

void    set_attack_for_queen(chess_piece *queen, int **coor, int coor_size, int size)
{
	int	i;
	int j;
	int index;

	queen->can_attack = (int **)malloc(sizeof(int *) * (size * size));
	index = 0;
	// The rock things

	for (i = queen->x; i < size; i++)
	{
		if (in_coor(i, queen->y, coor, coor_size) && (i != queen->x))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = i; queen->can_attack[index++][1] = queen->y;
	}
	for (i = queen->x; i >= 0; i--)
	{
		if (in_coor(i, queen->y, coor, coor_size) && (i != queen->x))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = i; queen->can_attack[index++][1] = queen->y;
	}
	for (i = queen->y; i < size; i++)
	{
		if (in_coor(queen->x, i, coor, coor_size) && (i != queen->y))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = queen->x ;queen->can_attack[index++][1] = i;
	}
	for (i = queen->y; i >= 0; i--)
	{
		if (in_coor(queen->x, i, coor, coor_size) && (i != queen->y))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = queen->x ;queen->can_attack[index++][1] = i;
	}

	//The Bishops things
	for (i = queen->x, j = queen->y; j < size && i < size; i++, j++)
	{
		if (in_coor(i, j, coor, coor_size) && (i != queen->x && j != queen->y))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = i;queen->can_attack[index++][1] = j;
	}
	for (i = queen->x, j = queen->y; j >= 0 && i >= 0; i--, j--)
	{
		if (in_coor(i, j, coor, coor_size) && (i != queen->x && j != queen->y))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = i;queen->can_attack[index++][1] = j;
	}
	for (i = queen->x, j = queen->y; j < size && i >= 0; i--, j++)
	{
		if (in_coor(i, j, coor, coor_size) && (i != queen->x && j != queen->y))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = i;queen->can_attack[index++][1] = j;
	}
	for (i = queen->x, j = queen->y; j >= 0 && i < size; i++, j--)
	{
		if (in_coor(i, j, coor, coor_size) && (i != queen->x && j != queen->y))
			break;
		queen->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		queen->can_attack[index][0] = i;queen->can_attack[index++][1] = j;
	}
	queen->num_can_attack = index;
}

void    set_attack_for_pawn(chess_piece *pawn, int **coor, int coor_size)
{
	int	index;

	index = 0;
	pawn->can_attack = (int **)malloc(sizeof(int *) * 2);
	if (!in_coor(pawn->x - 1, pawn->y - 1, coor, coor_size))
	{
		pawn->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		pawn->can_attack[index][0] = pawn->x - 1;pawn->can_attack[index++][1] = pawn->y - 1;
	}
	if (!in_coor(pawn->x - 1, pawn->y + 1, coor, coor_size))
	{
		pawn->can_attack[index] = (int *)malloc(sizeof(int) * 2);
		pawn->can_attack[index][0] = pawn->x - 1;pawn->can_attack[index++][1] = pawn->y + 1;
	}
	pawn->num_can_attack = index;
}