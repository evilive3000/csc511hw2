#include <iostream>
#include <deque>
#include <algorithm>
#include "event.h"

using namespace std;

deque<Event *> *Event::events;
GrassLand *Event::land;

Event::Event() {
    if (!events) {
        events = new deque<Event *>;
    }
    events->push_back(this);
}

int Event::selfProcess() {
    cout << "update|cells|";
    int size = land->size * land->size;
    for (int k = 0; k < size; k++) {
        land->g[k].growGrass();
        cout << land->g[k].getGrassLevel() << ";";
    }
    // this needed to make queue more randomized;
    random_shuffle(events->begin(), events->end());
    cout << endl;
}

void Event::setGrassland(GrassLand *l) {
    Event::land = l;
}

void Event::processNext() {
    Event *e = Event::events->front();
    Event::events->pop_front();
    if (e->selfProcess() != 1) {
        Event::events->push_back(e);
    }
}

GrassLand *Event::getGrassland() {
    return Event::land;
}
