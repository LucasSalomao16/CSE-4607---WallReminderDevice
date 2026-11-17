#pragma once
#include <cstdint>

struct Reminder {
    uint32_t id = 0;
    char text[64] = {};
    uint32_t dueSec = 0;
    uint32_t repeatSec = 0; 
};