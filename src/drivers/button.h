#pragma once
#include "pico/stdlib.h"

enum class ButtonEvent {
    none, 
    pressed
};

void buttonInit(uint pin);

bool buttonPressed(uint pin);