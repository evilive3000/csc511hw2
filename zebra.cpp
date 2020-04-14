#include "zebra.h"

Zebra::Zebra(int cellId) : Herbivore(1, cellId) {}

float Zebra::needGrass() {
    return 8;
}

int Zebra::lifeSpan() {
    return 37 + rand() % 5;
}

int Zebra::prolif() {
    return 12 + rand() % 10;
}

void Zebra::birth() {
    new Zebra(*this);
}