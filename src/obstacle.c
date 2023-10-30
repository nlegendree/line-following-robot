#include "gpio_pin.h"

#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>



void setup() {
    wiringPiSetup();
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    
    // Initialiser le signal Trig à basse impulsion
    digitalWrite(PIN_TRIG, LOW);
    delay(2);
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
