# wheel-adapter
Adruino-based adapter to convert steering wheel resistive buttons into USB keyboard key presses

## Important disclaimer
All this work is just compilation of other works taken from [pccar.ru](http://pccar.ru) forum, with some minor
refactoring of the code.

## Hardware
Hardware part of the adapter is based on any Arduino based on ATmega32u4, e.g. Leonardo, Pro Micro etc. Regular Arduinos on ATmega 328 won't work as they cannot simulate USB HID devices.

### Connection to resistive buttons
Arduino should have pins A3 and GND connected to output of resistive wheel buttons, it's USB port can be connected to your CarPC, so wheel buttons press will simulate USB keyboard button press.


## Software

### Types of software
There are 2 major releases of wheel adapter 
 - first release (referenced as "old") requires Arduino IDE base files replacement and works only for Arduino IDE 1.0.5 or 1.6.5
 - second release (referenced as "new") does not require changes to Arduino IDE base files, but requires Tablet library to be installed (also in this repo). Any Arduino IDE newer than 1.6.8 can be used to compile.

Info (in Russian) on old wheel adapter can be found [here](http://pccar.ru/showpost.php?p=277286&postcount=182) and [here](http://pccar.ru/showpost.php?p=319975&postcount=307)

Info (in Russian) on new wheel adapter can be found [here](http://pccar.ru/showpost.php?p=366382&postcount=669)

### Folder structure:

├── libraries

│   └── Tablet	- Tablet library for new wheel adapter

└── sketches

    ├── wheel-adapter - Sketch for new wheel adapter

    ├── wheel-adapter-old - Sketch for old wheel adapter

    │   └── patches - patches for base Arduino IDE files

    │       ├── arduino-1.0.5

    │       └── arduino-1.6.5

    └── wheel-buttondump - Sketch for getting constant values for your own car resistive buttons

### Adaptation of constants for your car

Values of constants in the code are for Ford Escape 08-12, but you can get the values by yourself, by flashing sketch wheel-buttondump and observing values on serial port on button press.
```c
#define NOBUTTON 256
#define PLAY 432
#define NEXT 652
#define PREV 538
#define VOLUP 772
#define VOLDOWN 896
```
