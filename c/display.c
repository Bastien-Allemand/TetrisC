#include "../header/display.h"
#include <stdio.h>

void SetShapeInGrid(shape* current_shape, grid* board)
{
    if (current_shape == NULL || current_shape->form == NULL || board == NULL ||
        board->cases == NULL)
    {
        return;
    }

    for (int i = 0; i < current_shape->count; i++)
    {
        int x = current_shape->form[i].x;
        int y = current_shape->form[i].y;
        if (y >= 0 && y < board->length && x >= 0 && x < board->width &&
            board->cases[y] != NULL)
        {
            board->cases[y][x].isEmpty = false;
        }
    }
}

void resetGrid(grid* board)
{
    if (board == NULL || board->cases == NULL)
    {
        return;
    }

    for (int i = 0; i < board->length; i++)
    {
        if (board->cases[i] == NULL)
        {
            continue;
        }
        for (int j = 0; j < board->width; j++)
        {
            board->cases[i][j].isEmpty = true;
            board->cases[i][j].square = NULL;
        }
    }
}

void displayGrid(grid* board)
{
    if (board == NULL || board->cases == NULL)
    {
        return;
    }

    for (int i = board->length - 1; i >= 0; i--)
    {
        for (int j = 0; j < board->width; j++)
        {
            if (board->cases[i][j].isEmpty)
            {
                printf(" . ");
            }
            else
            {
                printf(" # ");
            }
            
        }
        printf("\n");
    }
    
}
