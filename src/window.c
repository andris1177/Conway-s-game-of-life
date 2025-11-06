#include "../header/window.h"

void initDisplay(int width, int heigth)
{
    InitWindow(width, heigth, "Conway's Game of Life");
    SetTargetFPS(60);
}

void draw(maps* m, int iter, int width, int heigth)
{
    int livingCount = 0;
    int  commonWindowSize;
    int gap = 2;
    int stats = 100;

    if (width == (heigth - stats))
    {
        commonWindowSize = width;
    }

    else if (width > heigth)
    {
        commonWindowSize = (heigth - stats);
    }

    else if (width < (heigth - stats))
    {
        commonWindowSize = width;
    }

    int firstX = ((width - commonWindowSize) / 2);
    int firstY = ((heigth - commonWindowSize) / 2) + (stats / 2);

    int size = (commonWindowSize / m->width) - gap;

    BeginDrawing();

    ClearBackground(BLACK);

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            if (m->curMap[i][j] == 1)
            {
                DrawRectangle(firstX, firstY, size, size, WHITE);
                livingCount++;
            }

            firstX += (size + gap);
        }

        firstY += (size + gap);
        firstX = ((width - commonWindowSize) / 2);
    }

    // simulation stats
    DrawText(TextFormat("Current iteration: %d", iter), 40, 45, 25, WHITE);
    DrawRectangle(0, 93, width, 5, WHITE);
    DrawText(TextFormat("Currently living cells: %d", livingCount), width - 400, 45, 25, WHITE);

    EndDrawing();
    livingCount = 0;
}

bool isWindowShouldClose()
{
    return WindowShouldClose();
}

void deInitDisplay()
{
    CloseWindow();
}