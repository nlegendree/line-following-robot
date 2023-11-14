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
    pwmSetClock(PWM_CLOCK);    // Réglage de la fréquence PWM
    pwmSetRange(PWM_RANGE);   // Réglage de la plage PWM (0-1024)
}

// Fonction pour faire avancer le moteur
void forward(int speed, int angle) {
    pwmWrite(PIN_M1B,0);
    pwmWrite(PIN_M2B,0);
    pwmWrite(PIN_M1A,PWM_TRIGGER(speed));
    pwmWrite(PIN_M2A,PWM_TRIGGER(speed));
}

// Fonction pour faire reculer le moteur
void backward(int speed, int angle) {
    pwmWrite(PIN_M1A,0);
    pwmWrite(PIN_M2A,0);
    pwmWrite(PIN_M1B,PWM_TRIGGER(speed));
    pwmWrite(PIN_M2B,PWM_TRIGGER(speed));
}

// Fonction pour arrêter le moteur
void stop() {
    pwmWrite(PIN_M1B,0);
    pwmWrite(PIN_M2B,0);
    pwmWrite(PIN_M1A,0);
    pwmWrite(PIN_M2A,0);
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

// Fonction main test
int main_test() {
	wiringPiSetupGpio();
    initMotors();  // Initialisation

    forward(200,MID_AXIS);
    
    delay(2000);

    backward(200,MID_AXIS);
    
    delay(2000);

    stop();

    return 0;
}
