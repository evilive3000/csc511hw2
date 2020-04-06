#include<iostream>
#include<string>
#include "animal.h"
#include "cell.h"

using namespace std;

int Animal::counter = 0;

Animal::Animal(GrassLand *land, queue<Event *> *events, int cellId)
        : Event(land, events), id(++counter), cellId(cellId) {
    getCell()->getAnimalSet()->insert(this);
    events->push(this);
    printState("create");
}

// COPY CONSTRUCTOR
Animal::Animal(Animal &a) : Event(a), cellId(a.cellId), id(++counter) {
    getCell()->getAnimalSet()->insert(this);
    a.events->push(this);
    printState("create");
}

Animal::~Animal() {
    printState("delete");
}

void Animal::selfProcess() {
    events->pop();
    age++;
    reduceEnergy();

    if (isAlive()) {
        move();
        feed();
        if (isPregnant()) birth();
        events->push(this);
        printState("update");
    } else {
        getCell()->getAnimalSet()->erase(this);
        delete this;
    }
}

void Animal::move() {
    int size = land->size;
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
    getCell()->getAnimalSet()->erase(this);
    // update cellId
    cellId = row * size + col;
    // add to new cell
    getCell()->getAnimalSet()->insert(this);
}

void Animal::printState(string state) {
    cout << state << "|animal|" << *this << endl;
}

bool Animal::isAlive() {
    bool enoughEnergy = getEnergyLevel() > 0;
    bool isYoung = age < lifeSpan();
    return enoughEnergy && isYoung;
}

bool Animal::isPregnant() {
    bool enoughEnergy = getEnergyLevel() > 0.5;
    bool isProlif = age % prolif() == 0;
    return isProlif && enoughEnergy;
}

float Animal::getEnergyLevel() {
    return energy;
}

std::ostream &operator<<(std::ostream &out, Animal &animal) {
    cout << animal.id << ";" << animal.age << ";" << animal.energy << ";" << animal.cellId;
    return out;
}

void Animal::increaseEnergy(float delta) {
    energy = min(1.0f, energy + delta);
}

void Animal::reduceEnergy() {
    energy -= 0.1;
}

Cell *Animal::getCell() {
    return land->getCell(cellId);
}
