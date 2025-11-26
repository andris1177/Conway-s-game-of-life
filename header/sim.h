#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "window.h"
#include "file.h"
#include "maps.h"
#include "simSpec.h"
#include "settings.h"
#include "debugmalloc.h"

void initSim(maps* map, simSpec* simSpec, windowSpec* wSpec); 
void makeMap(maps* map);
maps* makeList();
void applyRule(maps* map);
void mainLoop(maps* map, simSpec* sSpec, windowSpec* wSpec);
void freeMem(maps* map);
void deInitSim(maps* map, const simSpec* sSpec, const windowSpec* wSpec, const bool shouldWrite);