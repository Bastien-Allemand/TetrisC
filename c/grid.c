#include "../header/grid.h"
#include <stdlib.h>

bool checkRowComplete(grid* board, int row)
{
    if (board == NULL || board->cases == NULL || row < 0 ||
        row >= board->length || board->cases[row] == NULL)
    {
        return false;
    }

    for (int i = 0; i < board->width; i++)
    {
        if (board->cases[row][i].isEmpty)
        {
            return false;
        }
    }
    return true;
}

grid* generateGrid(int length, int width)
{
    if (length <= 0 || width <= 0)
    {
        return NULL;
    }

    grid* newGrid = calloc(1, sizeof(*newGrid));
    if (newGrid == NULL)
    {
        return NULL;
    }

    newGrid->cases = calloc((size_t)length, sizeof(*newGrid->cases));
    if (newGrid->cases == NULL)
    {
        free(newGrid);
        return NULL;
    }

    for (int i = 0; i < length; i++)
    {
        newGrid->cases[i] = calloc((size_t)width, sizeof(*newGrid->cases[i]));
        if (newGrid->cases[i] == NULL)
        {
            for (int row = 0; row < i; row++)
            {
                free(newGrid->cases[row]);
            }
            free(newGrid->cases);
            free(newGrid);
            return NULL;
        }

        for (int j = 0; j < width; j++)
        {
            newGrid->cases[i][j].x = j;
            newGrid->cases[i][j].y = i;
            newGrid->cases[i][j].isEmpty = true;
            newGrid->cases[i][j].square = NULL;
        }
    }
    newGrid->length = length;
    newGrid->width = width;
    return newGrid;
}