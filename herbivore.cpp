#include "herbivore.h"

Herbivore::Herbivore(GrassLand *land, queue<Event *> *events, int cellId) : Animal(land, events, cellId) {}

void Herbivore::feed() {
    float grNeed = (1 - getEnergyLevel()) * needGrass();
    float grLevel = getCell()->getGrassLevel();
    float grEaten = grLevel > grNeed ? grNeed : grLevel;

    increaseEnergy(grEaten / needGrass());

    getCell()->reduceGrass(grEaten);
}
