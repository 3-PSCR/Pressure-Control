# Actuation Strategies for a 3-segment Pneumatic Soft Continuum Robot

This repo contains three separate folders with Arduino sketches.
They are designed to control the Actuation System and segments explained here: [3-pscr.github.io](3-pscr.github.io).

### 1. 3PGui

This interfaces with the [GUI for the soft robot](https://github.com/3-PSCR/GUI) over Serial. On reset, it starts with all chambers locked and awaits instructions from the GUI before controlling the robot. It includes control of the extra vertical degree of freedom - which uses a stepper motor to drive the base of the soft robot arm up and down.

### 2. PressureCycle-1

This runs a ore-defined pressure cycle on one zone of the robot. The zone can be selected in `definitions.h`, and the array of command pressures can be found at the top of `PressureCycle-1.ino`. It pressurises the segment to the required pressure, locks it, and then waits 0.5 seconds before moving on.

### 3. PressureCycle-3

This runs a ore-defined pressure cycle on a pre-defined list of zones within the robot. The zones can be selected in `PressureCycle-3.ino` by replacing the indices with those to be controlled. The array of command pressures can be found at the top of `PressureCycle-3.ino`. It waits until all the controlled chambers are at the required pressure, pauses for 0.5 seconds, and then moves on with the pressure cycle.