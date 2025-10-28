#include "header/sim.h"
#include <unistd.h>

#define windowWidth 1024
#define windowHeigth 768

int main()
{
    maps map;
    simSpec spec;

    bool temp[100] = {
    // row 0
    0,0,0,0,0,0,0,0,0,0,
    // row 1 (glider)
    0,1,0,0,0,0,0,0,0,0,
    // row 2
    0,0,1,0,0,0,0,0,0,0,
    // row 3
    1,1,1,0,0,0,0,0,0,0,
    // row 4 (isolated cells)
    0,0,0,0,1,0,0,0,0,0,
    // row 5 (block still life)
    0,0,0,0,1,1,0,0,0,0,
    // row 6
    0,0,0,0,1,1,0,0,0,0,
    // row 7 (blinker)
    0,0,0,0,0,0,0,1,1,1,
    // row 8
    0,0,0,0,0,0,0,0,0,0,
    // row 9
    0,0,0,0,0,0,0,0,0,0
    };

    map.width = 10;
    map.heighth = 10;

    initSim(windowWidth, windowHeigth, "../example.map", "../result.map", &map);

    memcpy(map.preMap, temp, 100 * sizeof(bool));
    memcpy(map.curMap, temp, 100 * sizeof(bool));

    int iter = 1;
    while (!isWindowShouldClose())
    {
        draw(&map, iter);
        applyRule(&map, &spec);
        sleep(1);
        iter++;
    }
    
    deInitSim(&map);
}