#pragma once

#include "maps.h"
#include "simSpec.h"
#include "windowSpec.h"
#include "inputState.h"
#include "loopSpecs.h"

typedef struct 
{
    maps* map;
    simSpec sSpec;
    windowSpec wSpec;
    inputState iState;
    loopSpecs lSpec;
} appContex;