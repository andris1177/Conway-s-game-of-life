#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "raygui.h"

#include "maps.h"
#include "simSpec.h"
#include "windowSpec.h"
#include "sim.h"
#include "statics.h"
#include "uiColors.h"
#include "appContext.h"

typedef void (*uiDrawFn)(const maps* map, const windowSpec* wSpec);

void initDisplay(const windowSpec* wSpec);
void initMapDraw(const maps* map, windowSpec* wSpec); 
void getCellSize(const maps* map, windowSpec* wSpec, const bool init);
void zoom(const maps* map, windowSpec* wSpec, const int amount);
void pivot(const maps* map, windowSpec* wSpec, const int amount, const int direction);
void refit(const maps* map, windowSpec* wSpec);
void drawMap(appContex* app, uiDrawFn ui);
void drawSimUi(const maps* map, const windowSpec* wSpec);
void drawEditorUi(const maps* map, const windowSpec* wSpec);
void drawMainMenu(const windowSpec* wSpec, appMode* aMode, bool* preMode);
void drawEditorMenu(const windowSpec* wSpec, appMode* aMode, bool* preMode);
void deInitDisplay();