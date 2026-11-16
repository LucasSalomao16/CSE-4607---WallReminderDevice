#pragma once
#include "pico/stdlib.h"
void buzzerInit(uint pin, uint freqHz);

// true = tone, false = silent
void buzzerSet(bool on);