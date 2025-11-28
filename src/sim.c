#include "../header/sim.h"

void initSim(maps* map, simSpec* simSpec, windowSpec* wSpec)
{
    readFile(map, simSpec, wSpec);
    initDisplay(map, wSpec);
}

void makeMap(maps* map)
{
    if (map->width == 0 && map->height == 0)
    {
        fprintf(stderr, "Map with 0 area is provided. exiting...\n");
        freeAll();
        exit(ERROR_INPUT);
    }

    map->curMap = safeMalloc(sizeof(bool*) * (size_t)map->height);
    map->preMap = safeMalloc(sizeof(bool*) * (size_t)map->height);

    for (int i = 0; i < map->height; i++)
    {
        map->curMap[i] = safeMalloc(sizeof(bool) * (size_t)map->width);
        map->preMap[i] = safeMalloc(sizeof(bool) * (size_t)map->width);
    }
}

maps* makeList()
{
    maps* first = NULL;
    maps* list = NULL;

    for (int i = 0; i < MEMORY_LENGTH; i++)
    {
        maps* node = safeMalloc(sizeof(maps));
        node->preMap = NULL;
        node->curMap = NULL;
        node->height = -1;
        node->width = -1;
        node->index = -1;

        if (first == NULL)
        {
            list = node;
            first = list;
        }
        
        else
        {
            list->next = node;
            list->next->pre = list;
            list = list->next;
        }
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

void mainLoop(maps* map, const simSpec* sSpec, windowSpec* wSpec)
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

        if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_UP))
        {
            nextButton = true;
        }

        if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_DOWN))
        {
            preButoon = true;
        }

        double currentTime = GetTime();
        double timePast = currentTime - lastUpdate;

        if (pause && nextButton)
        {
            if (map->next->index > map->index)
            {
                // ie there is a new node after the current one, so the user backtracked, 
                //no neede to generate the values once again so only switching to the next chain is enough
                map = map->next;
                nextButton = false;
            }
        }

        if (map->pre->preMap != NULL && map->pre->curMap != NULL && preButoon && pause)
        {
            map = map->pre;
            preButoon = false;
        }

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
    }
}

void deInitSim(const maps* map, const simSpec* sSpec, const windowSpec* wSpec, const bool shouldWrite)
{
    if (shouldWrite)
    {
        writeFile(map, sSpec, wSpec);
    }

    if (wSpec->isRaylibInit)
    {
        deInitDisplay();
    }

    freeAll();
    memReport();
}