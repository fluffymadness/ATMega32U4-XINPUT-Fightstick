# ATMega32U4-XINPUT-Fightstick
This one is a working Xinput Emulator Sketch flashable via Arduino IDE. I personally use it on a pro micro clone microcontroller that can be bought for 2-3$ on aliexpress. 

This is based on the work of the kade device team. 
I made some modifications to make it flashable via Arduino IDE, added things like fake analog and rewrote the input handling, to make it, in my opinion, more easily readable/modifiable.


Here is the link to the original work:
https://github.com/bootsector/XInputPadMicro

The Code itself has proper Button-Debounce, you can configure the miliseconds for the it via #define MILLIDEBOUNCE.

There are 2 Modes of input.

You can switch seamlessly between the 2 modes by pressing START+SELECT. 

- Digital Only
- Fake Analog (Digital Movement is mapped to L-Analog)

## Building Instructions

- Download Arduino IDE, 

- Download the Bounce2 Library inside the Arduino IDE
- Download Arduino Lufa from https://github.com/Palatis/Arduino-Lufa and follow the instructions on it's repository
- Build and Flash for your ATMEGA32U4 Board
- Have Fun

## Pinmapping

Here is the Pinnumbers to Button Mapping for Connecting the actual physical cables to a Pro Micro.

​    joystickUP.attach(0,INPUT_PULLUP);

​    joystickDOWN.attach(1,INPUT_PULLUP);

​    joystickLEFT.attach(2,INPUT_PULLUP);

​    joystickRIGHT.attach(3,INPUT_PULLUP);

​    buttonA.attach(4,INPUT_PULLUP);

​    buttonB.attach(5,INPUT_PULLUP);;

​    buttonX.attach(6,INPUT_PULLUP);

​    buttonY.attach(7,INPUT_PULLUP);

​    buttonLB.attach(9,INPUT_PULLUP);

​    buttonRB.attach(8,INPUT_PULLUP);

​    buttonLT.attach(14,INPUT_PULLUP);

​    buttonRT.attach(10,INPUT_PULLUP);

​    buttonSTART.attach(15,INPUT_PULLUP);

​    buttonSELECT.attach(16,INPUT_PULLUP);

​    buttonHOME.attach(18,INPUT_PULLUP);

### Credits

Many thanks to the creators of the original project (https://github.com/bootsector/XInputPadMicro)

Dean Camera for the LUFA Library

zlittell, msf-xinput was very helpful for starting this kind of things.

thomasfredericks for the Bounce2Lib.
