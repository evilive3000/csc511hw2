#ifndef ZEBRA_T
#define ZEBRA_T

#include<iostream>
#include "herbivore.h"

class Zebra : public Herbivore {
public:
    Zebra(GrassLand *, queue<Event *> *, int);

protected:
    float needGrass() override;

    int lifeSpan() override;

    void birth() override;

    int prolif() override;
};

#endif