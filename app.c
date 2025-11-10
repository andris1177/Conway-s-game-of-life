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

    spec.iFile = argv[1];

    if (argv[2] != 0)
    {
        shouldWrite = 1;
        spec.oFile = argv[2];
    }

    initSim(&map, &spec);

    int iter = 1;
    bool run = 0;

    if (spec.simLength < 0)
    {
        run = 1;
    }

    while ((!isWindowShouldClose() && iter <= spec.simLength) || (run && !isWindowShouldClose()))
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

        if (!pause || (next && pause))
        {
            applyRule(&map);
            
            // allow sleep to take less than a second but need different library and functioon in windows and unix
            if (spec.simSpeed > 0)
            {
                #ifdef _WIN32
                    sleep((DWORD)(spec.simSpeed * 1000.0));
                #else
                    usleep((useconds_t)(spec.simSpeed * 1e6));
                #endif
            }
            
            iter++;
            next = 0;
        }

    }
    
    deInitSim(&map, &spec, shouldWrite);
}