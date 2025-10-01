#include "distance.h"

#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>

#include "gpioPins.h"

// Distance sensor initialization
void initDistanceSensor() {
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

// Function to acquire the distance through the ultrasonic sensor
int getDistance() {
    struct timeval tv1;
    struct timeval tv2;
    long start, stop;
    float dis;

    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(PIN_TRIG, HIGH);  // produce a pluse
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    while (!(digitalRead(PIN_ECHO) == 1))
        ;
    gettimeofday(&tv1, NULL);  // current time

    while (!(digitalRead(PIN_ECHO) == 0))
        ;
    gettimeofday(&tv2, NULL);  // current time

    start = tv1.tv_sec * 1000000 + tv1.tv_usec;
    stop = tv2.tv_sec * 1000000 + tv2.tv_usec;

    dis = (float)(stop - start) / 1000000 * 34000 / 2;  // count the distance

    return (int)dis;
}
