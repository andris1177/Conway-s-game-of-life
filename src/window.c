#include "../header/window.h"

void initDisplay(int width, int heigth)
{
    InitWindow(width, heigth, "Conway's Game of Life");
    SetTargetFPS(60);
}

void draw(maps* m, int iter, int width, int heigth)
{
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText(TextFormat("Integer value: %d", iter), 500, 500, 10, WHITE);

    int gap = 10;

    int firstX = gap;
    int firstY = gap;

    int sizeX = (width / m->width) - gap;
    int sizeY = (heigth / m->height) - gap;

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            if (m->curMap[i][j] == 1)
            {
                DrawRectangle(firstX, firstY, sizeX, sizeY, WHITE);
            }

            firstY += sizeY+gap;
        }

        firstY = gap;
        firstX += sizeX+gap;
    }

    EndDrawing();
}

bool isWindowShouldClose()
{
    return WindowShouldClose();
}

void deInitDisplay()
{
    CloseWindow();
}