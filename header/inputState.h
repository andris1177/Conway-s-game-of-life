#pragma once

#include <stdbool.h>

typedef struct
{
    bool pause;
    bool next;
    bool prev;
    bool zoomIn;
    bool zoomOut;
    bool recenter;
    bool panUp, panDown, panRight, panLeft;
} inputState;