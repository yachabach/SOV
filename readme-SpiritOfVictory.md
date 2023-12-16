# Spirit Of Victory Display Project

This project consists of:

- Platter - holds the art piece
- Motor and gear system - rotates the platter
- Controller - Arduino based hardware and software for motor control
- User Interface  
  - Button
  - Status Light  
  
## User Interface

### User Button

---
One button allows user interaction.  It responds to 3 user actions:

- **Double Push** (< 0.5") - [Program Platter Travel](#programming-platter-travel-limits)
- **Single Push** - [Start/Stop/Set Travel Limit](#startstopset-travel-limit)
- **Long Push** (> 0.5") - [Rotate platter to home](#rotate-platter-to-home)

### Programming Platter Travel Limits  

---
The platter can be programmed to reverse direction when reaching a travel limit.  

1. **Double Push** the user button.  

 > The controller enters programming mode.  The status light illuminates steady.  The platter rotates to ***Home***, pauses, then starts to rotate clockwise.  When the platter reaches the desired clockwise travel limit...

2. **Single Push** the user button.  

 > The clockwise travel limit is saved and the platter turns counter-clockwise.  When the platter reaches the desired counter-clockwise travel limit...

3. **Single Push** the user button.  

 > The counter-clockwise travel limit is saved, and the platter returns to ***Home*** and stops.  The controller exits the programming mode and the status light turns off.

The program is now stored in EEPROM memory.  If power is removed, the program will be recovered on the next power-up.

If there is no travel limit program, the platter will rotate clockwise continuously.

#### !!! If the user wishes to exit the programming mode before completing a program  

4. **Long Push** the user button.  

 > The platter returns **Home**, the new program is discarded.  If a previous program existed, it is retained.

### Start/Stop/Set Travel Limit

---
A single short button push causes the following action depending on the platter:  

- Platter is not turning - **Start**
- Platter is turning - **Stop**
- Platter is turning in progamming mode - **Set Travel Limit** (See [Programming Platter Travel Limits](#programming-platter-travel-limits))

If there is no travel limit set, the platter will rotate clockwise continuously.

If the platter is stopped while running a program, the current direction and travel limit is stored.  When the platter is started again, it resumes travel from where it left off.

### Rotate Platter to Home

---
Use this button to rotate the platter to it's **Home** position.  It can be used to:

- Center the art piece for static viewing
- Exit travel limit programming without saving
- Recover a "Lost" condition

A flashing status light indicates that the platter is "Lost".  This means that the controller doesn't know it's location relative to rotation limits and has stopped.  It cannot continue until it is sent **Home**.  A Single Long Push authorizes the controller to rotate to **Home**.  At **Home**, the status light will extinguish and the unit can be restarted with a Single Short Push.

## Status Light

A single LED status light will illuminate in two patterns:  

- Steady - Controller is in "Programming Mode" (See [Programming Platter Travel Limits](#programming-platter-travel-limits))  
- Flashing - Controller is "Lost" (See [Rotate Platter to Home](#rotate-platter-to-home))
