#ifndef TETRIS_DISPLAY_H
#define TETRIS_DISPLAY_H

#include "object.h"
#include "grid.h"

void SetShapeInGrid(shape* current_shape, grid* board);
void resetGrid(grid* board);
void displayGrid(grid* board, int score);

#endif