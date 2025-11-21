#pragma once

/// @brief basic settings for the smulation
typedef struct
{
    /// @brief the time in seconds for one iteration be visible 
    double simSpeed;
    /// @brief the amount of iteration the game should run
    int simLength;
    /// @brief input file name 
    const char* iFile;
    /// @brief output file name 
    const char* oFile;
} simSpec;
