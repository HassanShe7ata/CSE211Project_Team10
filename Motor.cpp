#include "Motor.h"

/**
 * @file Motor.cpp
 * @brief Implementation of the Motor class.
 */

Motor::Motor(PinName pwmPin, PinName forwardPin, PinName reversePin)
    : _speedPwmOutput(pwmPin),
        _forwardDirectionControl(forwardPin),
        _reverseDirectionControl(reversePin)
{
    _speedPwmOutput.period_ms(1);  // 1 kHz PWM period
    stop();                        // Start in safe stopped state
}

void Motor::forward(float normalizedSpeed) {
    if (normalizedSpeed > 1.0f) normalizedSpeed = 1.0f;
    if (normalizedSpeed < 0.0f) normalizedSpeed = 0.0f;

    _forwardDirectionControl = 1;
    _reverseDirectionControl = 0;
    _speedPwmOutput = normalizedSpeed;
}

void Motor::backward(float normalizedSpeed) {
    if (normalizedSpeed > 1.0f) normalizedSpeed = 1.0f;
    if (normalizedSpeed < 0.0f) normalizedSpeed = 0.0f;

    _forwardDirectionControl = 0;
    _reverseDirectionControl = 1;
    _speedPwmOutput = normalizedSpeed;
}

void Motor::stop() {
    _forwardDirectionControl = 0;
    _reverseDirectionControl = 0;
    _speedPwmOutput = 0.0f;
}
