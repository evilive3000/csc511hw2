#ifndef EVENT_T
#define EVENT_T

#include <iostream>
#include <string>
#include <queue>
#include "grassLand.h"

using namespace std;

class Event {
public:
    GrassLand *land;
    queue<Event *> *events;
public:
    Event(GrassLand *, queue<Event *> *);

    virtual void selfProcess();
};

#endif