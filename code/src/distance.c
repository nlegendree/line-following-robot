#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include "distance.h"
#include "gpioPins.h"

#define SOUND_SPEED 34300

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
    int distance = travelTime/2*SOUND_SPEED;
    
    return distance;
}