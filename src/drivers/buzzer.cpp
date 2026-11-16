#include "buzzer.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <cstdint>

// static = only visible inside this file
static uint buzzerPin;
static uint buzzerSlice;
static uint16_t buzzerWrap;

void buzzerInit(uint pin, uint freqHz) {
    buzzerPin = pin;
    gpio_set_function(buzzerPin, GPIO_FUNC_PWM);
    buzzerSlice = pwm_gpio_to_slice_num(buzzerPin);

    // PWM counter runs at clk_sys / div and wraps every (wrap + 1) counts.
    float div = 64.0f;
    buzzerWrap = (uint16_t)(clock_get_hz(clk_sys) / div / freqHz - 1);
    pwm_set_clkdiv(buzzerSlice, div);
    pwm_set_wrap(buzzerSlice, buzzerWrap);

    buzzerSet(false); // start silent
    pwm_set_enabled(buzzerSlice, true);
}

void buzzerSet(bool on) {
    // 50% duty = square wave = tone.
    // Level above wrap = pin always HIGH = silent (module is active-low).
    pwm_set_gpio_level(buzzerPin, on ? buzzerWrap / 2 : buzzerWrap + 1);
}