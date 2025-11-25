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

maps* makeList()
{
    int memoryLength = 200;

    maps* list = (maps *)malloc(sizeof(maps));
    maps* first = list;

    for (int i = 1; i < memoryLength; i++)
    {
        list->preMap = NULL;
        list->curMap = NULL;
        list->height = -1;
        list->width = -1;
        list->index = -1;
        list->next = (maps *)malloc(sizeof(maps));
        list->next->pre = list;
        list = list->next;
    }

    list->next = first;
    first->pre = list;

    return first;
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

void mainLoop(maps* map, simSpec* sSpec, windowSpec* wSpec)
{
    bool preButoon = false;
    bool nextButton = false;
    bool pause = false;
    bool inf = false;
    double lastUpdate = GetTime();

    map->index = 1;

    if (sSpec->simLength < 0)
    {
        inf = true;
    }

    while (!WindowShouldClose() && (map->index <= sSpec->simLength || inf))
    {
        draw(map, wSpec, pause);

        if (IsKeyPressed(KEY_SPACE))
        {
            pause = !pause;
        }      

        if (IsKeyPressed(KEY_RIGHT))
        {
            nextButton = true;
        }

        if (IsKeyPressed(KEY_LEFT))
        {
            preButoon = true;
        }

        double currentTime = GetTime();
        double timePast = currentTime - lastUpdate;

        if ((timePast >= sSpec->simSpeed && !pause) || (nextButton && pause))
        {
            lastUpdate = GetTime();

            map->next->height = map->height;
            map->next->width = map->width;
            map->next->index = map->index;

            if (map->next->preMap == NULL || map->next->curMap == NULL)
            {
                makeMap(map->next);
            }

            for (int i = 0; i < map->height; i++)
            {
                for (int j = 0; j < map->width; j++)
                {
                    map->next->preMap[i][j] = map->preMap[i][j];
                    map->next->curMap[i][j] = map->curMap[i][j];
                }
            }

            map = map->next;

            applyRule(map);
            nextButton = false;
            map->index++;
        }

        if (map->pre->preMap != NULL && map->pre->curMap != NULL && preButoon && pause)
        {
            map = map->pre;
            preButoon = false;
        }
    }
}

void freeMem(maps* map)
{
    while (map != NULL)
    {
        if (map->preMap != NULL && map->curMap != NULL)
        {
            for (int i = 0; i < map ->height; i++)
            {
                free(map->preMap[i]);
                free(map->curMap[i]);
            }

            free(map->preMap);
            free(map->curMap);
        }


        maps * tmp = map->next;
        free(map);
        map = tmp;

        printf("runnung\n");
    }
}

void deInitSim(maps* map, const simSpec* sSpec, const windowSpec* wSpec, const bool shouldWrite)
{
    if (shouldWrite)
    {
        writeFile(map, sSpec, wSpec);
    }

    map->pre->next = NULL;
    freeMem(map);

    deInitDisplay();
}