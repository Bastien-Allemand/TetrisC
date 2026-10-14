#include "header/object.h"
#include "header/objectManipulation.h"
#include "header/grid.h"
#include "header/display.h"
#include "header/shapeCreation.h"
#include "header/controls.h"
#include <stdlib.h>

int main()
{
    grid* board = generateGrid(10, 10);
    shape* current_shape = createShape(LSHAPE);
    if (board == NULL || current_shape == NULL)
    {
        free(board);
        free(current_shape);
        return EXIT_FAILURE;
    }

    while (1)
    {
        resetGrid(board);
        SetShapeInGrid(current_shape, board);
        displayGrid(board);
        input(current_shape);
    }
}