#include <cstdio>
#include <cstring>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "core/controller.h"
#include "drivers/buzzer.h"
#include "drivers/pir.h"
#include "drivers/button.h"

// ----- The current pins we have to move to config.h later for clean code
constexpr uint BUZZER_PIN = 14; // GP14 = physical pin 19
constexpr uint SNOOZE_PIN = 17; // GP17 = physical pin 22
constexpr uint DONE_PIN = 16; // GP16 = physical pin 21
constexpr uint BUZZER_FREQ_HZ = 2700; // most piezos are loudest around 2-4 kHz
constexpr uint PIR_PIN = 15;   // GP15 = physical pin 20

Controller ctrl; //this creates the controller object (main state machine)

// --------- helper functions BELOW

// counts milliseconds since Pico turned on
uint32_t nowMs() {
    return to_ms_since_boot(get_absolute_time());
}

// just for printing state names in the log, not used by the controller
const char* stateName(State s) {
    switch (s) {
        case State::idle:     return "IDLE";
        case State::armed:    return "ARMED";
        case State::alerting: return "ALERTING";
        case State::snoozed:  return "SNOOZED";
    }
    return "?";
}

// applies the outputs to the hardware (LED, buzzer, etc.) For now this only turns the onboard LED on/off, but later it will also control the buzzer and the LED matrix.
void applyOutputs(const Output& out) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, out.alarmOn);
    buzzerSet(out.alarmOn); //turns on buzzer when alarm is on
    
    // TODO: LED matrix (text / image)
}

// basically handles all the events.
// if the state changes, it applies the outputs and prints a log message.
void handle(Event e) {
    State before = ctrl.getCurrentState();
    Output out = ctrl.eventOccur(e, nowMs());

    // Only touch hardware / print when the state actually changes.
    if (ctrl.getCurrentState() != before) {
        applyOutputs(out);
        printf("%s -> %s  [alarm=%d text=%d img=%d]\n",
               stateName(before), stateName(ctrl.getCurrentState()),
               out.alarmOn, out.displayTxt, out.displayImg);
    }
}


// --------- helper functions ABOVE


int main() {
    stdio_init_all();
    // checking in on board led works
    if (cyw43_arch_init()) {
        printf("Wi-Fi chip init failed (needed for the onboard LED)\n");
        return 1;
    }
    //pins
    pirInit(PIR_PIN);
    buzzerInit(BUZZER_PIN, BUZZER_FREQ_HZ);
    buttonInit(SNOOZE_PIN); // initialize the snooze button
    buttonInit(DONE_PIN); // initialize the done button  
    
    sleep_ms(2000);
    applyOutputs(ctrl.eventOccur(Event::tick, nowMs())); //starts fsm

    while (true) {
        // Fake inputs from the serial monitor (non-blocking read)
        // this is just because we dont have any reminder system yet, so its for simulation
        int c = getchar_timeout_us(0);
        if (c == 'r') { // when r is pressed a reminder is added to the queue
         Reminder r; 
         strcpy(r.text, "Take out trash");
         r.dueSec = nowMs()/1000; // due immediately 
         ctrl.queue.add(r); 
         printf("Added reminder, queue size = %d\n", ctrl.queue.size());

        }
        if (c == 'd') handle(Event::done);
        if (c == 's') handle(Event::snooze);
        //temporary print to see if the buttons are working
        if (buttonPressed(SNOOZE_PIN)) { printf("BTN: snooze\n"); handle(Event::snooze); }
        if (buttonPressed(DONE_PIN))   { printf("BTN: done\n");   handle(Event::done); }

        // Real input from the PIR
        if (pirRead()) {
            printf("PIR: motion\n");   
            handle(Event::motion);
        }
        
        if (ctrl.getCurrentState() == State::armed && pirHigh()) {
            handle(Event::motion);
        }
        
        handle(Event::tick); // CLAUDE: lets the controller check timeouts (once those are written)
    }
}