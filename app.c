#include "header/sim.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    (void)argc; // to tell the compiler that argc is unused
    maps map;
    simSpec spec;

    bool pause = 0;
    bool next= 0;
    bool shouldWrite = 0;
    int iter = 1;
    bool inf = 0;

    spec.iFile = argv[1];

    initSim(&map, &spec);

    if (argv[2] != 0)
    {
        shouldWrite = 1;
        spec.oFile = argv[2];
    }

    if (spec.simLength < 0)
    {
        inf = 1;
    }

    double lastUpdate = GetTime();

    while (!isWindowShouldClose() && (iter <= spec.simLength || inf ))
    {
        draw(&map, iter, spec.windowWidth, spec.windowHeight, pause);

        if (IsKeyPressed(KEY_SPACE))
        {
            pause = !pause;
        }

        if (IsKeyPressed(KEY_RIGHT))
        {
            next = 1;
        }

        double currentTime = GetTime();
        double timePast = currentTime - lastUpdate;

        if (!pause && timePast >= spec.simSpeed || (next && pause))
        {
            applyRule(&map);
            iter++;
            next = 0;
            lastUpdate = currentTime;
        }

        if (pause)
        {
            timePast = 0;
        }
    }
    
    deInitSim(&map, &spec, shouldWrite);
}