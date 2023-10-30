#include "gpio_pin.h"
#include "buzzer.h"

#include <wiringPi.h>

void initBuzzer() {
    pinMode(PIN_BUZZER, OUTPUT);
}

void buzzerMode(int high_low) {
    digitalWrite(PIN_BUZZER,high_low);
}