#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"

#include "maps.h"
#include "simSpec.h"

void initDisplay(int width, int heigth);
void draw(maps* m, int iter, int width, int heigth);
bool isWindowShouldClose();
void deInitDisplay();