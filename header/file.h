#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "maps.h"
#include "simSpec.h"
#include "sim.h"

/// @brief reads the input file into the given structs
void readFile(maps* map, simSpec* sSpec, windowSpec* wSpec);
/// @brief writes the given structs into the output file 
void writeFile(const maps* map, const simSpec* spec, const windowSpec* wSpec);