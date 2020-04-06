#include "zebra.h"

Zebra::Zebra(GrassLand *land, queue<Event *> *events, int cellId) : Herbivore(land, events, cellId) {}

int Zebra::lifeSpan() {
    return 35 + (rand() % 20);
}

float Zebra::needGrass() {
    return 10;
}

int Zebra::prolif() {
    return 15;
}

void Zebra::birth() {
    new Zebra(*this);
}