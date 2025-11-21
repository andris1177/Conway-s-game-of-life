#include "header/sim.h"
#include "header/debugmalloc.h"

#include <unistd.h>

int main(int argc, char *argv[])
{
    maps map;
    simSpec sSpec = {0};
    windowSpec wSpec = {0};
    bool shouldWrite = false;

    if (argc >= 2 && argv[1] != NULL)
    {
        sSpec.iFile = argv[1];
    }

    else
    {
        printf("Input file is missing\n");
        return -1;
    }

    if (argc >= 3 && argv[2] != NULL)
    {
        shouldWrite = 1;
        sSpec.oFile = argv[2];
    }

    initSim(&map, &sSpec, &wSpec);
    mainLoop(&map, &wSpec, &sSpec);
    deInitSim(&map, &sSpec, &wSpec, shouldWrite);
    
    return 0;
}