#include "pir.h"

static volatile bool motionFlag = false; // CLAUDE said that volatile is good for interrupts
constexpr uint PIR_PIN = 15;   // GP15 = physical pin 20

//Everytime motion is detected, the gpioCallback function is called. It sets the motionFlag to true, which is 
// then checked in the main loop to handle the motion event.

void gpioCallback(uint gpio, uint32_t events) {
    if (gpio == PIR_PIN && (events & GPIO_IRQ_EDGE_RISE)) {
        motionFlag = true;
    }
}

//sets up pir sensor pin as input and enables interrupt on rising edge
void pirInit(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_down(pin); //pulls down to 0V when no motion is detected
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_RISE, true, &gpioCallback);
}

// checks for motion
bool pirRead() {
    bool motionDetected = motionFlag;
    motionFlag = false; // Clear the flag after reading
    return motionDetected;
}

//checks if pir is high. 
bool pirHigh() {
    return gpio_get(PIR_PIN);
}
