#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"

#ifdef _WIN32
    #include <window.h>
#else
    #include <unistd.h>
#endif

#include "maps.h"
#include "simSpec.h"

void initDisplay(int width, int heigth);
void draw(maps* m, int iter, int width, int heigth, bool pause);
bool isWindowShouldClose();
void deInitDisplay();