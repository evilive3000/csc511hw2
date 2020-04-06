#ifndef GRASSLAND_T
#define GRASSLAND_T

#include<iostream>
#include "cell.h"

using namespace std;

struct GrassLand {
    int size;
    Cell *g;

    GrassLand(int size) : size(size), g(new Cell[size * size]) {}

    Cell *getCell(int id) {
        return &g[id];
    }

    Cell *randomCell() {
        return getCell(rand() % (size * size));
    }
};

#endif