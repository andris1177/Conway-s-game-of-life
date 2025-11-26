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

## To run the app you need to give it an input map and optionally an output map, if an output map is provided the last state will be written to it. There is a couple of example maps in the repo you can try out or make your own version from it. Right now you have to edit the text file manually with the basic parameters and map layout but I plan to make a gui editor to make it easier to create maps. You can also pause the simulation by pressing space.

## About that file

### It's a simple file where you can set all the available settings. 

#### width and height is self explanatory you have to set your map dimesions here. 

#### simCount is the value that sets how many times the rules should be applied and the result be showen on the window, if you set it below 0 it'll going to run until you close the window by pressing esc or using your os specific way. 

#### simShowTime this sets how many seconds should one iteration be on the window, it is a double so you can set it to less than one second. 0 or a negative value means no speedcap, in this case only the rendering speed will limit it which is limited to 60fps.


``` bash
./gol ../example/example1.map output.map
```

### To-Do list 
- [x] Eanble indefinite runtime
- [x] Hotkey for play and pause
- [x] Add support for different aspect ratios
- [x] Improve gui elemt position
- [x] Support for non square starting map
- [ ] Add gui map editor
- [ ] Add a guii library (optional)
- [ ] Add pop up menu for on the spot animation/display changes (optional)

### Known bugs to fix
- [x] Non square maps doesn't fill the entire available space, see example4 for reference
- [x] Some points of the map doesn't get read correctly
- [x] makelist fails to set any data value for the last node, it causes a segfault at index 199 in mainLoop and another segfault at the freeMem function