#pragma once

#include <stdbool.h>

/// @brief varibales for the map
typedef struct maps
{
    bool **preMap;
    bool **curMap;
    int width;
    int height;
} maps;