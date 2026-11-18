#include "button.h"
#include <cstdint>
#include "pico/stdlib.h"

static const uint32_t DEBOUNCE_MS = 25;
static bool lastLevel[30];
static uint32_t lastChangeMs[30];

void buttonInit(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);

    lastLevel[pin, GPIO_IN] = true;  // released = high 
    lastChangeMs[pin] = 0;
}

bool buttonPressed(uint pin) {
    bool level = gpio_get(pin);
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if(level != lastLevel[pin] && now - lastChangeMs[pin] >= DEBOUNCE_MS) {
        lastLevel[pin] = level;
        lastChangeMs[pin] = now;
        return level == false; // low = pressed 
    }

    return false; 
}