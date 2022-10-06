#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define TCA9548A true      // true if TCA9548A multiplexer is used
#define TCA9548A_ADDR 0x70  // Multiplexer I2C address

class Oled {
  int _bus;
  bool _redraw;
  Adafruit_SSD1306 _display;//(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
public:
  Oled();//(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  void begin();
  void begin(int bus);
  void draw_text(const char* text);
  void draw_effect(const char* fxname, bool state);
  void select_bus();
  void clear();
  void draw();
  void set_redraw();
  void draw_tempo(int tempo,const char* sufix);
};

#endif