#include "../header/window.h"

void initDisplay(maps* map, windowSpec* wSpec)
{
    InitWindow(wSpec->windowWidth, wSpec->windowHeight, "Conway's Game of Life");
    SetTargetFPS(wSpec->fps);
    getCellSize(map, wSpec, true);
    wSpec->moveX = 0;
    wSpec->moveY = 0;
    wSpec->isRaylibInit = true;
}

void getCellSize(const maps* map, windowSpec* wSpec, bool init)
{
    if (init)
    {
        wSpec->avlWidth = wSpec->windowWidth;
        wSpec->avlHeight = wSpec->windowHeight - (2 * STATS_SIZE); 

        // caculate the max size in x and y directions with a given map size and window size
        int sizeX = (wSpec->avlWidth - map->width * CELL_GAP) / map->width;
        int sizeY = (wSpec->avlHeight - map->height * CELL_GAP) / map->height;

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
            fprintf(stderr, "To small window resolution for the given map. exiting...\n");
            freeAll();
            deInitDisplay();
            memReport();
            exit(ERROR_INPUT);
        }

        wSpec->originalSize = wSpec->size;
    }

    wSpec->displayMapSizeX = (map->width * wSpec->size) + ((map->width - 2) * CELL_GAP);
    wSpec->displayMapSizeY = (map->height * wSpec->size) + ((map->height - 2) * CELL_GAP);

    wSpec->startX = ((wSpec->avlWidth - wSpec->displayMapSizeX) / 2) + wSpec->moveX;
    wSpec->startY = (((wSpec->avlHeight - wSpec->displayMapSizeY) / 2) + STATS_SIZE) + wSpec->moveY;
}

void zoom(maps* map, windowSpec* wSpec, int amount)
{
    if (wSpec->size + amount >= 1)
    {
        wSpec->size += amount;
        getCellSize(map, wSpec, false);
    }
}

void pivot(maps* map, windowSpec* wSpec, int amount, int direction)
{
    if (direction == 1)
    {
        wSpec->moveX += amount;
    }

    if (direction == 2)
    {
        wSpec->moveY += amount;
    }

    getCellSize(map, wSpec, false);
}

void refit(maps* map, windowSpec* wSpec)
{
    wSpec->size = wSpec->originalSize;
    wSpec->moveX = 0;
    wSpec->moveY = 0;
    getCellSize(map, wSpec, false);
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

            x += (wSpec->size + CELL_GAP);
        }

        y += (wSpec->size + CELL_GAP);
        x = ((wSpec->avlWidth - wSpec->displayMapSizeX) / 2) + wSpec->moveX;
    }

    // simulation stats top
    DrawRectangle(0, 0, wSpec->windowWidth, 98, PINK);
    DrawText(TextFormat("Current iteration: %d", map->index), 40, 40, 25, WHITE);
    DrawText(TextFormat("Currently living cells: %d", livingCount), wSpec->windowWidth - (MeasureText("Currently living cells:xxx", 25) + 40), 40, 25, WHITE);
    DrawRectangle(0, 93, wSpec->windowWidth, 5, WHITE);

    // simulation stats bottom
    DrawRectangle(0, wSpec->windowHeight - STATS_SIZE + 2, wSpec->windowWidth, 98, PINK);
    DrawText(TextFormat("%.2lfx", (double)wSpec->size / (double)wSpec->originalSize), wSpec->windowWidth - (MeasureText("1.00x", 25) + 40), wSpec->windowHeight - 55, 25, WHITE);
    DrawText(TextFormat("FPS:          %d", GetFPS()), 40, wSpec->windowHeight - 40, 25, WHITE);
    DrawText(TextFormat("Frametime:   %lf", GetFrameTime()), 40, wSpec->windowHeight - 70, 25, WHITE);
    DrawRectangle(0, wSpec->windowHeight - 97, wSpec->windowWidth, 5, WHITE);

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