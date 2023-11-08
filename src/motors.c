#include "motors.h"
#include "gpioPins.h"
#include "controller.h"

#include <wiringPi.h>

// Initialisation de la bibliothèque WiringPi
void initMotors() {
    pinMode(PIN_M1A,PWM_OUTPUT);
	pinMode(PIN_M1B,PWM_OUTPUT);
	pinMode(PIN_M2A,PWM_OUTPUT);
	pinMode(PIN_M2B,PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(400);    // Réglage de la fréquence PWM
    pwmSetRange(1024);   // Réglage de la plage PWM (0-1024)
}

// Fonction pour faire avancer le moteur
void forward(int R2) {
    pwmWrite(PIN_M1B,0);
    pwmWrite(PIN_M2B,0);
    pwmWrite(PIN_M1A,(int)(R2*1024)/MAX_TRIGGER);
    pwmWrite(PIN_M2A,(int)(R2*1024)/MAX_TRIGGER);
}

// Fonction pour faire reculer le moteur
void backward(int L2) {
    pwmWrite(PIN_M1A,0);
    pwmWrite(PIN_M2A,0);
    pwmWrite(PIN_M1B,(int)(L2*1024)/MAX_TRIGGER);
    pwmWrite(PIN_M2B,(int)(L2*1024)/MAX_TRIGGER);
}

// Fonction pour arrêter le moteur
void stop() {
    pwmWrite(PIN_M1B,0);
    pwmWrite(PIN_M2B,0);
    pwmWrite(PIN_M1A,0);
    pwmWrite(PIN_M2A,0);
}

// Fonction main test
int main_test() {
	wiringPiSetupGpio();
    initMotors();  // Initialisation

    forward(200);
    
    delay(2000);

    backward(200);
    
    delay(2000);

    stop();

    return 0;
}

