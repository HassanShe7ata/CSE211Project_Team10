#include "mbed.h"
#include "Ultrasonic.h"
#include "Motor.h"
#include <cstdio>

/**
 * @file main.cpp
 * @brief Object-following robot car control loop.
 *
 * The robot continuously reads front distance using HC-SR04 and commands
 * both drive motors forward when the measured distance is greater than 15 cm.
 * If distance is 15 cm or less (or measurement timed out as -1), both motors stop.
 */

// Ultrasonic front sensor pins.
#define TRIG_PIN    D9
#define ECHO_PIN    D10

// Motor channel 1 driver pins.
#define MOTOR1_PWM   D5
#define MOTOR1_FWD   D3
#define MOTOR1_REV   D4

// Motor channel 2 driver pins.
#define MOTOR2_PWM   D6
#define MOTOR2_FWD   D7
#define MOTOR2_REV   D8

#define DRIVE_FORWARD_SPEED 0.4f

int main() {
    Ultrasonic frontDistanceSensor(TRIG_PIN, ECHO_PIN);
    
    // Initialize both drive motor channels.
    Motor driveMotor1(MOTOR1_PWM, MOTOR1_FWD, MOTOR1_REV);
    Motor driveMotor2(MOTOR2_PWM, MOTOR2_FWD, MOTOR2_REV);
    
    while (true) {
        int measuredDistanceCm = frontDistanceSensor.getDistance();
        
        if (measuredDistanceCm <= 15) {
            driveMotor1.stop();
            driveMotor2.stop();
            printf("Distance is %d cm (<= 15 cm). Stopping both motors.\r\n", measuredDistanceCm);
        }
        else {
            driveMotor1.forward(DRIVE_FORWARD_SPEED);
            driveMotor2.forward(DRIVE_FORWARD_SPEED);
            printf("Object at %d cm - BOTH MOTORS MOVING FORWARD at %.1f%%\r\n", 
                   measuredDistanceCm, DRIVE_FORWARD_SPEED * 100);
        }
        
        ThisThread::sleep_for(100ms);
    }
}
