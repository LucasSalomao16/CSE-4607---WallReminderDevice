#pragma once
#include "events.h"

//states
enum class State{
    idle,
    armed,
    alerting,
    snoozed,
};

//outputs per state
struct Output{
    bool alarmOn;
    bool displayTxt;
    bool displayImg;
};


class Controller{
private:
        State currentState = State::idle;
        unsigned int alarmStart = 0;
        unsigned int snoozeStart = 0;


public:
    Output eventOccur(Event event, unsigned int time);
    State getCurrentState() const { return currentState; } //for tests
};

