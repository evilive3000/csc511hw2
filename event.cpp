#include <iostream>
#include <queue>
#include <unistd.h>

#include "event.h"

using namespace std;

Event::Event(GrassLand *land, queue<Event *> *events) : land(land), events(events) {}

void Event::selfProcess() {
    cout << "update|cells|";
    int size = land->size * land->size;
    for (int k = 0; k < size; k++) {
        land->g[k].growGrass();
        cout << land->g[k].getGrassLevel() << ";";
    }
    cout << endl;

    events->pop();
    events->push(this);
    usleep(10000);
}

