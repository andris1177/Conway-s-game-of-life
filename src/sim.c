#include "../header/sim.h"

void initSim(int sizeX, int sizeY)
{

}

void makeMap(maps map)
{
    bool map.preMap = malloc(sizeof(bool) * (map.width * map.heighth));
    bool map.curMap = malloc(sizeof(bool) * (map.width * map.heighth));

    return {preMap, curMap};
}

bool getMapByIndex(int index, bool* map);
{
    return *map[index];
}

void setMapByIndex(bool value, int index, bool* map)
{
    *map[index] = value;
}

void freeMap(maps map)
{
    free(map.preMap);
    free(map.preMap);
}