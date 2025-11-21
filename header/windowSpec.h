#pragma once

/// @brief window related variables 
typedef struct 
{
    /// @brief the whole window resolution in x direction in pixel
    int windowWidth;
    /// @brief the whole window resolution in y direction in pixel
    int windowHeight;
    /// @brief The number of times a frame will be rendered in one second in fps
    int fps;
    /// @brief the size of one cell in pixel 
    int size;
    /// @brief the gap between each cell in pixel
    int gap;
    /// @brief the padding for the stats  at the top of the window in pixel
    int stats;
    /// @brief the usable width of the window
    int avlWidth;
    /// @brief the usable height of the window
    int avlHeight;
    /// @brief the width of the part where the map will be drawn in pixel
    int displayMapSizeX;
    /// @brief the height of the part where the map will be drawn in pixel 
    int displayMapSizeY;
} windowSpec;
