#  PID Control

Author: Kyle Martin, 2019-11-3

## Summary
In this skill, we implemented a PID control loop where we only used proportional control.  We wired three LEDs to GPIO outputs, one red, one green, and one blue, and wired a microlidar to the ESP32 using UART connection.  If the distance read by the microlidar was below 50 centimeters, we turned the blue LED on.  If the distance was above 50 centimeters, we turned the red LED on.  If the distance was equal to 50 centimeters, we turned the green LED on.  In this scenario, we were the actuator of the system, trying to get as close to 50 centimeters from a wall as possible

## Sketches and Photos
![Image](./images/board.JPG)

## Modules, Tools, Source Used in Solution
- http://whizzer.bu.edu/briefs/design-patterns/dp-pid

## Supporting Artifacts
- Demo Video: https://drive.google.com/file/d/1eULtILkhsYk3odKt4sJnbfWufSe1UgWv/view?usp=sharing

-----

## Reminders
- Repo is private
