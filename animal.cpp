#include<iostream>
#include<string>
#include "animal.h"
#include "cell.h"

using namespace std;

int Animal::counter = 0;

Animal::Animal(int species, int cellId) : id(++counter), species(species), cellId(cellId) {}

// COPY CONSTRUCTOR
Animal::Animal(Animal &a) : id(++counter), species(a.species), cellId(a.cellId) {}

int Animal::selfProcess() {
    age++;
    reduceEnergy();

    // if not alive returns value greater then 0
    if (!isAlive()) {
        return 1;
    }

    move();
    feed();
    if (isPregnant())
        birth();

    cout << "update|animal|" << *this << endl;
}


void Animal::move() {
    int size = Animal::getGrassland()->size;
    int col = cellId % size;
    int row = cellId / size;

    // 0  1  2
    // 3  X  4
    // 5  6  7
    int dir = rand() % 8;

    if (dir == 2 || dir == 4 || dir == 7) col++;
    if (dir == 0 || dir == 3 || dir == 5) col--;
    if (dir == 0 || dir == 1 || dir == 2) row--;
    if (dir == 5 || dir == 6 || dir == 7) row++;

    row = (row + size) % size;
    col = (col + size) % size;

    // remove from current cell
//    getCell()->removeAnimal(this);
    // update cellId
    cellId = row * size + col;
    // add to new cell
//    getCell()->addAnimal(this);
}

bool Animal::isAlive() {
    bool enoughEnergy = getEnergyLevel() > 0;
    bool isYoung = age < lifeSpan();
    return enoughEnergy && isYoung;
}

bool Animal::isPregnant() {
    bool enoughEnergy = getEnergyLevel() > 0.5;
    bool isProlif = (age % prolif()) == 0;
    return isProlif && enoughEnergy;
}

float Animal::getEnergyLevel() {
    return energy;
}

std::ostream &operator<<(std::ostream &out, Animal &animal) {
    cout << animal.id << ";" << animal.age << ";" << animal.energy << ";" << animal.cellId << ";" << animal.species;
    return out;
}

void Animal::increaseEnergy(float delta) {
    energy = min(1.0f, energy + delta);
}

void Animal::reduceEnergy() {
    energy -= 0.1;
}

Cell *Animal::getCell() {
    return Animal::getGrassland()->getCell(cellId);
}