#include "../header/shapeCreation.h"
#include <stdlib.h>

square* createSquare(int x, int y)
{
    square* new_square = malloc(sizeof(*new_square));
    if (new_square == NULL)
    {
        return NULL;
    }

    new_square->x = x;
    new_square->y = y;
    return new_square;
}

static shape* createShapeFromSquares(TYPE type, const square* squares, int count)
{
    shape* new_shape = malloc(sizeof(*new_shape));
    if (new_shape == NULL)
    {
        return NULL;
    }

    new_shape->form = malloc((size_t)count * sizeof(*new_shape->form));
    if (new_shape->form == NULL)
    {
        free(new_shape);
        return NULL;
    }

    for (int i = 0; i < count; i++)
    {
        new_shape->form[i] = squares[i];
    }

    new_shape->count = count;
    new_shape->type = type;
    return new_shape;
}

shape* createLShape(void)
{
    const square squares[] = {{0, 0}, {0, 1}, {0, 2}, {1, 2}};
    return createShapeFromSquares(LSHAPE, squares, 4);
}

shape* createRLShape(void)
{
    const square squares[] = {{1, 0}, {1, 1}, {1, 2}, {0, 2}};
    return createShapeFromSquares(RLSHAPE, squares, 4);
}

shape* createSShape(void)
{
    const square squares[] = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
    return createShapeFromSquares(SSHAPE, squares, 4);
}

shape* createRSShape(void)
{
    const square squares[] = {{2, 1}, {1, 1}, {1, 0}, {0, 0}};
    return createShapeFromSquares(RSSHAPE, squares, 4);
}

shape* createIShape(void)
{
    const square squares[] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    return createShapeFromSquares(ISHAPE, squares, 4);
}

shape* createSquareShape(void)
{
    const square squares[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    return createShapeFromSquares(SQUARE, squares, 4);
}

shape* createTShape(void)
{
    const square squares[] = {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
    return createShapeFromSquares(TSHAPE, squares, 4);
}

shape* createShape(TYPE type)
{
    switch (type)
    {
        case LSHAPE:
            return createLShape();
        case RLSHAPE:
            return createRLShape();
        case SSHAPE:
            return createSShape();
        case RSSHAPE:
            return createRSShape();
        case ISHAPE:
            return createIShape();
        case SQUARE:
            return createSquareShape();
        case TSHAPE:
            return createTShape();
        default:
            return NULL;
    }
}
