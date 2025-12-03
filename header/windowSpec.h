#pragma once

#include <stdbool.h>

/// @brief All of the data related to the window that needs to be shared between functions. 
typedef struct 
{
    int windowWidth;
    int windowHeight;
    int fps;
    int size;
    int originalSize;
    int avlWidth;
    int avlHeight;
    int displayMapSizeX;
    int displayMapSizeY;
    int startX;
    int startY;
    int moveX;
    int moveY;
} windowSpec;
