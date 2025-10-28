#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "window.h"
#include "file.h"
#include "maps.h"
#include "simSpec.h"


void initSim(int wWidth, int wHeigth, maps* m, simSpec spec);
void makeMap(maps* m);
void applyRule(maps* m, simSpec* spec);
void deInitSim(maps* m);