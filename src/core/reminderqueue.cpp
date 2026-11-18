#include "reminderqueue.h"

// Inserts r in order of due time (earliest first). Assumes there is room.
void ReminderQueue::insertSorted(const Reminder& r) {
    int i = count;
    while (i > 0 && items[i - 1].dueSec > r.dueSec) {
        items[i] = items[i - 1]; // shift later reminders back
        i--;
    }
    items[i] = r;
    count++;
}

// Removes the reminder at index pos, shifting the rest forward.
void ReminderQueue::removeAt(int pos) {
    for (int i = pos; i < count - 1; i++) {
        items[i] = items[i + 1];
    }
    count--;
}

// Adds a reminder, assigns it an id, returns the id (0 = queue full).
uint32_t ReminderQueue::add(const Reminder& r) {
    if (count >= MAX) {
        return 0;
    }
    Reminder copy = r;
    copy.id = nextId++;
    insertSorted(copy);
    return copy.id;
}

// Returns the front reminder if it is due, returns nullptr otherwise
const Reminder* ReminderQueue::peekDue(uint32_t nowSec) const 
{
    if(count > 0 && items[0].dueSec <= nowSec) {
        return &items[0];
    }
    return nullptr;
}

// Called when done is pressed, removes the front reminder from the queue. 
void ReminderQueue::completeFront(uint32_t nowSec) {
    // does nothing if queue is empty 
    if(count == 0) {
        return;
    }

    Reminder r = items[0];
    removeAt(0);

    // readd to the queue if it is repeated 
    if(r.repeatSec > 0) {
        while(r.dueSec <= nowSec) {
            r.dueSec += r.repeatSec;
        }

        insertSorted(r);
    }
}

// Returns the number of reminders in the queue 
int ReminderQueue::size() const { 
    return count; 
}

// Returns a refernce to the reminder at position i
const Reminder& ReminderQueue::at(int i) const {
    return items[i]; 
}