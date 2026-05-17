# CSE211Project_Team10

Embedded object-following robot car built on STM32 NUCLEO-F401RE with HC-SR04 distance sensing and dual DC motor control.

The current firmware is modular:
- `main.cpp` contains the control loop and state decisions.
- `Ultrasonic.h/.cpp` handles HC-SR04 measurement.
- `Motor.h/.cpp` handles motor direction and PWM speed.

## Quick Launch

1. Connect hardware:
	- HC-SR04: TRIG D6, ECHO D7
	- Motor A: PWM D9, FWD D4, REV D5
	- Motor B: PWM D10, FWD D11, REV D12
2. Build and flash from project root:

```bash
mbed compile -m NUCLEO_F401RE -t GCC_ARM --flash
```

3. Start the board. Control behavior:
	- Distance < 15 cm: move backward
	- Distance 15 to 30 cm: stop
	- Distance > 30 cm: move forward
	- No echo/timeout: stop (safety)

## Demonstration Video

[Watch the project demo](Video%20Robot%20Car%20Follower.mp4)
