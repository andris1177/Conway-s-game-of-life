#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "settings.h"
#include "debugmalloc.h"

/// @brief Initializes the safe memory variables.
void initMem();
/// @brief Works just like malloc() from the outside, but it also stores the allocated memory in a sort of gc list and if the os can't give the requested size of memory, it frees all the allocated memory in th gc list and closes the program.  
void* safeMalloc(size_t size);
/// @brief Grows the internal memList block.
void grow();
/// @brief Shrinks the internal memMap block. 
void shrink();
/// @brief Works just like free() from the outside, but it also removes the pointer from the internal gc list and if it gets a pointer not in the gc list, it frees every other pointer in the list and closes the program.
void safeFree(void* ptr);
/// @brief Frees all the memory in the gc list, can't be called twice without first calling initMem() once again.
void freeAll();
/// @brief Prints out the amount of allocated and freed memory and prints out any remaining memory address. 
void memReport();