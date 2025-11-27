#include "../header/window.h"

void initDisplay(const windowSpec* wSpec)
{
    InitWindow(wSpec->windowWidth, wSpec->windowHeight, "Conway's Game of Life");
    SetTargetFPS(wSpec->fps);
}

void getCellSize(windowSpec* wSpec, maps* map)
{
    wSpec->stats = 100;
    wSpec->gap = 2;
    wSpec->avlWidth = wSpec->windowWidth;
    wSpec->avlHeight = wSpec->windowHeight - wSpec->stats; 

    // caculate the max size in x direction and y witha given map size and window size
    int sizeX = (wSpec->avlWidth - map->width * wSpec->gap) / map->width;
    int sizeY = (wSpec->avlHeight - map->height * wSpec->gap) / map->height;

    if (sizeX == sizeY)
    {
        wSpec->size = sizeY;
    }

    else if (sizeX > sizeY)
    {
        wSpec->size = sizeY;
    }

    else if (sizeX < sizeY)
    {
        wSpec->size = sizeX;
    }

    if (wSpec->size < 1)
    {
        fprintf(stderr, "To small window resolution for the given map\n");
        freeMem(map);
        deInitDisplay();
        exit(ERROR_INPUT);
    }

    wSpec->displayMapSizeX = (map->width * wSpec->size) + ((map->width - 2) * wSpec->gap);
    wSpec->displayMapSizeY = (map->height * wSpec->size) + ((map->height - 2) * wSpec->gap);

    wSpec->startX = (wSpec->avlWidth - wSpec->displayMapSizeX) / 2;
    wSpec->startY = ((wSpec->avlHeight - wSpec->displayMapSizeY) / 2) + wSpec->stats;
}

void draw(const maps* map, windowSpec* wSpec, const bool pause)
{
    int livingCount = 0;
    

    int x = wSpec->startX;
    int y = wSpec->startY;

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if (map->preMap[i][j])
            {
                DrawRectangle(x, y, wSpec->size, wSpec->size, WHITE);
                livingCount++;
            }

            x += (wSpec->size + wSpec->gap);
        }

        y += (wSpec->size + wSpec->gap);
        x = (wSpec->avlWidth - wSpec->displayMapSizeX) / 2;
    }

    // simulation stats
    DrawText(TextFormat("Current iteration: %d", map->index), 40, 40, 25, WHITE);
    DrawText(TextFormat("Currently living cells: %d", livingCount), wSpec->windowWidth - (MeasureText("Currently living cells:xxx", 25) + 40), 40, 25, WHITE);
    DrawRectangle(0, 93, wSpec->windowWidth, 5, WHITE);

    if (pause)
    {
        DrawText("PAUSED", (wSpec->windowWidth / 2) - (MeasureText("PAUSED", 25) / 2), 40, 25, WHITE);
    }

    EndDrawing();
    livingCount = 0;
}

void deInitDisplay()
{
    CloseWindow();
}