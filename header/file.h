#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "maps.h"
#include "simSpec.h"
#include "sim.h"
#include "settings.h"

/// @brief Reads the file into the given structs.
void readFile(maps* map, simSpec* sSpec, windowSpec* wSpec);
/// @brief Writes the data from the given structs into the output file.
void writeFile(const maps* map, const simSpec* spec, const windowSpec* wSpec);