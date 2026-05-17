/**
 * @file Ultrasonic.h
 * @brief HC-SR04 ultrasonic distance sensor interface.
 *
 * The sensor is measured by:
 * 1) Sending a 10 us trigger pulse
 * 2) Timing how long the echo pin stays HIGH
 * 3) Converting pulse width to distance in centimeters
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "mbed.h"

/**
 * @class Ultrasonic
 * @brief Interrupt-based HC-SR04 distance measurement driver.
 *
 * Usage example:
 * @code
 * Ultrasonic frontSensor(PA_6, PA_7);  // Trigger pin, Echo pin
 * int distanceCm = frontSensor.getDistance();
 * @endcode
 */
class Ultrasonic {
public:
    /**
     * @brief Construct an ultrasonic sensor driver.
     * @param triggerPin Pin connected to sensor TRIG (DigitalOut).
     * @param echoPin    Pin connected to sensor ECHO (InterruptIn).
     */
    Ultrasonic(PinName triggerPin, PinName echoPin);
    
    /**
     * @brief Trigger a new measurement and return the distance.
     * @return Distance in centimeters, or -1 if a timeout occurs.
     */
    int getDistance();

private:
    DigitalOut _triggerOutput;        // TRIG output pin
    InterruptIn _echoInput;           // ECHO input pin (interrupt driven)
    Timer _echoPulseTimer;            // Measures ECHO pulse width
    volatile int _measuredDistanceCm; // Latest measured distance in centimeters
    
    /**
     * @brief ISR for ECHO rising edge.
     * Starts pulse-width timing.
     */
    void onEchoRise();
    
    /**
     * @brief ISR for ECHO falling edge.
     * Stops timing and computes distance.
     */
    void onEchoFall();
};

#endif // ULTRASONIC_H
