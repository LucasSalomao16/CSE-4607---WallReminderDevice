#pragma once
#include "reminder.h"

class ReminderQueue {
public: 
    static constexpr int MAX = 16; // maximum number of reminders in the queue 
    uint32_t add(const Reminder& r);
    const Reminder* peekDue(uint32_t nowSec) const;
    void completeFront(uint32_t nowSec);
    int size() const;
    const Reminder& at(int i) const;
private:
    Reminder items[MAX];
    int count = 0;
    uint32_t nextId = 1;

    void insertSorted(const Reminder& r);
    void removeAt(int i);
};