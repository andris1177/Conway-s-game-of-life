#include "../header/sim.h"

void initSim(maps* map, simSpec* simSpec, windowSpec* wSpec)
{
    readFile(map, simSpec, wSpec);
    initDisplay(wSpec);
    getCellSize(wSpec, map);
}

void makeMap(maps* map)
{
    if (map->width == 0 && map->height == 0)
    {
        printf("Map with 0 area is provided\n");
        exit(-1);
    }

    map->curMap = malloc(sizeof(bool*) * (size_t)map->height);
    map->preMap = malloc(sizeof(bool*) * (size_t)map->height);

    for (int i = 0; i < map->height; i++)
    {
        map->curMap[i] = (bool *)malloc(sizeof(bool) * (size_t)map->width);
        map->preMap[i] = (bool *)malloc(sizeof(bool) * (size_t)map->width);
    }
}

void applyRule(maps* map)
{
    int countn = 0;

    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (k == 0 && l == 0)
                    {
                        continue;
                    }

                    if (k+i < 0 || l+j < 0 || k+i > (map->height-1) || l+j > (map->width-1))
                    {
                        continue;
                    }

                    else
                    {
                        if (map->preMap[i+k][j+l] == 1)
                        {
                            countn++;
                        }
                    }
                }
            }

            if (countn < 2 || countn > 3)
            {
                map->curMap[i][j] = 0;
            }

            else if (countn == 3)
            {
                map->curMap[i][j] = 1;
            }

            else
            {
                map->curMap[i][j] = map->preMap[i][j];
            }

            countn = 0;
        }
    }

    bool** tmp = map->preMap;
    map->preMap = map->curMap;
    map->curMap = tmp;
}

void mainLoop(maps* map, windowSpec* wSpec, simSpec* sSpec)
{
    bool pause = 0;
    bool next= 0;
    int iter = 1;
    bool inf = 0;

    if (sSpec->simLength < 0)
    {
        inf = 1;
    }

    double lastUpdate = GetTime();

    while (!WindowShouldClose() && (iter <= sSpec->simLength || inf ))
    {
        draw(map, wSpec, pause, iter);

        if (IsKeyPressed(KEY_SPACE))
        {
            pause = !pause;
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            next = 1;
        }

        double currentTime = GetTime();
        double timePast = currentTime - lastUpdate;

        if (!pause && timePast >= sSpec->simSpeed || (next && pause))
        {
            applyRule(map);
            iter++;
            next = 0;
            lastUpdate = currentTime;
        }

        if (pause)
        {
            timePast = 0;
        }
    }
}

void deInitSim(maps* map, const simSpec* sSpec, const windowSpec* wSpec, const bool shouldWrite)
{
    if (shouldWrite)
    {
        writeFile(map, sSpec, wSpec);
    }

    for (int i = 0; i < map ->height; i++)
    {
        free(map->preMap[i]);
        free(map->curMap[i]);
    }

    free(map->preMap);
    free(map->curMap);
    deInitDisplay();
}