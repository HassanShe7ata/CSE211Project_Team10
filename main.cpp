#include "mbed.h"

// ===== Distance Thresholds (cm) =====
#define MIN_DIST        15       // Closer than this -> back up
#define MAX_DIST        30       // Farther than this -> move forward
#define ECHO_TIMEOUT_US 30000    // 30 ms max wait (~5 m range limit)

// ===== Motor Speed (0.0 - 1.0) =====
#define MOTOR_SPEED     0.40f    // 40% duty cycle

// ===== Motor Direction Pins =====
DigitalOut in1(D4);   // Motor A - forward pin
DigitalOut in2(D5);   // Motor A - backward pin
DigitalOut in3(D11);  // Motor B - forward pin
DigitalOut in4(D12);  // Motor B - backward pin

// ===== Motor PWM (Speed Control) =====
PwmOut ena(D9);       // Motor A enable / speed
PwmOut enb(D10);      // Motor B enable / speed

// ===== Ultrasonic Sensor Pins =====
DigitalOut trigPin(D6);
DigitalIn echoPin(D7);

// ===== Shared Timer for Echo Measurement =====
Timer echoTimer;

float readDistance()
{
    // Send 10 us trigger pulse
    trigPin = 0;
    wait_us(2);
    trigPin = 1;
    wait_us(10);
    trigPin = 0;

    // Wait for ECHO to go HIGH
    int waitCount = 0;
    while (echoPin == 0) {
        wait_us(1);
        if (++waitCount >= ECHO_TIMEOUT_US) {
            return -1.0f;
        }
    }

    // Measure HIGH pulse width
    echoTimer.reset();
    echoTimer.start();

    waitCount = 0;
    while (echoPin == 1) {
        wait_us(1);
        if (++waitCount >= ECHO_TIMEOUT_US) {
            echoTimer.stop();
            return -1.0f;
        }
    }
    echoTimer.stop();

    // Distance (cm) = time_us * 0.034 / 2
    float durationUs = (float)echoTimer.elapsed_time().count();
    return (durationUs * 0.034f) / 2.0f;
}

void moveForward()
{
    in1 = 1;
    in2 = 0;
    in3 = 1;
    in4 = 0;
}

void moveBackward()
{
    in1 = 0;
    in2 = 1;
    in3 = 0;
    in4 = 1;
}

void stopMotors()
{
    in1 = 0;
    in2 = 0;
    in3 = 0;
    in4 = 0;
}

int main()
{
    // PWM setup (1 kHz period = 1 ms)
    ena.period_ms(1);
    enb.period_ms(1);

    // Same speed for both motors
    ena.write(MOTOR_SPEED);
    enb.write(MOTOR_SPEED);

    echoTimer.start();

    printf("=== Object-Following Robot Started ===\r\n");
    fflush(stdout);

    while (true) {
        float distance = readDistance();

        if (distance < 0.0f) {
            printf("Distance: NO ECHO (timeout)\r\n");
            stopMotors();
        } else {
            printf("Distance: %d cm\r\n", (int)distance);

            if (distance < MIN_DIST) {
                moveBackward();
            } else if (distance > MAX_DIST) {
                moveForward();
            } else {
                stopMotors();
            }
        }
        fflush(stdout);

        // Wait 100 ms before next measurement
        thread_sleep_for(100);
    }
}
