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
        unsigned int SNOOZE_MS = 10UL * 60 * 1000;
        unsigned int ALARM_TIMEOUT_MS = 60UL * 1000;


public:
    Output eventOccur(Event event, unsigned int time);
    State getCurrentState() const { return currentState; } //for tests
};

