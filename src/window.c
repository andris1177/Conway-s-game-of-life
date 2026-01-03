#define RAYGUI_IMPLEMENTATION
#include "../header/window.h"

void initDisplay(const windowSpec* wSpec)
{
    InitWindow(wSpec->windowWidth, wSpec->windowHeight, "Conway's Game of Life");
    SetTargetFPS(wSpec->fps);
}

void initMapDraw(const maps* map, windowSpec* wSpec)
{
    getCellSize(map, wSpec, true);
    wSpec->moveX = 0;
    wSpec->moveY = 0;
}

void getCellSize(const maps* map, windowSpec* wSpec, const bool init)
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
            safeExit("To small window resolution for the given map. exiting...\n", ERROR_INPUT, true);
        }

        wSpec->originalSize = wSpec->size;
    }

    wSpec->displayMapSizeX = (map->width * wSpec->size) + ((map->width - 2) * CELL_GAP);
    wSpec->displayMapSizeY = (map->height * wSpec->size) + ((map->height - 2) * CELL_GAP);

    wSpec->startX = ((wSpec->avlWidth - wSpec->displayMapSizeX) / 2) + wSpec->moveX;
    wSpec->startY = (((wSpec->avlHeight - wSpec->displayMapSizeY) / 2) + STATS_SIZE) + wSpec->moveY;
}

void zoom(const maps* map, windowSpec* wSpec, const int amount)
{
    if (wSpec->size + amount >= 1)
    {
        wSpec->size += amount;
        getCellSize(map, wSpec, false);
    }
}

void pivot(const maps* map, windowSpec* wSpec, const int amount, const int direction)
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

void refit(const maps* map, windowSpec* wSpec)
{
    wSpec->size = wSpec->originalSize;
    wSpec->moveX = 0;
    wSpec->moveY = 0;
    getCellSize(map, wSpec, false);
}

void drawMap(appContex* app, uiDrawFn ui)
{
    app->wSpec.livingCount = 0;
    
    int x = app->wSpec.startX;
    int y = app->wSpec.startY;

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < app->map->height; i++)
    {
        for (int j = 0; j < app->map->width; j++)
        {
            if (app->map->preMap[i][j])
            {
                DrawRectangle(x, y, app->wSpec.size, app->wSpec.size, WHITE);
                app->wSpec.livingCount++;
            }

            x += (app->wSpec.size + CELL_GAP);
        }

        y += (app->wSpec.size + CELL_GAP);
        x = ((app->wSpec.avlWidth - app->wSpec.displayMapSizeX) / 2) + app->wSpec.moveX;
    }

    ui(app->map, &app->wSpec);

    EndDrawing();
    app->wSpec.livingCount = 0;
}

void drawSimUi(const maps* map, const windowSpec* wSpec)
{
    // simulation stats top
    DrawRectangle(0, 0, wSpec->windowWidth, 98, PINK);
    DrawText(TextFormat("Current iteration: %d", map->index), 40, 40, 25, WHITE);
    DrawText(TextFormat("Currently living cells: %d", wSpec->livingCount), wSpec->windowWidth - (MeasureText("Currently living cells:xxx", 25) + 40), 40, 25, WHITE);
    DrawRectangle(0, 93, wSpec->windowWidth, 5, WHITE);

    // simulation stats bottom
    DrawRectangle(0, wSpec->windowHeight - STATS_SIZE + 2, wSpec->windowWidth, 98, PINK);
    DrawText(TextFormat("%.2lfx", (double)wSpec->size / (double)wSpec->originalSize), wSpec->windowWidth - (MeasureText("1.00x", 25) + 40), wSpec->windowHeight - 55, 25, WHITE);
    DrawText(TextFormat("FPS:          %d", GetFPS()), 40, wSpec->windowHeight - 40, 25, WHITE);
    DrawText(TextFormat("Frametime:   %lf", GetFrameTime()), 40, wSpec->windowHeight - 70, 25, WHITE);
    DrawRectangle(0, wSpec->windowHeight - 97, wSpec->windowWidth, 5, WHITE);

    if (wSpec->pause)
    {
        DrawText("PAUSED", (wSpec->windowWidth / 2) - (MeasureText("PAUSED", 25) / 2), 40, 25, WHITE);
    }
}

void drawEditorUi(const maps* map, const windowSpec* wSpec)
{
    // simulation stats top
    DrawRectangle(0, 0, wSpec->windowWidth, 98, PINK);
    DrawText(TextFormat("Currently living cells: %d", wSpec->livingCount), wSpec->windowWidth - (MeasureText("Currently living cells:xxx", 25) + 40), 40, 25, WHITE);
    DrawRectangle(0, 93, wSpec->windowWidth, 5, WHITE);

    // simulation stats bottom
    DrawRectangle(0, wSpec->windowHeight - STATS_SIZE + 2, wSpec->windowWidth, 98, PINK);
    DrawText(TextFormat("%.2lfx", (double)wSpec->size / (double)wSpec->originalSize), wSpec->windowWidth - (MeasureText("1.00x", 25) + 40), wSpec->windowHeight - 55, 25, WHITE);
    DrawText(TextFormat("FPS:          %d", GetFPS()), 40, wSpec->windowHeight - 40, 25, WHITE);
    DrawText(TextFormat("Frametime:   %lf", GetFrameTime()), 40, wSpec->windowHeight - 70, 25, WHITE);
    DrawRectangle(0, wSpec->windowHeight - 97, wSpec->windowWidth, 5, WHITE);
}

void drawMainMenu(const windowSpec* wSpec, appMode* aMode, bool* preMode)
{ 
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30); 
    GuiSetStyle(DEFAULT, TEXT_PADDING, 10);
    BeginDrawing();
    ClearBackground(BLACK);
    if (GuiButton((Rectangle){ wSpec->windowWidth / 2 - 150, wSpec->windowHeight / 2, 300, 70 }, "Map Editor"))
    {
        aMode->editorMenu = true;
        *preMode = false;
    }
    EndDrawing();
}

void drawEditorMenu(const windowSpec* wSpec, appMode* aMode, bool* preMode)
{
    BeginDrawing();
    ClearBackground(BLACK);
    int curr = 0;
    bool open = false;
    GuiDropdownBox((Rectangle){100, 100, 200, 100}, "test1;test2;test3", &curr, open);
    EndDrawing();
}

void deInitDisplay()
{
    CloseWindow();
}
