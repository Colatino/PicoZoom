# PicoZoom
A MIDI controller for Zoom pedals based on the Raspberry pi Pico.
 
This project is the microcontroler version of the [one](https://github.com/Colatino/ZeroPedal) I've built with a Raspberry Pi Zero

The purpose of this project is to build an auxiliary pedal controller to be used with Zoom multi-effects processors like the G1XFour (tested with this model) and be able to toggle individual effects on/off among other possible features.

This project wouldn't be possible without [zoom-zt2](https://github.com/mungewell/zoom-zt2) and [ZoomPedalFun](https://github.com/shooking/ZoomPedalFun).

## BILL OF MATERIALS
- 1 x Raspberry Pi Pico
- 5 x SSD1306 0.91" oled displays
- 1 x TC9548A
- 5 x SPST momentary footswitches
- 1 x female USB type A breakout board
- Some jumper wires
- Some box or case to contain everything - mine will be 3d printed and the files available on the case folder

## DEPENDENCIES
This project makes use of the following libraries:
- A custom version of [Adafruit_TinyUSB_Arduino](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) based on [rppicomidi's fork](https://github.com/rppicomidi/tinyusb/tree/pio-midihost) of [tinyusb](https://github.com/hathach/tinyusb)
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306) and its dependencies
- [Arduino MIDI](https://github.com/FortySevenEffects/arduino_midi_library)

## ROADMAP
- [x] Ensure USB communications
- [x] Detect pedal plug/unplug
- [x] Handle MIDI packets
  - [x] Get pedal model/vid/pid
  - [x] Get current patch
    - [x] Get current patch effects state (on/off)
    - [x] Set current patch effect state (on/off)
    - [x] Detect if there is a delay effect on patch
      - [x] Implement tap tempo
  - [x] Implement global tap tempo (global BPM)
- [x] Handle footswitch press
- [x] Handle OLEDs
- [ ] Create wiring diagram
- [ ] Write a step-by-step
- [ ] Record and publish sample videos
- [ ] Improve README
- [ ] Support other Zoom pedals
