#pragma once

#include <stdbool.h>

typedef struct maps
{
    struct maps* pre;
    struct maps* next;
    bool **preMap;
    bool **curMap;
    int width;
    int height;
    int index;
} maps;