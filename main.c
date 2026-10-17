#include "header/object.h"
#include "header/objectManipulation.h"
#include "header/grid.h"
#include "header/display.h"
#include "header/shapeCreation.h"
#include "header/controls.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

double updateDeltaTime()
{
    static LARGE_INTEGER frequency;
    static LARGE_INTEGER lastTime;
    static bool initialized = false;
    LARGE_INTEGER currentTime;

    if (!initialized)
    {
        if (!QueryPerformanceFrequency(&frequency) ||
            !QueryPerformanceCounter(&lastTime))
        {
            return -1.0;
        }
        initialized = true;
        return 0.0;
    }

    if (!QueryPerformanceCounter(&currentTime))
    {
        return -1.0;
    }

    double delta = (double)(currentTime.QuadPart - lastTime.QuadPart) /
                   (double)frequency.QuadPart;
    lastTime = currentTime;
    return delta;
}

static void positionShape(shape* current_shape, int x, int y)
{
    for (int i = 0; i < current_shape->count; i++)
    {
        current_shape->form[i].x += x;
        current_shape->form[i].y += y;
    }
}

int main()
{
    //hide cursor 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    double deltaTime;
    bool running = true;
    float counter = 0.0f;
    float lock_counter = 0.0f;
    int score = 0;
    grid* g = generateGrid(20, 10);
    srand((unsigned)time(NULL));

    if (g == NULL)
    {
        return EXIT_FAILURE;
    }

    shape* current_shape = createShape(rand() % 7);
    shape* global_shape = calloc(1, sizeof(*global_shape));
    if (current_shape == NULL || global_shape == NULL)
    {
        return EXIT_FAILURE;
    }
    positionShape(current_shape, g->width / 2 - 1, g->length - 4);
    global_shape->type = GROUP;
    while (running)
    {
        deltaTime = updateDeltaTime();
        if (deltaTime < 0.0) return EXIT_FAILURE;

        resetGrid(g);
        SetShapeInGrid(global_shape, g);
        input(current_shape, g);
        bool grounded = hitbottom(current_shape, g);
        if (grounded)
        {
            lock_counter += (float)deltaTime;
            if (lock_counter >= 0.5f)
            {
                fusion(global_shape,current_shape);
                current_shape = createShape(rand() % 7);
                positionShape(current_shape, g->width / 2 - 1, g->length - 4);
                counter = 0.0f;
                lock_counter = 0.0f;
                score += 100 * clearCompletedRows(global_shape, g);
            }
        }
        else
        {
            lock_counter = 0.0f;
            if (counter >= 1.0f)
            {
                moveDown(current_shape);
                counter = 0.0f;
            }
            else
            {
                counter += (float)deltaTime;
            }
        }

        resetGrid(g);
        SetShapeInGrid(current_shape, g);
        SetShapeInGrid(global_shape, g);
        displayGrid(g, score);

        // move the cursor to the top-left corner of the console
        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }
}