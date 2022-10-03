/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET 4         // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SSD1306 d;

bool state = true;
bool redraw = true;
volatile bool _trigger = false;
volatile unsigned long _trigger_time = 0;
unsigned long _time = 0;

void switch_isr() {
  _trigger_time = millis();
  _trigger = true;
}

void switch_task() {
  if (_trigger) {
    if (_trigger_time - _time > 250) {
      _time = _trigger_time;
      state = !state;
      redraw = true;
    }
  }
}

void setup() {
  pinMode(5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(5), switch_isr, FALLING);
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Init");
  Wire.setSDA(0);
  Wire.setSCL(1);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
}

void draw_effect(const char* text, bool _state) {
display.setTextColor(SSD1306_WHITE);
  // If effect is active, draw line first
  if (_state)
    display.fillRect(0, 3 * SCREEN_HEIGHT / 8, SCREEN_WIDTH, SCREEN_HEIGHT / 4, SSD1306_WHITE);

  // Text size variables
  int xscale = 5;
  int yscale = 5;
  uint16_t w, h;
  int16_t x1, y1;
  display.setTextSize(xscale, yscale);

  // Then try to draw the widest text possible (SCREEN_WIDTH-10)
  while (xscale >= 1 && yscale >= 1) {
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    Serial.printf("%d %d %d %d\r\n",xscale,yscale,w,h);
    if (w <= SCREEN_WIDTH - 10 && h <= SCREEN_HEIGHT) {
      break;
    }
    if (w >= SCREEN_WIDTH-10) {
      xscale--;
    }
    if (h > SCREEN_HEIGHT) {
      yscale--;
    }    
    display.setTextSize(xscale, yscale);
  }
  // Text position
  int16_t cursorx, cursory;
  cursorx = (SCREEN_WIDTH - w) / 2;
  cursory = (SCREEN_HEIGHT - h) / 2;

  // Draw a black bounding box
  display.fillRect(cursorx - 1, cursory, w, h, SSD1306_BLACK);

  // Centralize text
  display.setCursor(cursorx, cursory);
  display.println(text);
  if (!_state)
    display.fillRect(0, 3 * SCREEN_HEIGHT / 8, SCREEN_WIDTH, SCREEN_HEIGHT / 4, SSD1306_WHITE);
}

void display_task() {
  // Clear the buffer
  if (redraw) {
    display.clearDisplay();
    draw_effect("Delay", state);
    display.display();
    redraw = false;
  }
}

void loop() {
  switch_task();
  display_task();
}