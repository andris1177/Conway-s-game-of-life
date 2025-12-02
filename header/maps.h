#pragma once

#include <stdbool.h>

/// @brief The map struct makes up the chained memory list and stores the gol state. 
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