/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 André Colatino (https://github.com/Colatino/picozoom)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the PicoZoom project.
 */
 
#include "oled.h"

// Constructor
Oled::Oled() {}
//: _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void Oled::begin() {
  _display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  _display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

void Oled::begin(int bus) {
  _bus = bus;
  _display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  Oled::select_bus();

  if (!_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.printf("Failed to initialize oled on bus %d\r\n",bus);
  }
  //Serial.println("Started");
}

void Oled::select_bus() {
  if (TCA9548A) {
    //Serial.printf("Selecting bus %d\r\n",_bus);
    Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
    Wire.write(1 << _bus);         // send byte to select bus
    Wire.endTransmission();
  }
}

void Oled::draw_effect(const char *fxname, bool state) {
  //Serial.printf("Drawing effect on display at bus %d\r\n",_bus);
  if (state)
    _display.fillRect(0, 3 * SCREEN_HEIGHT / 8, SCREEN_WIDTH, SCREEN_HEIGHT / 4, SSD1306_WHITE);

  if (strcmp(fxname, "Bypass") != 0)
    Oled::draw_text(fxname);

  if (!state)
    _display.fillRect(0, 3 * SCREEN_HEIGHT / 8, SCREEN_WIDTH, SCREEN_HEIGHT / 4, SSD1306_WHITE);
}

void Oled::draw_text(const char *text) {
  _display.setTextColor(SSD1306_WHITE);

  // Text size variables
  int xscale = 5;
  int yscale = 3;
  uint16_t w, h;
  int16_t x1, y1;
  _display.setTextSize(xscale, yscale);

  // Then try to draw the widest text possible (SCREEN_WIDTH-10)
  while (xscale >= 1 && yscale >= 1) {
    _display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    if (w <= SCREEN_WIDTH - 10) {
      break;
    }
    if (w >= SCREEN_WIDTH - 10) {
      xscale--;
    }
    // if (h > SCREEN_HEIGHT) {
    //   yscale--;
    // }
    _display.setTextSize(xscale, yscale);
  }
  // Text position
  int16_t cursorx, cursory;
  cursorx = (SCREEN_WIDTH - w) / 2;
  cursory = (SCREEN_HEIGHT - h) / 2;

  // Draw a black bounding box
  _display.fillRect(cursorx - 1, cursory, w, h, SSD1306_BLACK);

  // Centralize text
  _display.setCursor(cursorx, cursory + 1);
  _display.println(text);
}

void Oled::draw_tempo(int tempo, const char *sufix) {
  String helper = String(tempo);
  helper.concat(" ");
  helper.concat(sufix);
  ////Serial.println(tempo);
  _display.setTextColor(SSD1306_WHITE);

  // Text size variables
  uint16_t w, h;
  int16_t x1, y1;
  _display.setTextSize(2);

  // Centralize text
  _display.setCursor(5, 0);
  _display.println(helper);
}

void Oled::clear() {
  _display.clearDisplay();
}

void Oled::draw() {
  Oled::select_bus();
  _display.display();
  //Serial.println("Drawn");
  _redraw = false;
}

bool Oled::get_redraw() {
  return _redraw;
}

void Oled::set_redraw() {
  _redraw = true;
}