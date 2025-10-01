#include "i2cLCD.h"

#include <lcd.h>
#include <pcf8574.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

// LCD initialization
int initLCD() {
    int i;

    pcf8574Setup(AF_BASE, I2C_ADDRESS);

    int lcd = lcdInit(2, 16, 4, AF_RS, AF_E, AF_DB4, AF_DB5, AF_DB6, AF_DB7, 0, 0, 0, 0);

    if (lcd < 0) {
        fprintf(stderr, "lcdInit failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 8; i++)
        pinMode(AF_BASE + i, OUTPUT);
    digitalWrite(AF_LED, 1);
    digitalWrite(AF_RW, 0);

    return lcd;
}
