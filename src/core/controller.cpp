#include "controller.h"

Output Controller::eventOccur(Event event, unsigned int time) {
    // FSM that update the state based on the event.
    nowSec = time / 1000; 
    
    switch (currentState) {
        case State::idle:
            // check if there's any reminders due 
            if(queue.peekDue(nowSec)) {
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
            if (event == Event::done) {
                // if a reminder is done, remove it from the queue and check to see if 
                // there's another reminder due now 
                finishReminder();
            }
            else if (event == Event::snooze) {
                currentState = State::snoozed;
                snoozeStart = time;
            }
            else if (event == Event::tick && time - alarmStart >= ALARM_TIMEOUT_MS) {
                currentState = State::armed;
            }
            break;

        case State::snoozed:
            if(event == Event::done) {
                // if a reminder is finished during snooze, remove it from the queue and check to see if 
                // there's another reminder due now 
                finishReminder();
            }
            else if(event == Event::tick && time - snoozeStart >= SNOOZE_MS) {
                currentState = State::alerting;
                alarmStart = time;
            }

            else if(event == Event::done) {
                currentState = State::idle;
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

void Controller::finishReminder() {
    // remove reminder from the queue
    queue.completeFront(nowSec);

    // check to see if another reminder is due now amd move
    // to armed or idle 
    if(queue.peekDue(nowSec)) {
        currentState = State::armed;
    }
    else {
        currentState = State::idle;
    }
}