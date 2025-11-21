#pragma once

#include <stdbool.h>

typedef struct
{
    bool **preMap;
    bool **curMap;
    int width;
    int height;
} maps;