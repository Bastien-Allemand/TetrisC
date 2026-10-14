#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H

#include <stdbool.h>
#include "object.h"

typedef struct
{
    int x;
    int y;
    bool isEmpty;
    square* square;
} position;
typedef struct grid
{
    position** cases;
    int length;
    int width;

}grid;

bool checkRowComplete(grid* board, int row);
grid* generateGrid(int length, int width);

#endif