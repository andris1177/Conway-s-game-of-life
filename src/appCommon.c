#include "../header/sim.h"

void initSim(appContex* app)
{
    readFile(app->map, &app->simSpec, &app->wSpec);
    initDisplay(app->map, &app->wSpec);
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

void mainLoop(appContex* app, initLoop initL, loopType loopT, shouldContinue shouldC)
{
    app->map->index = 1;
    initL(&app->sSpec, &app->lSpec);

    while (!WindowShouldClose() && shouldC(app->map, &app->sSpec, &app->lSpec))
    {
        keyInput(&app->iState);

        app->map = loopT(app);
        
        if (&app->iState->zoomIn)
        {
            zoom(app->map, &app->wSpec, ZOOM_STEP);
            app->zoomIn = false;
        }

        else if (&app->iState->zoomOut)
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

void deInitSim(const appContex* app, const bool shouldWrite)
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