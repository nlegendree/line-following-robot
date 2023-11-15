#include "motors.h"
#include "gpioPins.h"
#include "controller.h"

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
        pwmWrite(PIN_EN1,(int)(coeffAngle*coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)(coeffSpeed*PWM_RANGE));
    }
    else {
        float coeffAngle = (float)(MAX_AXIS - angle)/(MID_AXIS+1);
        pwmWrite(PIN_EN1,(int)(coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)(coeffAngle*coeffSpeed*PWM_RANGE));
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
        pwmWrite(PIN_EN1,(int)(coeffAngle*coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)(coeffSpeed*PWM_RANGE));
    }
    else {
        float coeffAngle = (float)(MAX_AXIS - angle)/(MID_AXIS+1);
        pwmWrite(PIN_EN1,(int)(coeffSpeed*PWM_RANGE));
        pwmWrite(PIN_EN2,(int)(coeffAngle*coeffSpeed*PWM_RANGE));
    }
}

// Fonction pour arrêter le moteur
void stop() {
    pwmWrite(PIN_EN1,0);
    pwmWrite(PIN_EN2,0);
}

// Fonction pour faire avancer le moteur en mode suiveur de ligne
void LF_forward() {

}

// Fonction pour faire tourner le moteur à gauche en mode suiveur de ligne
void LF_turnLeft() {

}

// Fonction pour faire tourner le moteur à droite en mode suiveur de ligne
void LF_turnRight() {

}
