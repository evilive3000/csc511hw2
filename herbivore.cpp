#include "herbivore.h"

Herbivore::Herbivore(int species, int cellId) : Animal(species, cellId) {}

void Herbivore::feed() {
    float grNeed = (1 - getEnergyLevel()) * needGrass();
    float grLevel = getCell()->getGrassLevel();
    float grEaten = grLevel > grNeed ? grNeed : grLevel;

    increaseEnergy(grEaten / needGrass());

    getCell()->reduceGrass(grEaten);
}
