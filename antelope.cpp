#include "antelope.h"

Antelope::Antelope(int cellId) : Herbivore(2, cellId) {}

float Antelope::needGrass() {
    return 7;
}

int Antelope::lifeSpan() {
    return 25 + rand() % 5;
}

int Antelope::prolif() {
    return 10 + rand() % 10;
}

void Antelope::birth() {
    new Antelope(*this);
}