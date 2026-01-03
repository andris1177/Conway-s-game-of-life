#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "window.h"
#include "file.h"
#include "statics.h"
#include "mem.h"
#include "appContext.h"

typedef void (*initLoop)(simSpec* sSpec, loopSpecs* lSpec);
typedef maps* (*loopType)(appContex* app);
typedef bool (*shouldContinue)(const appContex* app);

// appCommon.c
void initSim(appContex* app); 
void makeMap(maps* map);
maps* makeList();
void keyInput(inputState* input);
void mainLoop(appContex* app, initLoop initL, loopType loopT, shouldContinue shouldC);
void deInitSim(const appContex* app, const bool shouldWrite);

// sim.c
void initSimLoop(simSpec* sSpec, loopSpecs* lSpec);
maps* simLoop(appContex* app);
bool shouldContinueSim(const appContex* app);
void applyRule(maps* map);

// editor.c
void initEditorLoop(simSpec* sSpec, loopSpecs* lSpec);
maps* editorLoop(appContex* app);
bool shouldContinoueEditor(const appContex* app);
