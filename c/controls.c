#include <stdio.h>
#include <stdlib.h>
#include "../header/objectManipulation.h"
#include "../header/controls.h"

void input(shape* current_shape)
{
    char command;
    printf("Enter a command (a/s/d for movement, q/e for rotation, x to exit): ");
    if (scanf(" %c", &command) != 1)
    {
        return;
    }

    switch (command)
    {
        case 'a':
            moveLeft(current_shape);
            break;
        case 's':
            moveDown(current_shape);
            break;
        case 'd':
            moveRight(current_shape);
            break;
        case 'q':
            rotation(true, current_shape);
            break;
        case 'e':
            rotation(false, current_shape);
            break;
        case 'x':
            printf("Exiting the game.\n");
            exit(0);
        default:
            printf("Invalid command. Please try again.\n");
    }
}