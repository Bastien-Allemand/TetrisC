#include "../header/objectManipulation.h"
#include <stdlib.h>

void rotation(bool dir, shape* current_shape)
{
    if (current_shape == NULL || current_shape->form == NULL ||
        current_shape->count <= 0 || current_shape->type == SQUARE)
    {
        return;
    }

    int pivot_x = current_shape->form[0].x;
    int pivot_y = current_shape->form[0].y;

    for (int i = 0; i < current_shape->count; i++)
    {
        int x = current_shape->form[i].x - pivot_x;
        int y = current_shape->form[i].y - pivot_y;

        if (dir)
        {
            current_shape->form[i].x = pivot_x + y;
            current_shape->form[i].y = pivot_y - x;
        }
        else
        {
            current_shape->form[i].x = pivot_x - y;
            current_shape->form[i].y = pivot_y + x;
        }
    }
}

void moveDown(shape* current_shape)
{
    if (current_shape == NULL || current_shape->form == NULL)
    {
        return;
    }
    for (int i = 0; i < current_shape->count; i++)
    {
        current_shape->form[i].y--;
    }
}

void moveLeft(shape* current_shape)
{
    if (current_shape == NULL || current_shape->form == NULL)
    {
        return;
    }
    for (int i = 0; i < current_shape->count; i++)
    {
        current_shape->form[i].x--;
    }
}

void moveRight(shape* current_shape)
{
    if (current_shape == NULL || current_shape->form == NULL)
    {
        return;
    }
    for (int i = 0; i < current_shape->count; i++)
    {
        current_shape->form[i].x++;
    }
}

void fusion(shape* shape1, shape* shape2)
{
    if (shape1 == NULL || shape2 == NULL || shape1 == shape2 ||
        shape1->form == NULL || shape2->form == NULL ||
        shape1->count < 0 || shape2->count < 0)
    {
        return;
    }

    int newCount = shape1->count + shape2->count;
    square* newForm = realloc(shape1->form, (size_t)newCount * sizeof(square));
    if (newForm == NULL)
    {
        return;
    }

    for (int i = 0; i < shape2->count; i++)
    {
        newForm[shape1->count + i] = shape2->form[i];
    }

    free(shape2->form);
    shape1->form = newForm;
    shape1->count = newCount;
    shape2->form = NULL;
    shape2->count = 0;
}

bool hitbottom(shape* current_shape, grid* board)
{
    if (current_shape == NULL || current_shape->form == NULL ||
        board == NULL || board->cases == NULL)
    {
        return true;
    }

    for (int i = 0; i < current_shape->count; i++)
    {
        int x = current_shape->form[i].x;
        int y = current_shape->form[i].y;

        if (y < 0 || y >= board->length || x < 0 || x >= board->width ||
            board->cases[y] == NULL)
        {
            return true;
        }

        if (!board->cases[y][x].isEmpty)
        {
            return true;
        }
    }
    return false;
}
