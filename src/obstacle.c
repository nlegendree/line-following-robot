#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define TRIG_PIN 17  // GPIO pin pour le signal Trig
#define ECHO_PIN 18  // GPIO pin pour le signal Echo

void setup() {
    wiringPiSetup();
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    
    // Initialiser le signal Trig à basse impulsion
    digitalWrite(TRIG_PIN, LOW);
    delay(2);
}

int getDistance() {
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    while (digitalRead(ECHO_PIN) == LOW)
        ;
    long startTime = micros();
    
    while (digitalRead(ECHO_PIN) == HIGH)
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
