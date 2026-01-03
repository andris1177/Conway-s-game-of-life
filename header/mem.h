#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#include "settings.h"
#include "debugmalloc.h"
#include "window.h"

void initMem();
void* safeMalloc(size_t size);
void grow();
void shrink();
void safeFree(void* ptr);
void freeAll();
void safeExit(const char* message, const int errorCode, const bool isError);
void memReport();
