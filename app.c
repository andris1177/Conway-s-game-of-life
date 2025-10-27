#include "header/sim.h"

#define windowWidth 1024
#define windowHeigth 768

int main()
{
    maps map;
    simSpec spec;

    bool temp[] = {
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

    memcpy(map.preMap, temp, sizeof(temp));
    memcpy(map.curMap, temp, sizeof(temp));

    map.width = 10;
    map.width = 10;

    initSim(windowWidth, windowHeigth, "../example.map", "../result.map", &map);

    while (isWindowShouldClose)
    {
        applyRule(&map, &spec);
        draw(&map);
    }
    
    deInitSim(&map);
}