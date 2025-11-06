# Conway-s-game-of-life

## This is my project for prog 1 uni class. This project should build on linux macos and windows however I only tested it on linux.

### To build it you need cmake 

``` bash
mkdir build && cd build
cmake --build .
```

## To run the app you need to supply an input map and optionally and output map, if an output map is supplied the last state will be written to it. There is an example map in the repo. 

``` bash
./gol ../example.map output.map
```