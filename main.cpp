#include "mbed.h"
#include "PinNames.h"
#include "Motor.h"
#include "Ultrasonic.h"

// ===== Distance Thresholds (cm) =====
#define MIN_DIST 15      // Closer than this -> back up
#define MAX_DIST 30      // Farther than this -> move forward

// ===== Motor Speed (0.0 - 1.0) =====
#define MOTOR_SPEED 0.40f

// ===== Motor Driver Pin Mapping =====
// NUCLEO-F401RE Arduino header equivalents:
// D4=PB_5, D5=PB_4, D6=PB_10, D7=PA_8, D9=PC_7, D10=PB_6, D11=PA_7, D12=PA_6
#define MOTOR_A_PWM PC_7   // D9
#define MOTOR_A_FWD PB_5   // D4
#define MOTOR_A_REV PB_4   // D5

#define MOTOR_B_PWM PB_6   // D10
#define MOTOR_B_FWD PA_7   // D11
#define MOTOR_B_REV PA_6   // D12

// ===== Ultrasonic Pin Mapping =====
#define ULTRASONIC_TRIG PB_10  // D6
#define ULTRASONIC_ECHO PA_8   // D7

int main()
{
    Ultrasonic frontSensor(ULTRASONIC_TRIG, ULTRASONIC_ECHO);
    Motor motorA(MOTOR_A_PWM, MOTOR_A_FWD, MOTOR_A_REV);
    Motor motorB(MOTOR_B_PWM, MOTOR_B_FWD, MOTOR_B_REV);

    printf("=== Object-Following Robot Started ===\r\n");
    fflush(stdout);

    while (true) {
        int distanceCm = frontSensor.getDistance();

        if (distanceCm < 0) {
            printf("Distance: NO ECHO (timeout)\r\n");
            motorA.stop();
            motorB.stop();
        } else {
            printf("Distance: %d cm\r\n", distanceCm);

            if (distanceCm < MIN_DIST) {
                motorA.backward(MOTOR_SPEED);
                motorB.backward(MOTOR_SPEED);
            } else if (distanceCm > MAX_DIST) {
                motorA.forward(MOTOR_SPEED);
                motorB.forward(MOTOR_SPEED);
            } else {
                motorA.stop();
                motorB.stop();
            }
        }

        fflush(stdout);
        thread_sleep_for(100);
    }
}
