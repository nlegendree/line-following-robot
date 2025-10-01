#include <SDL2/SDL.h>
#include <fcntl.h>
#include <lcd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

#include "buzzer.h"
#include "controller.h"
#include "distance.h"
#include "gpioPins.h"
#include "i2cLCD.h"
#include "lineFinder.h"
#include "motors.h"

#define MODE_MANUAL 0
#define MODE_LINEFINDER 1

#define FORWARD 0
#define TURN_LEFT 1
#define TURN_RIGHT 2

// Global variables used to communicate between processes
int lcd, mode, motorState, R2, L2, LX;
bool controllerConnected, nearObstacle, exitSDL;

// LCD display and distance acquisition process
PI_THREAD(lcdPrintAndGetDistance) {
    while (!exitSDL) {
        lcdClear(lcd);
        if (controllerConnected) {          // If a controller is connected
            if (mode == MODE_LINEFINDER) {  // If the robot is in line-finding mode
                int distance = getDistance();
                if (distance <= DISPLAY_DISTANCE) {   // If the distance sensor detects an obstacle
                    if (distance <= STOP_DISTANCE) {  // If an obstacle is too close to the distance sensor
                        lcdPrintf(lcd, "Obstacle too    close!");
                        nearObstacle = 1;
                    } else {  // If an obstacle is relatively close to the distance sensor
                        lcdPrintf(lcd, "Obstacle : %d cm", distance);
                        nearObstacle = 0;
                    }
                } else {  // If the distance sensor does not detect any obstacle, the LCD display shows the direction the robot is taking
                    switch (motorState) {
                        case FORWARD:
                            lcdPrintf(lcd, "Moving forward");
                            break;
                        case TURN_LEFT:
                            lcdPrintf(lcd, "Truning left");
                            break;
                        case TURN_RIGHT:
                            lcdPrintf(lcd, "Turning right");
                            break;
                    }
                    nearObstacle = 0;
                }
            } else if (mode == MODE_MANUAL) {  // If the robot is in manual mode
                lcdPrintf(lcd, "Speed : %d kph", abs((int)((R2 - L2) / 252)));
            }
        } else {  // If a controller is not connected
            lcdPrintf(lcd, "Waiting for     controller...");
        }
        delay(100);
    }
    return 0;
}

// Direction selection function in line-finding mode
void lineFinder(int lcd) {
    // Line finder sensors states update
    bool left = detectLine(PIN_LINEFINDER_LEFT);
    bool center = detectLine(PIN_LINEFINDER_CENTER);
    bool right = detectLine(PIN_LINEFINDER_RIGHT);
    printf("%d %d %d\n", left, center, right);

    // Actions based on these states
    if (nearObstacle) {  // If the distance sensor detects an obstacle
        stopMotors();
        buzzerOn();
    } else {                               // If the distance sensor does not detect any obstacle
        if (!left && !center && !right) {  // If all sensors detect a white surface, the motors keep their previous state
            switch (motorState) {
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
        } else if (detectIntersection(left, center, right) || center) {  // If the sensors detect an intersection or a front line, the motors move forward
            LF_forward();
            motorState = FORWARD;
        } else if (left) {  // If only the left sensor detects a line, the motors turn left
            LF_turnLeft();
            motorState = TURN_LEFT;
        } else if (right) {  // If only the right sensor detects a line, the motors turn right
            LF_turnRight();
            motorState = TURN_RIGHT;
        }
        buzzerOff();
    }
}

// Robot control function in manual-control mode
void manualControl(int lcd, SDL_GameController *controller) {
    // Triggers and axes states update
    R2 = triggerValue(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    L2 = triggerValue(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    LX = axisValue(controller, SDL_CONTROLLER_AXIS_LEFTX);

    // Actions based on these states
    if (R2 >= L2) {  // If the acceleration trigger is pressed further in than the reverse trigger
        forward(R2 - L2, LX);
    } else {  // If the reverse trigger is pressed further in than the acceleration trigger
        backward(L2 - R2, LX);
    }
}

// Main function
int main(int argc, char *argv[]) {
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
        if (event.type == SDL_QUIT)  // Checks if the user wants to exit the program
            exitSDL = 1;
        if (event.cdevice.type == SDL_CONTROLLERDEVICEADDED && !controllerConnected) {  // Checks if a controller has been connected
            controller = SDL_GameControllerOpen(0);
            controllerConnected = 1;
        }
        if (event.cdevice.type == SDL_CONTROLLERDEVICEREMOVED && controllerConnected) {  // Checks if a controller has been disconnected
            SDL_GameControllerClose(controller);
            stopMotors();
            mode = MODE_MANUAL;
            buzzerOff();
            controllerConnected = 0;
        }
        if (controllerConnected) {
            if (buttonIsBeingPressed(controller, SDL_CONTROLLER_BUTTON_A))  // Press CROSS to enter Line-Finder Mode
                mode = MODE_LINEFINDER;
            else if (buttonIsBeingPressed(controller, SDL_CONTROLLER_BUTTON_B)) {  // Press CIRCLE to leave Line-Finder Mode
                buzzerOff();
                mode = MODE_MANUAL;
                motorState = FORWARD;
            }

            if (mode == MODE_LINEFINDER)  // Executes the line-following mode
                lineFinder(lcd);
            else if (mode == MODE_MANUAL)  // Executes the manual mode
                manualControl(lcd, controller);
        }
    }

    // Actions performed when the program exits
    buzzerOff();
    SDL_Quit();

    return EXIT_SUCCESS;
}
