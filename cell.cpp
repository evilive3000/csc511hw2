#include "cell.h"

using namespace std;

int Cell::counter = 0;

Cell::Cell() : grassLevel(10.0), id(++counter) {}

void Cell::growGrass() {
    grassLevel = min(grassLevel * 1.001 + 0.4, 100.0);
}

void Cell::reduceGrass(float amount) {
    grassLevel = max(grassLevel - amount, 0.0f);
}

float Cell::getGrassLevel() {
    return grassLevel;
}