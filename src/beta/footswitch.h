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
 
#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H
#include <Arduino.h>

typedef enum {
  OPEN,
  PRESS,
  TAP,
  HOLD,
  HOLDB,
  TOGGLE,
  TEMPO,
  TEMPOB
} foot_switch_state_t;

class FootSwitch {
  int _pin;
  bool _trigger;
  foot_switch_state_t _trigger_state;
  unsigned long _trigger_time;
  unsigned long _time;
  foot_switch_state_t _state;
  int _debounce_time;
  unsigned long _tempo;
  bool _got_tempo;
public:

  FootSwitch();

  void begin(int pin, int debounce_time);
  foot_switch_state_t task();
  void set_trigger_state(unsigned long t_time);
  void reset_state();
  unsigned long get_tempo();
  bool got_tempo();
  void set_tempo_b();
};

#endif