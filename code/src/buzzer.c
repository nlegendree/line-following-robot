#include "buzzer.h"
#include "gpioPins.h"

#include <wiringPi.h>

// Buzzer initialization
void initBuzzer() {
    pinMode(PIN_BUZZER, OUTPUT);
}

// Function to turn on the buzzer
void buzzerOn() {
    digitalWrite(PIN_BUZZER, HIGH);
}

// Function to turn off the buzzer
void buzzerOff() {
    digitalWrite(PIN_BUZZER, LOW);
}
