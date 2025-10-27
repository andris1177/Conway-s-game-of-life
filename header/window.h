#pragma once

#include <stdbool.h>
#include "raylib.h"

#include "maps.h"

void initDisplay(int width, int heigth);
void draw(maps* m);
bool isWindowShouldClose();
void deInitDisplay();