#include "gpio_pin.h"

#include <wiringPi.h>

// Initialisation de la bibliothèque WiringPi
void initMotors() {
    pinMode(PIN_M1A, PWM_OUTPUT);
	pinMode(PIN_M1B, PWM_OUTPUT);
	pinMode(PIN_M2A, PWM_OUTPUT);
	pinMode(PIN_M2B, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(400);    // Réglage de la fréquence PWM
    pwmSetRange(1024);   // Réglage de la plage PWM (0-1024)
}

// Fonction pour faire avancer le moteur
void forward(int R2) {
    digitalWrite(M1B, LOW);
    digitalWrite(M2B, LOW);
    pwmWrite(M1A, (int)(R2*1024)/256);
    pwmWrite(M2A, (int)(R2*1024)/256);
}

/*
// Fonction pour faire reculer le moteur
void reverse() {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, HIGH);
    pwmWrite(PWM_PIN, 512);  // 50% de puissance
}

// Fonction pour arrêter le moteur
void stop() {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    pwmWrite(PWM_PIN, 0);  // PWM à zéro pour arrêter le moteur
}

void turnRight(int angle) {
    
   

}
*/


int main() {
	wiringPiSetupGpio();
    init();  // Initialisation
	while(1) {
		forward(255);
	}


    return 0;
}

