cmake_minimum_required(VERSION 3.16...4.0)
project(conways-game-of-life 
        VERSION 1.8
        DESCRIPTION "The famous 0 player game implemented in c for a uni prog assigement" 
        LANGUAGES C)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG c1ab645 # v5.5
)

FetchContent_MakeAvailable(raylib)

add_library(core STATIC src/file.c src/sim.c src/window.c)
target_include_directories(core PUBLIC header)
target_link_libraries(core PUBLIC raylib)

# for debug 
target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
target_compile_options(core PRIVATE $<$<CONFIG:Debug>:-O0 -g -fsanitize=address,undefined>)
target_link_options(core PRIVATE $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

add_executable(gol app.c)
target_link_libraries(gol PUBLIC core)