#include "gpio_pin.h"

#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>



void initDistanceSensor() {
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);

    // Initializing Trig signal with low input
    digitalWrite(PIN_TRIG, LOW);
}

int getDistance() {
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    
    while (digitalRead(PIN_ECHO) == LOW)
        ;
    long startTime = micros();
    
    while (digitalRead(PIN_ECHO) == HIGH)
        ;
    long endTime = micros();
    
    long travelTime = endTime - startTime;
    int distance = travelTime / 58; // Calcul de la distance en centimètres
    
    return distance;
}

int main() {
    setup();
    
    while (1) {
        int distance = getDistance();
        printf("Distance : %d cm\n", distance);
        sleep(1); // Mesure toutes les 1 seconde
    }
    
    return 0;
}
