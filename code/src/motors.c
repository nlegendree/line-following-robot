#include "motors.h"
#include "gpioPins.h"
#include "controller.h"

#include <math.h>
#include <wiringPi.h>

// Initialisation de la bibliothèque WiringPi
void initMotors() {
    pinMode(PIN_M1A,OUTPUT);
    pinMode(PIN_M1B,OUTPUT);
    pinMode(PIN_M2A,OUTPUT);
    pinMode(PIN_M2B,OUTPUT);
    pinMode(PIN_EN1,PWM_OUTPUT);
    pinMode(PIN_EN2,PWM_OUTPUT);

    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(PWM_CLOCK);    // Réglage de la fréquence PWM
    pwmSetRange(PWM_RANGE);   // Réglage de la plage PWM (0-1024)
}

// Fonction pour faire avancer le moteur
void forward(int speed, int angle) {
    digitalWrite(PIN_M1A,HIGH);
    digitalWrite(PIN_M2A,HIGH);
    digitalWrite(PIN_M1B,LOW);
    digitalWrite(PIN_M2B,LOW);
    
    float coeffSpeed = (float)speed/MAX_TRIGGER;
    if (angle <= MID_AXIS) {
        float coeffAngle = (float)angle/MID_AXIS;
        pwmWrite(PIN_EN1,(int)round(coeffAngle*coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)round(coeffSpeed*PWM_RANGE));
    }
    else {
        float coeffAngle = (float)(MAX_AXIS - angle)/(MID_AXIS+1);
        pwmWrite(PIN_EN1,(int)round(coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)round(coeffAngle*coeffSpeed*PWM_RANGE));
    }
}

// Fonction pour faire reculer le moteur
void backward(int speed, int angle) {
    digitalWrite(PIN_M1A,LOW);
    digitalWrite(PIN_M2A,LOW);
    digitalWrite(PIN_M1B,HIGH);
    digitalWrite(PIN_M2B,HIGH);
    
    float coeffSpeed = (float)speed/MAX_TRIGGER;
    if (angle <= MID_AXIS) {
        float coeffAngle = (float)angle/MID_AXIS;
        pwmWrite(PIN_EN1,(int)round(coeffAngle*coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)round(coeffSpeed*PWM_RANGE));
    }
    else {
        float coeffAngle = (float)(MAX_AXIS - angle)/(MID_AXIS+1);
        pwmWrite(PIN_EN1,(int)round(coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)round(coeffAngle*coeffSpeed*PWM_RANGE));
    }
}

// Fonction pour arrêter le moteur
void stop() {
    pwmWrite(PIN_EN1,0);
    pwmWrite(PIN_EN2,0);
}