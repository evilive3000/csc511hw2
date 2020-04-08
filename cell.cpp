#include "cell.h"

using namespace std;

int Cell::counter = 0;

Cell::Cell() : grassLevel(1.0), animalSet(new set<Animal *>()), id(++counter) {}

void Cell::growGrass() {
    grassLevel = min(grassLevel + 0.075, 100.0);
}

void Cell::reduceGrass(float amount) {
    grassLevel = max(grassLevel - amount, 0.0f);
}

float Cell::getGrassLevel() {
    return grassLevel;
}

set<Animal *> *Cell::getAnimalSet() {
    return animalSet;
}

int Cell::getId() {
    return id;
}