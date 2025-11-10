#include "../header/window.h"

void initDisplay(int width, int heigth)
{
    InitWindow(width, heigth, "Conway's Game of Life");
    SetTargetFPS(60);
}

void draw(maps* m, int iter, int width, int heigth, bool pause)
{
    int livingCount = 0;
    
    int stats = 100;
    int gap = 2;
    int avlWidth = width;
    int avlHeight = heigth - stats;
    int size; 

    // caculate the max size in x direction and y witha given map size and window size
    int sizeX = (avlWidth - m->width * gap) / m->width;
    int sizeY = (avlHeight - m->height * gap) / m->height;

    if (sizeX == sizeY)
    {
        size = sizeY;
    }

    else if (sizeX > sizeY)
    {
        size = sizeY;
    }

    else if (sizeX < sizeY)
    {
        size = sizeX;
    }

    int displayMapSizeX = (m->width * size) + ((m->width - 2) * gap);
    int displayMapSizeY = (m->height * size) + ((m->height - 2) * gap);

    int x = (avlWidth - displayMapSizeX) / 2;
    int y = ((avlHeight - displayMapSizeY) / 2) + stats;

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < m->height; i++)
    {
        for (int j = 0; j < m->width; j++)
        {
            if (m->preMap[i][j] == 1)
            {
                DrawRectangle(x, y, size, size, WHITE);
                livingCount++;
            }

            x += (size + gap);
        }

        y += (size + gap);
        x = (avlWidth - displayMapSizeX) / 2;
    }

    // simulation stats
    DrawText(TextFormat("Current iteration: %d", iter), 40, 40, 25, WHITE);
    DrawText(TextFormat("Currently living cells: %d", livingCount), width - (MeasureText("Currently living cells:xxx", 25) + 40), 40, 25, WHITE);
    DrawRectangle(0, 93, width, 5, WHITE);

    if (pause)
    {
        DrawText(TextFormat("PAUSED", livingCount), (width / 2) - (MeasureText("PAUSED", 25) / 2), 40, 25, WHITE);
    }

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