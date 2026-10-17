#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "../header/objectManipulation.h"
#include "../header/controls.h"

void input(shape* current_shape, grid* board)
{
    if (current_shape == NULL || board == NULL || !_kbhit())
    {
        return;
    }

    int command = _getch();
    square* original_form = malloc(
        (size_t)current_shape->count * sizeof(*original_form));
    if (original_form == NULL)
    {
        return;
    }
    memcpy(original_form, current_shape->form,
           (size_t)current_shape->count * sizeof(*original_form));

    switch (command)
    {
        case 'a':
            moveLeft(current_shape);
            if (!canPlaceShape(current_shape, board))
            {
                memcpy(current_shape->form, original_form,
                       (size_t)current_shape->count * sizeof(*original_form));
            }
            break;
        case 's':
            if (!hitbottom(current_shape, board))
            {
                moveDown(current_shape);
            }
            break;
        case 'd':
            moveRight(current_shape);
            if (!canPlaceShape(current_shape, board))
            {
                memcpy(current_shape->form, original_form,
                       (size_t)current_shape->count * sizeof(*original_form));
            }
            break;
        case 'r':
            rotation(true, current_shape);
            if (!canPlaceShape(current_shape, board))
            {
                memcpy(current_shape->form, original_form,
                       (size_t)current_shape->count * sizeof(*original_form));
            }
            break;
        case 'x':
            exit(0);
    }
    free(original_form);
}