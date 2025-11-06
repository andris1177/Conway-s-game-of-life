# Conway-s-game-of-life

## This is my project for the prog 1 uni class. This program should build on linux macos and windows however I only tested it on linux.

### To build it you need cmake and a c compiler

``` bash
mkdir build && cd build
cmake ../
cmake --build .
```

### If you are using windows and have gcc through mingw you need to build a bit differently

``` bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

## To run the app you need to give an input map and optionally an output map, if an output map is provided the last state will be written to it. There is an example map in the repo you can try out or make your own version from it. Right now you have to edit the text file manually with the basic parameters and map layout but I plan to make a gui editor to make it easier to create maps. If  the simCount is less than 0 the program will run until you close the program by pressing esc or using yout os to close it.

``` bash
./gol ../example.map output.map
```

### core 
- [x] Eanble indefinite runtime
- [ ] Add gui map editor
- [ ] Improve gui elemt position
- [ ] Support for recangle starting map
- [ ] Add support for different aspect ratios
- [ ] Hotkey for play and pause
- [ ] Add a guii library (optional)
- [ ] Add pop up menu for on the spot animation/display changes (optional)