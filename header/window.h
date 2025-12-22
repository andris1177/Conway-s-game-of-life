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

typedef void (*uiDrawFn)(const maps* map, windowSpec* wSpec);

void initDisplay(windowSpec* wSpec);
void getCellSize(const maps* map, windowSpec* wSpec, bool init);
void zoom(maps* map, windowSpec* wSpec, int amount);
void pivot(maps* map, windowSpec* wSpec, int amount, int direction);
void refit(maps* map, windowSpec* wSpec);
void drawMap(const maps* map, windowSpec* wSpec, uiDrawFn ui);
void drawSimUi(const maps* map, const windowSpec* wSpec);
void drawEditorUi(const maps* map, const windowSpec* wSpec);
void deInitDisplay();