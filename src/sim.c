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
    drawMap(app->map, app->wSpec, drawSimUi);

    double currentTime = GetTime();
    double timePast = currentTime - app->lSpec->lastUpdate;

    if (app->iState->pause && input->next)
    {
        if (app->map->next->index > app->map->index)
        {
            // ie there is a new node after the current one, so the user backtracked, 
            //no neede to generate the values once again so only switching to the next chain is enough
            app->map = map->next;
            app->iState->next = false;
        }
    }

    if (app->map->pre->preMap != NULL && app->map->pre->curMap != NULL && app->iState->prev && app->iState->pause)
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

    return map;
}

bool shouldContinueSim(const appContex* app)
{
    return (map->index <= sSpec->simLength || lSpec->inf);
}