# dcs-bios-universal-panel
A repo to hold all my Arduino code for my DCS panel

# Overview
The goal of this project is to make a Arduino that connects to the game DCS World.
For output a simple 16x2 lcd is used.
For input a combination of 16 buttons, one LED and 5 KY-040 Rotary Encoders are used.
The plan is to put all the hardware in a box so that it can be easily stored/used. this will also include a PCB to connect everything to the Arduino.

Much of this project is still in Dutch and will be translated over time.

I have make a basic layout of the final cable layout design, this is work in progress and a electronic diagram will added the future.
![Image of Arduino circuit layout]("/commpanel LCD/PinSchema.png")

The version of dcs-bios I have is modified to use dynamic inputs, wich was made by [Blue73](https://forum.dcs.world/topic/197601-dcs-bios-dynamic-mapping-based-on-aircraft-type-code/). Extra modyfication I have made to this is to allow Encoders to also use dynamic decArg & incArg. If needed I also plan to make a modification of the led class to also accep dynamic output.

## How to use
In terms of usability, a lot of inspiration is taken from the Youtube video from [John Gardner](https://www.youtube.com/watch?v=bt69aoobHJ8).
Controlling the display is pretty straitforward, the only thing you have to remember is what action each key has in wich profile.
Controlling what profile is currently used is based o 2 things: first is what aircraft is currently being used, this is decided by DCS itself; Second is the Encoder 5, this one controls what submenu is currently selected, the current submenu is also displayed at the top right of the lcd.
