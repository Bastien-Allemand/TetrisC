#include "../header/objectManipulation.h"
#include <stdlib.h>

static bool isRowComplete(const shape* settled_shape, int row, int width)
{
    bool* occupied = calloc((size_t)width, sizeof(*occupied));
    if (occupied == NULL)
    {
        return false;
    }

    int occupied_count = 0;
    for (int i = 0; i < settled_shape->count; i++)
    {
        int x = settled_shape->form[i].x;
        if (settled_shape->form[i].y == row && x >= 0 && x < width &&
            !occupied[x])
        {
            occupied[x] = true;
            occupied_count++;
        }
    }

    free(occupied);
    return occupied_count == width;
}

int clearCompletedRows(shape* settled_shape, grid* board)
{
    if (settled_shape == NULL || settled_shape->form == NULL ||
        board == NULL || board->width <= 0 || board->length <= 0)
    {
        return 0;
    }

    int cleared_rows = 0;
    for (int row = 0; row < board->length; row++)
    {
        if (!isRowComplete(settled_shape, row, board->width))
        {
            continue;
        }

        int write_index = 0;
        for (int read_index = 0; read_index < settled_shape->count;
             read_index++)
        {
            square current = settled_shape->form[read_index];
            if (current.y == row)
            {
                continue;
            }

            if (current.y > row)
            {
                current.y--;
            }
            settled_shape->form[write_index++] = current;
        }
        settled_shape->count = write_index;
        cleared_rows++;
        row--;
    }

    if (settled_shape->count == 0)
    {
        free(settled_shape->form);
        settled_shape->form = NULL;
    }
    else
    {
        square* resized = realloc(
            settled_shape->form,
            (size_t)settled_shape->count * sizeof(*settled_shape->form));
        if (resized != NULL)
        {
            settled_shape->form = resized;
        }
    }
    return cleared_rows;
}

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

void fusion(shape* to, shape* from)
{
    if (to == NULL || from == NULL || to == from ||
        from->form == NULL ||
        to->count < 0 || from->count < 0)
    {
        return;
    }

    int newCount = to->count + from->count;
    square* newForm = realloc(to->form, (size_t)newCount * sizeof(*newForm));
    if (newForm == NULL)
    {
        return;
    }

    for (int i = 0; i < from->count; i++)
    {
        newForm[to->count + i] = from->form[i];
    }

    free(from->form);
    to->form = newForm;
    to->count = newCount;
    from->form = NULL;
    from->count = 0;
}

bool hitbottom(shape* current_shape, grid* board)
{
    if (!canPlaceShape(current_shape, board))
    {
        return true;
    }

    for (int i = 0; i < current_shape->count; i++)
    {
        int x = current_shape->form[i].x;
        int next_y = current_shape->form[i].y - 1;
        if (next_y < 0)
        {
            return true;
        }
        if (next_y < board->length &&
            !board->cases[next_y][x].isEmpty)
        {
            return true;
        }
    }
    return false;
}

bool canPlaceShape(const shape* current_shape, const grid* board)
{
    if (current_shape == NULL || current_shape->form == NULL ||
        board == NULL || board->cases == NULL)
    {
        return false;
    }

    for (int i = 0; i < current_shape->count; i++)
    {
        int x = current_shape->form[i].x;
        int y = current_shape->form[i].y;
        if (x < 0 || x >= board->width || y < 0 || y >= board->length ||
            board->cases[y] == NULL || !board->cases[y][x].isEmpty)
        {
            return false;
        }
    }
    return true;
}
