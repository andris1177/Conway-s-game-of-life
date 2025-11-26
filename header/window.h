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

void initDisplay(const windowSpec* wSpec);
void getCellSize(windowSpec* wSpec, maps* map);
void draw(const maps* map, windowSpec* wSpec, const bool pause);
void deInitDisplay();