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
 
#include "footswitch.h"

FootSwitch::FootSwitch() {}

void FootSwitch::begin(int pin, int debounce_time) {
  _pin = pin;
  _trigger = false;
  _state = OPEN;
  _time = 0;
  _trigger_time = 0;
  _debounce_time = debounce_time;
  _tempo = 0;
  _got_tempo = false;
  pinMode(_pin, INPUT_PULLUP);
}

foot_switch_state_t FootSwitch::task() {
  if (_state == OPEN) {
    if (_trigger) {
      _trigger = false;
      if (_trigger_time - _time >= _debounce_time) {
        _time = _trigger_time;
        _state = PRESS;
      }
    }
  } else if (_state == PRESS) {
    // Pressing for more than 1 second activate HOLD state
    if (!digitalRead(_pin)) {
      if (millis() - _time >= 1000) {
        _state = TAP;
        _time = millis();
        _tempo = 0;
      }
    } else {
      if (millis() - _time > _debounce_time) {
        reset_state();
        return TOGGLE;
      }
    }
  } else if(_state==TAP){
    _state=HOLD;
    _time=millis();
  }else if (_state == HOLD) {
    // Do nothing - wait to reset after task is done
    if (_trigger) {
      _trigger = false;
      unsigned long tempo = _trigger_time - _time;
      if (tempo >= _debounce_time) {
        if (tempo < 3000) {
          _time = _trigger_time;
          _tempo = tempo;
          _got_tempo = true;
        }
      }
    } else {
      if (millis() - _time > 3000) {
        if (_tempo > 0) {
          reset_state();
          return TEMPO;
        }
      }
    }
  } else if (_state == HOLDB) {
    // Do nothing - wait to reset after task is done
    if (_trigger) {
      _trigger = false;
      unsigned long tempo = _trigger_time - _time;
      if (tempo >= _debounce_time) {
        if (tempo < 3000) {
          _time = _trigger_time;
          _tempo = tempo;
          _got_tempo = true;
        }
      }
    } else {
      if (millis() - _time > 3000) {
        if (_tempo > 0) {
          reset_state();
          return TEMPOB;
        }
      }
    }
  }
  return _state;
}

void FootSwitch::reset_state() {
  _state = OPEN;
  _time = millis();
  _trigger = false;
  _got_tempo = false;
}

unsigned long FootSwitch::get_tempo() {
  _got_tempo = false;
  return _tempo;
}

bool FootSwitch::got_tempo() {
  return _got_tempo;
}

void FootSwitch::set_trigger_state(unsigned long t_time) {
  if (!digitalRead(_pin)) {
    _trigger = true;
    _trigger_time = t_time;
  }
}

void FootSwitch::set_tempo_b() {
  _state = TEMPOB;
  _trigger_time = millis();
  _time = _trigger_time;
  _got_tempo = false;
}