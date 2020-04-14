#ifndef GRASSLAND_ANTELOPE_H
#define GRASSLAND_ANTELOPE_H

#include "herbivore.h"

class Antelope : public Herbivore {
public:
    Antelope(int);

protected:
    float needGrass() override;

    int lifeSpan() override;

    void birth() override;

    int prolif() override;
};


#endif //GRASSLAND_ANTELOPE_H
