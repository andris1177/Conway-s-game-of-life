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

/// @brief Creates the raylib window and sets the target fps.
void initDisplay(maps* map, windowSpec* wSpec);
/// @brief Calculates the max cell size that can fit into the window based on the map aspect ratio and the window resolution.
void getCellSize(const maps* map, windowSpec* wSpec, bool init);
/// @brief Increases the cell size and calls for recalculating other window related values.
void zoom(maps* map, windowSpec* wSpec, int amount);
/// @brief Shifts the entire map around.
/// @param direction If set to one, it moves the map in the x direction. If set to two moves the mpa in the y direction.
void pivot(maps* map, windowSpec* wSpec, int amount, int direction);
/// @brief Resets the map position and size to default.
void refit(maps* map, windowSpec* wSpec);
void drawMap(const maps* map, windowSpec* wSpec, uiDrawFn ui);
/// @brief Draws the map onto the window.
void drawSimUi(const maps* map, windowSpec* wSpec);
/// @brief Calls raylib CloseWindow function.
void deInitDisplay();