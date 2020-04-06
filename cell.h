#ifndef CELL_T
#define CELL_T

#include<iostream>
#include<set>

using namespace std;

class Animal;

class Cell {
    static int counter;
    int id;
    float grassLevel;
    set<Animal *> *animalSet;
public:
    Cell();

    void growGrass();

    void reduceGrass(float);

    float getGrassLevel();

    int getId();

    set<Animal *> *getAnimalSet();
};

#endif