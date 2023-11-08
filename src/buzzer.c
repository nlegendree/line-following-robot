#include "buzzer.h"
#include "gpio_pin.h"

#include <wiringPi.h>

void initBuzzer() {
    pinMode(PIN_BUZZER, OUTPUT);
}

void buzzerOn() {
    digitalWrite(PIN_BUZZER, HIGH);
}

void buzzerOff() {
    digitalWrite(PIN_BUZZER, LOW);
}