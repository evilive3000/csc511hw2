#ifndef EVENT_T
#define EVENT_T

#include <iostream>
#include <string>
#include <deque>
#include "grassLand.h"

using namespace std;

class Event {
    static GrassLand *land;
    static deque<Event *> *events;

    virtual int selfProcess();

public:
    Event();

    static void setGrassland(GrassLand *);

    static GrassLand *getGrassland();


    static void processNext();

};

#endif