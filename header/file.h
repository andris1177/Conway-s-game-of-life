#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "maps.h"
#include "simSpec.h"
#include "sim.h"
#include "debugmalloc.h"

void readFile(maps* map, simSpec* spec);
void writeFile(maps* map, simSpec* spec);