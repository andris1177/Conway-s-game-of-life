#include "header/sim.h"
#include <unistd.h>

#define windowWidth 700
#define windowHeigth 700

int main(int argc, char *argv[])
{
    maps map;
    simSpec spec;

    spec.iFile = argv[1];
    spec.oFile = argv[2];

    initSim(windowWidth, windowHeigth, &map, &spec);

    int iter = 1;
    while (!isWindowShouldClose() && iter <= spec.simLength)
    {
        applyRule(&map);
        draw(&map, iter, windowWidth, windowHeigth);
        sleep(spec.simSpeed);
        iter++;
    }
    
    deInitSim(&map, &spec);
}