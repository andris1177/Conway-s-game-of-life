#include "../header/window.h"

void initDisplay(int width, int heigth)
{
    InitWindow(width, heigth, "Conway's Game of Life");
    SetTargetFPS(60);
}

void draw(maps* m, int iter, int width, int heigth)
{
    int livingCount = 0;

    BeginDrawing();

    ClearBackground(BLACK);
    DrawText(TextFormat("Current iteration: %d", iter), 40, 45, 25, WHITE);
    DrawRectangle(0, 95, heigth, 5, WHITE);

    int gap = 10;
    int stats = 100;

    int firstX = gap;
    int firstY = gap+stats;

    int sizeX = (width / m->width) - gap;
    int sizeY = ((heigth-stats) / m->height) - gap;

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            if (m->curMap[i][j] == 1)
            {
                DrawRectangle(firstX, firstY, sizeX, sizeY, WHITE);
                livingCount++;
            }

            firstY += sizeY+gap;
        }

        firstY = gap+stats;
        firstX += sizeX+gap;
    }

    DrawText(TextFormat("Currently living cells: %d", livingCount), 350, 45, 25, WHITE);

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