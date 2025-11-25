#include "header/sim.h"

int main(int argc, char *argv[])
{
    maps* map = makeList();
    simSpec sSpec = {0};
    windowSpec wSpec = {0};
    bool shouldWrite = false;
    sSpec.iFile = "../examples/example1.map";

    if (argc >= 2 && argv[1] != NULL)
    {
        sSpec.iFile = argv[1];
    }

    else
    {
        //printf("Input file is missing\n");
        //return -1;
    }

    if (argc >= 3 && argv[2] != NULL)
    {
        shouldWrite = 1;
        sSpec.oFile = argv[2];
    }

    initSim(map, &sSpec, &wSpec);
    mainLoop(map, &sSpec, &wSpec);
    deInitSim(map, &sSpec, &wSpec, shouldWrite);
    
    return 0;
}