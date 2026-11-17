#include "controller.h"

Output Controller::eventOccur(Event event, unsigned int time) {
    // FSM that update the state based on the event.
    switch (currentState) {
        case State::idle:
            if (event == Event::reminderDue) {
                currentState = State::armed;
            }
            break;

        case State::armed:
            if (event == Event::motion) {
                currentState = State::alerting;
                alarmStart = time;
            }
            break;

        case State::alerting:
            // So this is only temporary and not fully done. Rn, Done just clears the alert so we can test repeatedly.
            // We have to update it so that it would go to the next due reminder (armed) or idle if the queue is empty.
            if (event == Event::done) {
                currentState = State::idle;
            }
            else if (event == Event::snooze) {
                currentState = State::snoozed;
                snoozeStart = time;
            }
            else if (event == Event::tick && time - alarmStart >= ALARM_TIMEOUT_MS) {
                currentState = State::armed;
            }
            // TODO: snooze
            break;

        case State::snoozed:
            if(event == Event::tick && time - snoozeStart >= SNOOZE_MS) {
                currentState = State::alerting;
                alarmState = time;
            }
            break;
    }

    //outputs per state
    Output out;
    switch (currentState) {
        case State::idle:     out = {false, false, true};  break;
        case State::armed:    out = {false, false, true};  break;
        case State::alerting: out = {true, true, false}; break;
        case State::snoozed:  out = {false, false, true};  break;
    }
    return out;
}