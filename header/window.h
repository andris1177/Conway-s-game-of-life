#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"

#include "maps.h"
#include "simSpec.h"
#include "windowSpec.h"

/// @brief creates the window and sets basic settings
void initDisplay(const windowSpec* wSpec);
/// @brief calculate the cell size and the size where the map can be drawn 
void getCellSize(windowSpec* wSpec, const maps* map);
/// @brief draws each cell onto the window 
void draw(const maps* map, windowSpec* wSpec, const bool pause, const int iter);
/// @brief closes the window 
void deInitDisplay();