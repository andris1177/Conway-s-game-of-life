#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "window.h"
#include "file.h"
#include "maps.h"
#include "simSpec.h"
#include "settings.h"
#include "mem.h"

/// @brief Initializes the simulation by calling other functions to read the file, create a display, and calculate the max cell size on the window  
void initSim(maps* map, simSpec* simSpec, windowSpec* wSpec); 
/// @brief Receives a map struct pointer and creates a 2d block into the struct, allocates the block on the heap
void makeMap(maps* map);
/// @brief Receives a map pointer and creates a set length chained list that forms a loop so the last element points to the first, also the list can be accessed from both direction due to the next and prev pointers in the struct
maps* makeList();
/// @brief Receives a map pointer and applies the gol rules to all of the cells on the map, it uses the preMap as the input and applies the changes to the curMap and switches the two pointers after each cycle  
void applyRule(maps* map);
/// @brief Handles keyboard inputs and runs the simulation by applying the rules to the latest chained list element, and also handles backtracking
void mainLoop(maps* map, const simSpec* sSpec, windowSpec* wSpec);
/// @brief Saves the last state to file if an output filename is given, calls freeMem and closes the raylib window, can't be called if the raylib window hasn't been initialized, as it'll segfault the program 
void deInitSim(const maps* map, const simSpec* sSpec, const windowSpec* wSpec, const bool shouldWrite);