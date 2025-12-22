#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "settings.h"
#include "debugmalloc.h"

void initMem();
void* safeMalloc(size_t size);
void grow();
void shrink();
void safeFree(void* ptr);
void freeAll();
void memReport();