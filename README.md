# dcs-bios-universal-panel
A repo to hold all my Arduino code for my DCS panel

# Overview
The goal of this project is to make a Arduino that connects to the game DCS World.
For output a simple 16x2 lcd is used.
For input a combination of 16 buttons, one LED and 5 KY-040 Rotary Encoders are used.
The plan is to put all the hardware in a box so that it can be easily stored/used. This will also include a PCB to connect everything to the Arduino Mega.

Much of this project is still in Dutch and will be translated to English over time.

I have made a basic layout of the final cable layout design, this is work in progress and a electronic diagram will be added the future.
![Image of Arduino circuit layout](https://raw.githubusercontent.com/EwoutHeb/dcs-bios-universal-panel/main/commpanel%20LCD/PinSchema.png)
This number on the breadboard that the cable conntects to is what port the cable is connected to on the Arduino Mega.

The version of dcs-bios I have is modified to use dynamic inputs, wich was made by [Blue73](https://forum.dcs.world/topic/197601-dcs-bios-dynamic-mapping-based-on-aircraft-type-code/). Extra modifications I have made to this will also allow Encoders to also use dynamic decArg & incArg. If needed I also plan to make a modification of the led class to also accept dynamic output.

## How to use
In terms of usability, a lot of inspiration is taken from the Youtube video from [John Gardner](https://www.youtube.com/watch?v=bt69aoobHJ8).
Controlling the display is pretty straitforward, the only thing you have to remember is what action each key has in wich profile.
Controlling what profile is currently used is based on 2 things: first is what aircraft is currently being used, this is checked in the program itself and information about this is recieved by the game itself; Second is the Encoder 5, this one controls what submenu is currently selected, the current submenu is also displayed at the top right of the lcd.
