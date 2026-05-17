#include "Ultrasonic.h"

#define ECHO_TIMEOUT_US 30000
#define TRIGGER_PULSE_US 10
#define US_PER_CM_DIVISOR 58.0f

Ultrasonic::Ultrasonic(PinName triggerPin, PinName echoPin)
    : _triggerOutput(triggerPin), _echoInput(echoPin), _measuredDistanceCm(-1)
{
    _triggerOutput = 0;

    _echoInput.rise(callback(this, &Ultrasonic::onEchoRise));
    _echoInput.fall(callback(this, &Ultrasonic::onEchoFall));
}

int Ultrasonic::getDistance() {
    _measuredDistanceCm = -1;

    _echoPulseTimer.stop();
    _echoPulseTimer.reset();

    // Send 10 us trigger pulse to start a ranging cycle.
    _triggerOutput = 1;
    wait_us(TRIGGER_PULSE_US);
    _triggerOutput = 0;

    // Poll until ISR stores a distance or timeout expires.
    int remainingTimeoutUs = ECHO_TIMEOUT_US;
    while (_measuredDistanceCm < 0 && remainingTimeoutUs > 0) {
        wait_us(10);
        remainingTimeoutUs -= 10;
    }

    return _measuredDistanceCm;
}

void Ultrasonic::onEchoRise() {
    _echoPulseTimer.reset();
    _echoPulseTimer.start();
}

void Ultrasonic::onEchoFall() {
    _echoPulseTimer.stop();

    auto echoPulseDuration = _echoPulseTimer.elapsed_time();
    float echoPulseWidthUs =
        std::chrono::duration_cast<std::chrono::microseconds>(echoPulseDuration).count();

    _measuredDistanceCm = (int)(echoPulseWidthUs / US_PER_CM_DIVISOR);

    _echoPulseTimer.reset();
}
