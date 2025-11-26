#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "maps.h"
#include "simSpec.h"
#include "sim.h"
#include "settings.h"

void readFile(maps* map, simSpec* sSpec, windowSpec* wSpec);
void writeFile(maps* map, const simSpec* spec, const windowSpec* wSpec);