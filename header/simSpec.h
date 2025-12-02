#pragma once

/// @brief Stores some basic sim data that doesn't really fit into the other structs. 
typedef struct
{
    double simSpeed;
    int simLength;
    const char* iFile;
    const char* oFile;
} simSpec;
