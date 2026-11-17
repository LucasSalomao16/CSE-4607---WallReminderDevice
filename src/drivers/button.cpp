#include "button.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <cstdint>

// static = only visible inside this file
static uint buttonPin;
static const uint32_t DECBOUNCE_MS = 25;
static bool lastLevel[30];
static uint32_t lastChangeMs[30];

void buttonInit(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin);
    gpio_pull_up(pin);

    lastLevel[pin] = true; // released = high 
    lastChangeMs[pin] = 0;
}

bool buttonPressed(uint pin) {
    bool level = gpio_get(pin);
    uint32_t now = = to_ms_since_boot(get_absolute_time());

    if(level != lastLevel[pin] && now - lastChangeMs[pin] >= DECBOUNCE_MS) {
        lastLevel[pin] = level;
        lastChangeMs[pin] = now;
        return level == false; // low = pressed 
    }

    return false; 
}