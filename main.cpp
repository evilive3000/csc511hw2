/*
In C and in C++ 2-dim arrays are stored in row-major form.
Name of a 1-dim array is identical to a pointer constant to the type of the first
array element. To access a component of a 2-dim array by a pointer to the firsr array
element one must treat it as stored in row-major form as a 1-dim array.

selfProcess: queue elements manage themselves in the queue: can add offspring
to the queue, can remove themselves from the queue and add themselves to the queue

No offspring are yet created
*/

#include <iostream>

#include "grassLand.h"
#include "event.h"
#include "zebra.h"
#include "antelope.h"

using namespace std;

int main() {
    GrassLand land(12);
    Event::setGrassland(&land);

    // Create non Animal Event;
    new Event();

    for (int i = 0; i < 20; i++) {
        new Zebra(land.randomCell()->getId());
        new Antelope(land.randomCell()->getId());
    }

    for (int k = 0; k < 500000; k++) {
        Event::processNext();
    }
}

