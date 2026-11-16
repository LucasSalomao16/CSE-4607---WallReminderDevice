#pragma once

enum class Event{
    motion,
    reminderDue,
    snooze,
    done,
    tick, //checked by the controller every loop
};


