# CSE211Project_Team10

Embedded object-following robot car built on STM32 NUCLEO-F401RE with HC-SR04 distance sensing and dual DC motor control.

## Quick Launch

1. Connect hardware:
	- HC-SR04: TRIG D9, ECHO D10
	- Motor A: PWM D5, FWD D3, REV D4
	- Motor B: PWM D6, FWD D7, REV D8
2. Build and flash from project root:

```bash
mbed compile -m NUCLEO_F401RE -t GCC_ARM --flash
```

3. Start the board. The rover drives forward when distance is greater than 15 cm and stops at or below 15 cm.

## Demonstration Video

<video controls width="760" preload="metadata">
	<source src="Video%20Robot%20Car%20Follower.mp4" type="video/mp4">
	Your browser or GitHub view does not support embedded playback.
</video>

Fallback: [Watch the project demo](Video%20Robot%20Car%20Follower.mp4)
