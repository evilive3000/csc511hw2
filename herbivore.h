#ifndef HERBIVORE_T
#define HERBIVORE_T

#include<iostream>
#include "animal.h"

using namespace std;

class Herbivore : public Animal {
protected:
    void feed() override;

    virtual float needGrass() = 0;

public:
    Herbivore(GrassLand *, queue<Event *> *, int);

};

#endif