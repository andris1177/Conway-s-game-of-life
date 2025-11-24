#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "window.h"
#include "file.h"
#include "maps.h"
#include "simSpec.h"
#include "debugmalloc.h"

/// @brief initializes the simulation
void initSim(maps* map, simSpec* simSpec, windowSpec* wSpec);
/// @brief request the 2d blocks from the os on the heap 
void makeMap(maps* map);
/// @brief applies the game rules on the map 
void applyRule(maps* map);
/// @brief free all unused pointers and closes the window
void deInitSim(maps* map, const simSpec* sSpec, const windowSpec* wSpec, const bool shouldWrite);
void mainLoop(maps* map, simSpec* sSpec, windowSpec* wSpec);