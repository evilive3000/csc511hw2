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
#include <queue>

#include "grassLand.h"
#include "event.h"
#include "zebra.h"

using namespace std;

int main() {
    int size = 7;
    GrassLand land(size);   // object containing pointer to array of cells
    cout << "create|grassland|" << size << endl;
    queue<Event *> events;

    events.push(new Event(&land, &events));

    new Zebra(&land, &events, land.randomCell()->getId());
//    new Zebra(&land, &events, land.randomCell()->getId());
//    new Zebra(&land, &events, land.randomCell()->getId());
//    new Zebra(&land, &events, land.randomCell()->getId());



    for (int k = 0; k < 2000; k++) {
        events.front()->selfProcess();
    }
}

