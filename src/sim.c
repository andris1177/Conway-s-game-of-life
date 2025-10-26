#include "../header/sim.h"

void initSim(int sizeX, int sizeY)
{

}

maps makeMap(int size)
{
    bool *preMap = malloc(sizeof(bool) * size);
    bool *curMap = malloc(sizeof(bool) * size);

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