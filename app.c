#include "header/sim.h"

#define windowWidth 1024
#define windowHeigth 768

int main()
{
    maps map;
    simSpec spec;

    bool temp[100] = {
    0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,0,0,0,0,
    0,1,0,1,0,0,0,1,1,0,
    0,0,1,1,0,0,0,1,0,0,
    0,0,0,0,1,1,0,0,0,0,
    0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,0,0,1,1,0,0,
    0,0,0,1,0,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0
    };

    map.width = 10;
    map.width = 10;

    initSim(windowWidth, windowHeigth, "../example.map", "../result.map", &map);

    memcpy(map.preMap, temp, 100 * sizeof(bool));
    memcpy(map.curMap, temp, 100 * sizeof(bool));

    while (!isWindowShouldClose)
    {
        applyRule(&map, &spec);
        draw(&map);
    }
    
    deInitSim(&map);
}