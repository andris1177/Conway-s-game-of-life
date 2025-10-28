#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"

#include "maps.h"

void initDisplay(int width, int heigth);
void draw(maps* m, int iter);
bool isWindowShouldClose();
void deInitDisplay();