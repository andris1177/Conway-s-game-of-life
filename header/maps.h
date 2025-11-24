#pragma once

#include <stdbool.h>

/// @brief varibales for the map
typedef struct maps
{
    struct maps* pre;
    struct maps* next;
    bool **preMap;
    bool **curMap;
    int width;
    int height;
} maps;