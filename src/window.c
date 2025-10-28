#include "../header/window.h"

void initDisplay(int width, int heigth)
{
    InitWindow(width, heigth, "Conway's Game of Life");
    SetTargetFPS(60);
}

void draw(maps* m, int iter)
{
    BeginDrawing();

    ClearBackground(BLACK);
    DrawText(TextFormat("Integer value: %d", iter), 500, 500, 10, WHITE);

    int firstX = 10;
    int firstY = 10;

    for (int i = 0; i < m->size; i++)
    {   
        if (i % 10 != 0)
        {
            firstX += 40;
        }
            
        if (i % 10 == 0)
        {
            firstX = 10;
            firstY += 40;
        }

        if (m->curMap[i] == 1)
        {
            DrawRectangle(firstX,firstY, 30, 30, WHITE);
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