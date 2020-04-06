#ifndef ANIMAL_T
#define ANIMAL_T

#include <iostream>
#include <string>
#include "event.h"

struct GrassLand;

class Cell;

using namespace std;

class Animal : public Event {
    static int counter;
    int cellId;
    int id;
    int age = 0;
    float energy = 1.0f;
protected:
    void increaseEnergy(float);

    virtual void reduceEnergy();

    virtual void move();

    virtual void feed() = 0;

    virtual int prolif() = 0;

    virtual int lifeSpan() = 0;

    virtual void birth() = 0;

    bool isAlive();

    bool isPregnant();

public:
    Animal(GrassLand *, queue<Event *> *, int);

    Animal(Animal &a);

    ~Animal();

    void selfProcess() override;

    float getEnergyLevel();

    Cell *getCell();

    void printState(string state);

    friend std::ostream &operator<<(std::ostream &out, Animal &animal);
};

#endif