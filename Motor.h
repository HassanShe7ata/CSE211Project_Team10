#ifndef MOTOR_H
#define MOTOR_H

#include "PinNames.h"
#include "drivers/DigitalOut.h"
#include "drivers/PwmOut.h"

/**
 * @file Motor.h
 * @brief Single DC motor driver abstraction for an H-bridge channel.
 *
 * The class controls one motor using:
 * - one PWM output for speed command
 * - two direction pins for forward/reverse selection
 */
class Motor {
public:
    /**
     * @brief Construct a motor interface.
     * @param pwmPin      PWM pin connected to the driver enable/speed input.
     * @param forwardPin  Digital pin connected to forward direction input.
     * @param reversePin  Digital pin connected to reverse direction input.
     */
    Motor(PinName pwmPin, PinName forwardPin, PinName reversePin);

    /**
     * @brief Command forward motion.
     * @param normalizedSpeed Speed command in range [0.0f, 1.0f].
     */
    void forward(float normalizedSpeed);

    /**
     * @brief Command reverse motion.
     * @param normalizedSpeed Speed command in range [0.0f, 1.0f].
     */
    void backward(float normalizedSpeed);

    /**
     * @brief Stop the motor immediately.
     */
    void stop();

private:
    PwmOut _speedPwmOutput;               // PWM duty cycle controlling motor speed
    DigitalOut _forwardDirectionControl;  // Forward direction control line
    DigitalOut _reverseDirectionControl;  // Reverse direction control line
};
#endif
