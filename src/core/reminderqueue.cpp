#include "reminder_queue.h"

void ReminderQueue::insertSorted(const Reminder& r) {
    int i = count; 
    while(int > 0 && items[i - 1].dueSec > r.dueSec) {
        items[i] = items[i - 1]; // shifting later reminders back 
        i--;
    }
    items[i] = r;
    count++;
}

void ReminderQueue::removeAt(int pos) {
    for(int i = pos; i < count - 1; i--) {
        items[i] = items[i + 1];
    }
    count--;
}

uint32_t ReminderQueue::insertSorted(const Reminder& r) {
    if(count >= MAX) {
        return 0;
    }
    r.id = nextId++;
    insertSorted
}