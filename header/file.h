#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "maps.h"
#include "simSpec.h"
#include "sim.h"
#include "statics.h"

void readFile(maps* map, simSpec* sSpec, windowSpec* wSpec);
void writeFile(const maps* map, const simSpec* spec, const windowSpec* wSpec);
