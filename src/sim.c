#include "../header/sim.h"

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

void initSimLoop(simSpec* sSpec, loopSpecs* lSpec)
{
    lSpec->inf = false;
    lSpec->lastUpdate = GetTime();

    if (sSpec->simLength < 0)
    {
        lSpec->inf = true;
    }
}

maps* simLoop(appContex* app)
{
    drawMap(app, drawSimUi);

    double currentTime = GetTime();
    double timePast = currentTime - app->lSpec.lastUpdate;

    if (app->iState.pause && app->iState.next)
    {
        if (app->map->next->index > app->map->index)
        {
            app->map = app->map->next;
            app->iState.next = false;
        }
    }

    if (app->map->pre->preMap != NULL && app->map->pre->curMap != NULL && app->iState.prev && app->iState.pause)
    {
        app->map = app->map->pre;
        app->iState.prev = false;
    }

    // TODO: also check if the user backtracked and don't regenerate nodes when the simulation is resumed. 
    if ((timePast >= app->sSpec.simSpeed && !app->iState.pause) || (app->iState.next && app->iState.pause))
    {
        app->lSpec.lastUpdate = GetTime();

        app->map->next->height = app->map->height;
        app->map->next->width = app->map->width;
        app->map->next->index = app->map->index;

        if (app->map->next->preMap == NULL || app->map->next->curMap == NULL)
        {
            makeMap(app->map->next);
        }

        for (int i = 0; i < app->map->height; i++)
        {
            for (int j = 0; j < app->map->width; j++)
            {
                app->map->next->preMap[i][j] = app->map->preMap[i][j];
                app->map->next->curMap[i][j] = app->map->curMap[i][j];
            }
        }

        app->map = app->map->next;

        applyRule(app->map);
        app->iState.next = false;
        app->map->index++;
    }

    return app->map;
}

bool shouldContinueSim(const appContex* app)
{
    return (app->map->index <= app->sSpec.simLength || app->lSpec.inf);
}