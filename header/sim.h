#pragma once

#include <stdbool.h>

#include "window.h"
#include "fie.h"

typedef struct
{
    bool *preMap;
    bool *curMap;
    int width;
    int heighth;
    int simCount;
    int simSpeed;
} maps;


void initSim(int sizeX, int sizeY);
maps makeMap(int size);
void freeMap(maps map);
bool getMapByIndex(int index, bool* map);
void setMapByIndex(bool value, int index, bool* map);