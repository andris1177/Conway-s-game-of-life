cmake_minimum_required(VERSION 3.16)
project(game-of-life LANGUAGES C)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG c1ab645 # v5.5
)