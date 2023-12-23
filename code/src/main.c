#include "controller.h"
#include "i2cLCD.h"
#include "gpioPins.h"
#include "lineFinder.h"
#include "motors.h"
#include "buzzer.h"
#include "distance.h"

#include <SDL2/SDL.h>
#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define MODE_MANUAL     0
#define MODE_LINEFINDER 1

#define FORWARD         0
#define TURN_LEFT       1
#define TURN_RIGHT      2

int lcd, mode, motorState, R2, L2, LX;
bool controllerConnected, nearObstacle, exitSDL;

PI_THREAD(lcdPrintAndGetDistance) {
    while (!exitSDL) {
        lcdClear(lcd);
        if (controllerConnected) {
            if (mode == MODE_LINEFINDER) {
                int distance = getDistance();
                if (distance <= DISPLAY_DISTANCE) {
                    if (distance <= STOP_DISTANCE) {
                        lcdPrintf(lcd,"Obstacle too    close!");
                        nearObstacle = 1;
                    }
                    else {
                        lcdPrintf(lcd,"Obstacle : %d cm",distance);
                        nearObstacle = 0;
                    }
                }
                else {
                    switch(motorState) {
                    case FORWARD:
                        lcdPrintf(lcd,"Moving forward");
                        break;
                    case TURN_LEFT:
                        lcdPrintf(lcd,"Truning left");
                        break;
                    case TURN_RIGHT:
                        lcdPrintf(lcd,"Turning right");
                        break;
                    }
                    nearObstacle = 0;
                }
            }
            else if (mode == MODE_MANUAL) {
                lcdPrintf(lcd,"Speed : %d kph",abs((int)((R2-L2)/252)));
            }
        }
        else {
            lcdPrintf(lcd,"Waiting for     controller...");
        }
        delay(100);
    }
    return 0;
}

void lineFinder(int lcd){
    bool left = detectLine(PIN_LINEFINDER_LEFT);
    bool center = detectLine(PIN_LINEFINDER_CENTER);
    bool right = detectLine(PIN_LINEFINDER_RIGHT);
    printf("%d %d %d\n",left,center,right);
    
    if (nearObstacle) {
        stopMotors();
        buzzerOn();
    }
    else {
        if (!left && !center && !right) {
            switch(motorState) {
                case FORWARD:
                    LF_forward();
                    break;
                case TURN_LEFT:
                    LF_turnLeft();
                    break;
                case TURN_RIGHT:
                    LF_turnRight();
                    break;
            }
        }
        else if (detectIntersection(left,center,right) || center) {
            LF_forward();
            motorState = FORWARD;
        }
        else if (left) {
            LF_turnLeft();
            motorState = TURN_LEFT;
        }
        else if (right) {
            LF_turnRight();
            motorState = TURN_RIGHT;
        }
        buzzerOff();
    }
}

void manualControl(int lcd, SDL_GameController *controller) {
    R2 = triggerValue(controller,SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    L2 = triggerValue(controller,SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    LX = axisValue(controller,SDL_CONTROLLER_AXIS_LEFTX);
    if (R2 >= L2) {
        forward(R2-L2,LX);
    }
    else {
        backward(L2-R2,LX);
    }
}

int main(int argc, char* argv[]) {
    // WiringPi Initialization
    wiringPiSetupGpio();
    
    // LCD Initialization
    lcd = initLCD();

    // Controller Initialization
    SDL_GameController *controller = initController();

    // Motors Initialization
    initMotors();

    // Line-Finder Initialization
    initLineFinder();
    
    // Line-Finder Initialization
    initDistanceSensor();

    // Buzzer Initialization
    initBuzzer();
    buzzerOff();

    // LCD and Distance Sensor Thread Creation
    piThreadCreate(lcdPrintAndGetDistance);

    // Main loop
    SDL_Event event;
    exitSDL = 0;
    controllerConnected = 0;
    mode = MODE_MANUAL;
    nearObstacle = 0;
    motorState = FORWARD;
    while (!exitSDL) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            exitSDL = 1;
        if (event.cdevice.type == SDL_CONTROLLERDEVICEADDED && !controllerConnected) {
            controller = SDL_GameControllerOpen(0);
            controllerConnected = 1;
        }
        if (event.cdevice.type == SDL_CONTROLLERDEVICEREMOVED && controllerConnected) {
            SDL_GameControllerClose(controller);
            stopMotors();
            mode = MODE_MANUAL;
            buzzerOff();
            controllerConnected = 0;
        }
        if (controllerConnected) {
            if (buttonIsBeingPressed(controller,SDL_CONTROLLER_BUTTON_A)) // Press CROSS to enter Line-Finder Mode
                mode = MODE_LINEFINDER;
            else if (buttonIsBeingPressed(controller,SDL_CONTROLLER_BUTTON_B)) { // Press CIRCLE to leave Line-Finder Mode
                buzzerOff();
                mode = MODE_MANUAL;
                motorState = FORWARD;
            }

            if (mode == MODE_LINEFINDER)
                lineFinder(lcd);
            else if (mode == MODE_MANUAL)
                manualControl(lcd,controller);
        }
    }

    buzzerOff();
    SDL_Quit();

    return 0;
}
