#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "distance.h"
#include "gpioPins.h"

void initDistanceSensor() {
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

int getDistance() {
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    
    long startTime, endTime;
    while (digitalRead(PIN_ECHO) == LOW) 
        startTime = micros();
    while (digitalRead(PIN_ECHO) == HIGH)
        endTime = micros();
    
    long travelTime = endTime - startTime;
    int distance = travelTime/58;
    
    return distance;
}