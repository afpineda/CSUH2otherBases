# User manual

## Power on

The steering wheel will get power as soon as it gets connected to the sim base.

## Bluetooth pairing

The steering wheel will enter *Bluetooth discovery mode*
automatically when no host computer is connected.

In Windows:

- Enter the control panel.

- Enter the "Bluetooth and other devices" page.

- Turn Bluetooth on.

- Click "Add bluetooth device".

- The steering wheel will show up as "**CSUH sim wheel**".
  If the device does not show up, ensure it has power,
  it is in range,
  and it is not already connected to another computer (or phone/tablet).

- Connect.

The pairing procedure is not needed more than once.
The computer will automatically connect to the steering wheel from now on,
when available.

The CSUH will appear to the host computer as a joystick or gamepad device.

## Select the working mode for the `LT` and `RT` buttons

Those buttons may be configured into one of several modes at any time.
Click the rotary encoder builtin push button
and the `Y` button at the same time (and no other button)
to select the next mode.

The [companion app][ref1] is also capable of selecting a specific mode.

## Regular buttons

In this mode,
`LT` and `RT` will be reported to the host computer according to their label,
just like any other button.

## Alternate mode

With alternate mode selected,
hold `LT` or `RT` while pressing any other button (or shift lever),
rotating the funky switch or rotating the additional rotary encoder.
Those inputs will be reported as alternate ones to the host computer,
thus duplicating the number of effective inputs.

For example, you may map the `A` button to "ignition" and `LT+A`
(the same as `RT+A`) to "start engine".

## F1-style clutch

With this mode selected, `LT` and `RT` will act as clutch paddles
(or "clutch buttons"):

- When both buttons are released, the clutch is fully disengaged.

- When both buttons are hold, the clutch is fully engaged.

- When one and only one of these buttons is hold,
  the clutch will get half-engaged to a certain bite point. See below.

## Launch control

It works in a similar way to the F1-style clutch,
but there is a "master" button and a "slave" button.

## Bite point calibration

Ensure clutch mode or launch control is selected.

- In F1-style mode, Hold one and only one clutch button.
  In launch control mode, hold the slave button.

- Rotate the funky switch clockwise or counter-clockwise
  to increase or decrease the bite point.

You may also set a bite point through the [companion app][ref1]
which can load and save your preferences to a file, too.

The current bite point will be saved to flash memory
after a delay of 15 seconds.

### Calibration procedure

Bite point calibration should be performed for each car, before race starts.
However, a bite point of 40%, more or less,
should work for most cars
if you don't like to repeat the calibration procedure each time.

- Move the car to a flat surface with no slope.

- Ensure the engine is always on.
  It is easy to stall the engine in this process.

- Hold one (and only one) clutch button and rotate
  the funky switch to the point where the car does not move,
  nor the engine gets stalled.

- Slowly, rotate the funky switch in the opposite direction
  to the point where the car starts moving. That's the correct bite point.

- Release the clutch button.

No need to repeat the calibration procedure
unless another car or game is selected.

#### Show current bite point

Your game should show the bite point (while holding any clutch button)
in some kind of graphic.
If not, enter the "properties" page of the "CSUH sim wheel"
at the devices panel.
The clutch is shown as an analog joystick axis.

The [companion app][ref1] will show the current bite point, too.

### How to take the start in F1-style clutch mode

- In the starting grid, select neutral (N) gear and start the engine.

- Hold both clutch buttons.

- Enter 1st gear (2nd gear may work better in some cars).

- Press the gas pedal to full extent.

- Wait for the semaphore lights to turn off (they turn green in some games).

- Release one and only one clutch button.

- Let the car go until a velocity of 50 km/h (31 MPH), more or less, is reached.

- Release the other clutch button.

### How to take the start in launch control mode

- In the starting grid, select neutral (N) gear and start the engine.

- Hold both clutch buttons.

- Enter 1st gear (2nd gear may work better in some cars).

- Press the gas pedal to full extent.

- Wait for the semaphore lights to turn off (they turn green in some games).

- Release the **master** button.

- Let the car go until a velocity of 50 km/h (31 MPH),
  more or less, is reached.

- Release the **slave** button.

[ref1]: https://github.com/afpineda/SimWheelESP32Config
