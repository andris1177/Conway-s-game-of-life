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
        memReport();
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
                map->curMap[i][j] = false;
            }

            else if (countn == 3)
            {
                map->curMap[i][j] = true;
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

void keyInput(inputState* input)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        input->pause = !input->pause;
    }      

    if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_UP))
    {
        input->next = true;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_DOWN))
    {
        input->prev = true;
    }

    double mouse = GetMouseWheelMove();

    if (mouse > 0 || IsKeyPressed(KEY_J))
    {
        input->zoomIn = true;
    }

    else if (mouse < 0 || IsKeyPressed(KEY_K))
    {
        input->zoomOut = true;
    }

    if (IsKeyPressed(KEY_F))
    {
        input->recenter = true;
    }

    if (IsKeyDown(KEY_W))
    {
        input->panUp = true;
    }

    if (IsKeyDown(KEY_S))
    {
        input->panDown = true;
    }

    if (IsKeyDown(KEY_A))
    {
        input->panLeft = true;
    }

    if (IsKeyDown(KEY_D))
    {
        input->panRight = true;
    }
}

void initSimLoop(simSpec* sSpec, loopSpecs* lSpec)
{
    lSpec->inf = false;
    lSpec->lastUpdate = GetTime();

    if (sSpec->simLength < 0)
    {
        lSpec->inf = true;
    }
}

void simLoop(maps* map, simSpec* sSpec, windowSpec* wSpec, loopSpecs* lSpec, inputState* input)
{
    double currentTime = GetTime();
    double timePast = currentTime - lSpec->lastUpdate;

    if (input->pause && input->next)
    {
        if (map->next->index > map->index)
        {
            // ie there is a new node after the current one, so the user backtracked, 
            //no neede to generate the values once again so only switching to the next chain is enough
            map = map->next;
            input->next = false;
        }
    }

    if (map->pre->preMap != NULL && map->pre->curMap != NULL && input->prev && input->pause)
    {
        map = map->pre;
        input->prev = false;
    }

    // TODO: also check if the user backtracked and don't regenerate nodes when the simulation is resumed. 
    if ((timePast >= sSpec->simSpeed && !input->pause) || (input->next && input->pause))
    {
        lSpec->lastUpdate = GetTime();

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
        input->next = false;
        map->index++;
    }

}

bool shouldContinueSim(maps* map, simSpec* sSpec, loopSpecs* lSpec)
{
    return (map->index <= sSpec->simLength || lSpec->inf);
}

void mainLoop(maps* map, const simSpec* sSpec, windowSpec* wSpec, inputState* input, loopSpecs* lSpec, initLoop initL, loopType loopT, shouldContinue shouldC)
{
    map->index = 1;
    initL(sSpec, lSpec);

    while (!WindowShouldClose() && shouldC(map, sSpec, lSpec))
    {
        drawMap(map, wSpec, drawSimUi);
        keyInput(input);

        loopT(map, sSpec, wSpec, lSpec, input);
        
        if (input->zoomIn)
        {
            zoom(map, wSpec, ZOOM_STEP);
            input->zoomIn = false;
        }

        else if (input->zoomOut)
        {
            zoom(map, wSpec, -1 * ZOOM_STEP);
            input->zoomOut = false;
        }


        if (input->recenter)
        {
            refit(map, wSpec);
            input->recenter = false;
        }

        if (input->panUp)
        {
            pivot(map, wSpec, MOVE_STEP, 2);
            input->panUp = false;
        }

        if (input->panDown)
        {
            pivot(map, wSpec, -1 * MOVE_STEP, 2);
            input->panDown = false;
        }

        if (input->panLeft)
        {
            pivot(map, wSpec, MOVE_STEP, 1);
            input->panLeft = false;
        }

        if (input->panRight)
        {
            pivot(map, wSpec, -1 * MOVE_STEP, 1);
            input->panRight = false;
        }
    }
}

void deInitSim(const maps* map, const simSpec* sSpec, const windowSpec* wSpec, const bool shouldWrite)
{
    if (shouldWrite)
    {
        writeFile(map, sSpec, wSpec);
    }

    if (IsWindowReady())
    {
        deInitDisplay();
    }

    freeAll();
    memReport();
}