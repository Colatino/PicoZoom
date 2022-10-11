# PicoZoom
A MIDI controller for Zoom pedals based on the Raspberry pi Pico.
 
This project is the microcontroler version of the [one](https://github.com/Colatino/ZeroPedal) I've built with a Raspberry Pi Zero

The purpose of this project is to build an auxiliary pedal controller to be used with Zoom multi-effects processors like the G1XFour (tested with this model) and be able to toggle individual effects on/off, add a tap-tempo functionality, among other possible features.

This project wouldn't be possible without [zoom-zt2](https://github.com/mungewell/zoom-zt2) and [ZoomPedalFun](https://github.com/shooking/ZoomPedalFun).

## HOW TO BUILD ONE

### CODE
You'll have to install the [Arduino IDE](https://www.arduino.cc/en/software) and add the [Arduino-pico core](https://github.com/earlephilhower/arduino-pico) to it, follow the [installation instructions](https://arduino-pico.readthedocs.io/en/latest/install.html) on the documentation.

This project makes use of the following libraries:
- A custom version of [Adafruit_TinyUSB_Arduino](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) based on [rppicomidi's fork](https://github.com/rppicomidi/tinyusb/tree/pio-midihost) of [tinyusb](https://github.com/hathach/tinyusb)
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306) and its dependencies
- [Arduino MIDI](https://github.com/FortySevenEffects/arduino_midi_library)

Copy the custom [Adafruit_TinyUSB_Arduino](https://github.com/Colatino/PicoZoom/tree/main/lib/Adafruit_TinyUSB_Library) library to you Arduino/libraries folder, be careful if you already have the original one installed as it will be overwritten.

You might want to change these lines to match your setup:
```cpp
#define NUM_PEDALS 5 // Number of switches and screens - for now each switch has to be linked to an oled screen
int switch_pins[] = { 5, 6, 7, 8, 9 }; // GPIO pins on the pico the switches are attached to 
FootSwitch footswitch[NUM_PEDALS];

int buses[] = { 7, 6, 5, 4, 3 }; // Buses on the TCA9548A the oled screens are attached to
Oled oleds[NUM_PEDALS];
```

For the G1XFour (possibly also the G1Four) no other line has to be changed.

On the IDE, go to Tools -> Board and select the Raspberry Pi Pico board (or other compatible) and select the appropriate comm Port. 

Then again Tools -> CPU Speed and set it to 120 MHz (this is crucial for the USB over PIO) and Tools -> USB Stack and set it to Adafruit TinyUSB.

Click upload and it will be compiled and sent to the board. 

If the IDE can't find the board, unplug it, hold the Bootsel button and plug it again. The PC will recognize it as a flash drive then on the IDE go to Sketch -> Export compiled binary and, after it is compiled, go to the sketch's folder and into the build folder look for the .UF2 file and drag and drop it on the Pico drive, all done.

### HARDWARE

To build it you'll need the following (G1XFour/G1Four):
- 1 x Raspberry Pi Pico (or a RP2040 based board)
- 5 x SSD1306 0.91" oled displays
- 1 x TC9548A
- 5 x SPST momentary footswitches
- 1 x female USB type A breakout board
- Some jumper wires
- Some box or case to contain everything - mine will be 3d printed and the files available on the case folder

Follow this wiring diagram (change GPIO if needed)
![image](https://github.com/Colatino/PicoZoom/blob/main/Fritzing/wiring.png)

I recommend not to use headers but instead solder the jumper wires to the TCA9548A as it may, sometimes, get loose.

After all the connections are made, I recommend that before you assembly the controller, test it with the Pedal as it will be harder to debug later.

If all goes well, just put everything inside the box you chose and you're done!

## How to use

Power the controller through the Pico's micro USB port (5V required, 1+ amps prefered) then connect it to the Pedal's own micro USB. The controller will provide power to the pedal and then it will read the pedal's data and show the current patch effects on the OLED screens. 

### Toggling effects

To toggle individual effects on/off just step on the corresponding switch, an active effect will have its name visible like -DELAY-, while an inactive one will have a strikethrough like ~~-DELAY-~~.

This is a video showing how it behaves when plugging and toggling effects:
[![Sample video](https://img.youtube.com/vi/8XPy8AvLA0o/maxresdefault.jpg)](https://www.youtube.com/watch?v=8XPy8AvLA0o)

### Tap tempo/BPM

The tap tempo feature works when you have a delay effect on the current patch. 
To use it you'll have to hold its corresponding footswitch for at least 1 second, the OLED screen will then show the message *TAP TEMPO*, then you just have to press/tap the switch at the desire interval and the controller will show the current measured time between taps. When you're satisfied just stop tapping and wait for 3 seconds, the controller will send the measured interval to the pedal and will go back to the normal functions, showing the effect's name again. See the video bellow for a sample of how it works:

[![Tap tempo sample](https://img.youtube.com/vi/NjomxG56lNE/maxresdefault.jpg)](https://youtu.be/NjomxG56lNE)


The global BPM feature works similarly but will ONLY be enabled when holding on any switch the DOES NOT correspond to a delay effect for 1 second. After activated a message *GLOBAL BPM* will show on the screen, then you just have to press/tap the switch at the desire interval and the controller will calculate the BPMs corresponding to that interval and show it on the screen. When you're satisfied just stop tapping and wait for 3 seconds, the controller will send the measured interval to the pedal and will go back to the normal functions, showing the effect's name again. See the video bellow for a sample of how it works:

[![Tap tempo sample](https://img.youtube.com/vi/VsWXhOvHJVc/maxresdefault.jpg)](https://youtu.be/VsWXhOvHJVc)

### ROADMAP
- [x] Ensure USB communications
- [x] Detect pedal plug/unplug
- [x] Handle MIDI packets
  - [x] Get pedal model/vid/pid
  - [x] Get current patch
    - [x] Get current patch effects state (on/off)
    - [x] Set current patch effect state (on/off)    
  - [x] Implement tap tempo
  - [x] Implement change global BPM
- [x] Handle footswitch press
- [x] Handle OLEDs
- [x] Create wiring diagram
- [x] Record and publish sample videos
- [x] Write a step-by-step guide
- [ ] Improve README
- [ ] Support other Zoom pedals by default?
- [ ] Add a battery?
