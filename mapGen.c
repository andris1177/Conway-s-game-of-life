#include <time.h>
#include <string.h>

#include "header/sim.h"

int main(int argc, char *argv[])
{
    initMem();
    maps* map = safeMalloc(sizeof(maps));
    simSpec* sSpec = safeMalloc(sizeof(simSpec));
    windowSpec* wSpec = safeMalloc(sizeof(windowSpec));
    bool out = false;
    bool gen = true;
    
    if (argc >= 10)
    {
        sSpec->oFile = argv[1];
        map->width = (int)strtol(argv[2], NULL, 10);
        map->height = (int)strtol(argv[3], NULL, 10);

        if (!strcmp(argv[4], "0"))
        {
            out = false;
        }

        else if (!strcmp(argv[4], "1"))
        {
            out = true;
        }

        else if (!strcmp(argv[4], "r"))
        {
            gen = false;
        }

        sSpec->simLength = (int)strtol(argv[5], NULL, 10);
        sSpec->simSpeed = strtod(argv[6], NULL);

        wSpec->windowWidth = (int)strtol(argv[7], NULL, 10);
        wSpec->windowHeight = (int)strtol(argv[8], NULL, 10);
        wSpec->fps = (int)strtol(argv[9], NULL, 10);
    }

    else
    {
        fprintf(stderr, "Not enough arguments, provide a filename, map width, height and the mode as a console line argument. exiting...\n");
        freeAll();
        memReport();
        exit(ERROR_INPUT);
    }

    makeMap(map);

    // seed for random value 
    srand((unsigned)time(NULL));

    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if (!gen)
            {
                out = (rand() % 2) == 1;
            }

            map->preMap[i][j] = out;
            map->curMap[i][j] = out;
        }
    }

    writeFile(map, sSpec, wSpec);

    freeAll();
    memReport();
}