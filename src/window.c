#include "../header/window.h"

void initDisplay(int width, int heigth)
{
    InitWindow(width, heigth, "Conway's Game of Life");
    SetTargetFPS(60);
}

void draw(maps* m)
{
    BeginDrawing();

    ClearBackground(BLACK);

    for (int i = 0; i < m->width*m->heighth; i++)
    {
        if (m->curMap[i])
        {
            DrawRectangle(i*60, i*60, 50, 50, WHITE);
        }
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