# Conway-s-game-of-life

## This is my project for the prog 1 uni class. This program should build on linux macos and windows however I only tested it on linux.

### To build it you need cmake and a c compiler

``` bash
mkdir build && cd build
cmake ../
cmake --build .
```

## To run the app you need to give an input map and optionally an output map, if an output map is provided the last state will be written to it. There is an example map in the repo you can try out or make your own version from it. Right now you have to edit the text file manually with the basic parameters and map layout but I plan to make a gui editor to make it easier to create maps. 

``` bash
./gol ../example.map output.map
```