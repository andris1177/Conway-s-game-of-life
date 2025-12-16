cmake_minimum_required(VERSION 3.12...4.0)
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

FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG 25c8c65 # v4.0
)

FetchContent_Declare(
    nfde
    GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git
    GIT_TAG 86d5f20 # v1.2.1
)

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(raygui)
FetchContent_MakeAvailable(nfde)

add_library(core STATIC src/file.c src/sim.c src/window.c src/mem.c)
target_include_directories(core PUBLIC header)
target_link_libraries(core PUBLIC raylib nfd)
target_include_directories(core PUBLIC  ${raygui_SOURCE_DIR}/src)

add_executable(gol app.c)
target_link_libraries(gol PUBLIC core)

add_executable(mapGen mapGen.c)
target_link_libraries(mapGen PUBLIC core)