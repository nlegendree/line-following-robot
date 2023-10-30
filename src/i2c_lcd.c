#include "i2c_lcd.h"

#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>

void initLCD() {

    int i;

    pcf8574Setup(AF_BASE,I2C_ADDRESS);
    
    if (lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) < 0)
    {
        fprintf (stderr, "lcdInit failed\n") ;
        exit (EXIT_FAILURE) ;
    }
    
    for(i=0;i<8;i++)
          pinMode(AF_BASE+i,OUTPUT);
    digitalWrite(AF_LED,1);
    digitalWrite(AF_RW,0);

}

int exempleASupprimer() {   
    
    initLCD();

    while(1)
    {   

	lcdClear(handle);
	lcdPrintf(handle,"%f.2",temp);

    }
    
    return 0; 
}		
