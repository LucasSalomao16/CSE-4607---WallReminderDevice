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