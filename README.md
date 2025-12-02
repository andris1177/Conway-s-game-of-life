# Conway-s-game-of-life

## This is my project for the prog 1 uni class. This program should build on linux, macos and windows however, I only tested it on linux and windows. 

### To build it, you need cmake and a c compiler. If you don't have cmake and can't install it you can use the cmaketools from the visual studio extension store, it will use its own cmake binary. 

``` bash
mkdir build && cd build
cmake ../
cmake --build .
```

### If you are using windows and have gcc through mingw you need to build a bit differently.

``` bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

## To run the app you need to give it an input map and, optionally, an output map. If an output map is provided, the last state will be written to it. There are a couple of example maps in the repo you can try out or make your own version from it. Or use the mapGen utility to generate one of your own.

## How to use the app


``` bash
./gol ../example/example1.map output.map
```

### Once the app is running, you can pause and resume the simulation by pressing space and close the simulation by pressing esc. When the simulation is paused, you can step the simulation forward and backward with the left and right arrows and fast forward and rewind with the up and down arrows. You can zoom in and out by pressing the J and K letters or by using the mouse scroll wheel. There is a zoom indicator at the bottom right of the window. You can move the map around with W, A, S, and D, this is handy when you're zoomed in. If you want to reset the view to the default one, press F. 

## How to use the mapGen utility

### It also compiles with the main go app, so it should already be in your build folder.

``` bash
./mapGen [output file name] [map width in cell count] [map height in cell count] [1: for a fully populated map, 0: for an empty map, r: for a random map] [simulation length, -1 for an infinite simulation] [The time, each iteration will be displayed on the window in seconds] [the window width in pixels] [the window height in pixels] [window render fps]
```

### To-Do list 
- [x] Eanble indefinite runtime
- [x] Hotkey for play and pause
- [x] Add support for different aspect ratios
- [x] Improve gui elemt position
- [x] Support for non square starting map
- [ ] Don't regenerate nodes if the user backtracks and unpauses the simulation. 
- [ ] Add gui map editor
- [ ] Add a guii library (optional)
- [ ] Add pop up menu for on the spot animation/display changes (optional)

### Known bugs to fix
- [x] Non square maps doesn't fill the entire available space, see example4 for reference
- [x] Some points of the map doesn't get read correctly
- [x] makelist fails to set any data value for the last node, it causes a segfault at index 199 in mainLoop and another segfault at the freeMem function
- [ ] If makeMap() fails when it is called from mainLoop(), it won't properly close the raylib window, will need to rework error handling.