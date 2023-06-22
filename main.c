#include "chess.h"

static inline
void    coordinate_for_king(int *x_k, int *y_k, char **av)
{
    int fouded = 0;
    for (int i = 1; av[i]; i++)
    {
        for (int j = 0; av[i][j]; j++)
        {
            if (av[i][j] == 'K')
            {
                *x_k = i - 1;
                *y_k = j;
                fouded = 1;
                break;
            }
        }
        if (fouded)
            break;
    }
}

static inline
int    **coordinate_list(char **av,int size, int *actually_size)
{
    int    **result;
    int     index;

    result = (int **)malloc(sizeof(int *) * (size * size));
    index = 0;
    for (int i = 1; av[i]; i++)
    {
        for (int j = 0; av[i][j]; j++)
        {
            if (av[i][j] == 'R' || av[i][j] == 'Q' || av[i][j] == 'B' || av[i][j] == 'P')
            {
                result[index] = (int *)malloc(sizeof(int *) * 2);
                result[index][0] = i - 1; result[index++][1] = j;
            }
        }
    }
    *actually_size = index;
    return (result);
}
static inline
void    freeleme(int **coor, int size)
{
    for (int i = 0; i < size; i++)
        free(coor[i]);
    free(coor);
}

int main(int ac, char **av)
{
    int size;
    int x_k;
    int y_k;
    int **coor;
    int done;
    int coor_size;

    if (ac > 1)
    {
        size = ft_strlen(av[1]);
        coordinate_for_king(&x_k, &y_k, av);
        done = 0;
        coor = coordinate_list(av, size, &coor_size);
        for (int i = 1; av[i]; i++)
        {
            for (int j = 0; av[i][j]; j++)
            {
                if (done)
                    break;
                switch (av[i][j])
                {
                case 'R':
                    if (check_rock(size, i - 1, j, coor, coor_size, x_k, y_k))
                    {
                        done = 1;
                        printf("Success!");
                    }    
                    break;
                case 'Q':
                    if (check_queen(size, i - 1, j, coor, coor_size, x_k, y_k))
                    {
                        done = 1;
                        printf("Success!");
                    }
                    break;
                case 'P':
                    if (check_pawn(size, i - 1, j, x_k, y_k))
                    {
                        done = 1;
                        printf("Success!");
                    }
                    break;
                case 'B':
                    if (check_bichop(size, i - 1, j, coor, coor_size, x_k, y_k))
                    {
                        done = 1;
                        printf("Success!");
                    }
                    break;
                default:
                    break;
                }
            }
            if (done)
                break;
        }
        if (!done)
            printf("Fail!");
        freeleme(coor, coor_size);
    }
    printf("\n");
}