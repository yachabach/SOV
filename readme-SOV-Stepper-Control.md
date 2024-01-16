# SOV Stepper Motor Control

[Excellent Tutorial on Steppers](https://www.youtube.com/watch?v=7spK_BkMJys)

## Setting Current Limit

It is important to set a current limit on the stepper motor drivers to protect both stepper and driver.  That is set with a Trim Pot on the stepper driver board.  Setting the limit can be done in two ways:

- Measure Reference Voltage  
- Measure Actual Current  

### Measure Reference Voltage

This voltage (Vref) is measured between the trim pot set screw and ground.  That is applied to the formula:

Current Limit = Vref / (8 * rcs)

Where:

- Vref
  : reference voltage
- rcs
- : Value if current sensing resistors (0.1) on our boards

For a 1 amp current limit we need VRef = 0.8 volts

The initial reference voltage was 0.608 volts.   Turning the pot did not seem to have any effect.  This gives us a current limit of 0.75 amps.

## Control Notes

Since we are using this in a state machine, we cannot let the stepper logic block.

The speed of the stepper is determined by the delay between steps.  The tutorial offers that anything less than 300 microseconds causes the stepper to miss steps.