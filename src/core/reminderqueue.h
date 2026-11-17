#pragma once
#include "reminder.h"

class ReminderQueue {
public: 
    static constexpr int MAX = 16;
    uint32_t add(Reminder r);
    const Reminder* peekDue(uint32_t nowSec) const;
    void completeFront(uint32_t nowSec);
    bool remove(uint32_t id);
    int size() const { return count; }
    const Reminder& at(int i) const { return items[i]; }
private:
    Reminder items[MAX];
    int count = 0;
    uint32_t nextId = 1;

    void insertSorted(const Reminder& r);
    void removeAt(int i);
};