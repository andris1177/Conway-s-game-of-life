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
    // row 1
    0,0,0,0,0,0,0,0,0,0,
    // row 2
    0,0,0,0,0,0,0,0,0,0,
    // row 3
    0,0,0,0,0,0,0,0,0,0,
    // row 4
    0,0,0,0,1,1,0,0,0,0,
    // row 5
    0,0,0,0,1,1,0,0,0,0,
    // row 6
    0,0,0,0,0,0,0,0,0,0,
    // row 7
    0,0,0,0,0,0,0,0,0,0,
    // row 8
    0,0,0,0,0,0,0,0,0,0,
    // row 9
    0,0,0,0,0,0,0,0,0,0
    };


    map.width = 10;
    map.width = 10;

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