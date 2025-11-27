#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#include "maps.h"
#include "simSpec.h"
#include "windowSpec.h"
#include "sim.h"
#include "settings.h"

/// @brief Creates the raylib window and sets the target fps
void initDisplay(const windowSpec* wSpec);
/// @brief Calculates the max cell size that can fit into the window based on the map aspect ratio and the window resolution 
void getCellSize(windowSpec* wSpec, maps* map);
/// @brief Craws the map on to the window  
void draw(const maps* map, windowSpec* wSpec, const bool pause);
/// @brief Calls raylib CloseWindow function
void deInitDisplay();