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
  _pin = pin; // Pin associated with the footswitch
  _trigger = false; // Holds the ISR state
  _state = OPEN; // Current state of the footswitch
  _time = 0; // Time between presses
  _trigger_time = 0; // Last trigger press
  _debounce_time = debounce_time; // Debounce constant
  _tempo = 0; // Calculated tempo
  _got_tempo = false; // If tempo calculation was completed
  pinMode(_pin, INPUT_PULLUP); // Sets the pin up
}

// Manages all the presses on the footswitch
// It is called inside the main loop (core 0)
foot_switch_state_t FootSwitch::task() {
  // If the footswitch is open
  if (_state == OPEN) {
    // Check if there was an interrupt press
    if (_trigger) {
      // Resets trigger
      _trigger = false;
      // Checks for debounce
      if (_trigger_time - _time >= _debounce_time) {
        _time = _trigger_time;
        // Switch was pressed
        _state = PRESS;
      }
    }
  } else if (_state == PRESS) {
    // Swtich is pressed
    if (!digitalRead(_pin)) {
      // Pressed for more than 1s
      if (millis() - _time >= 1000) {
        // Enter tap state and sets is variables
        _state = TAP;
        _time = millis();
        _tempo = 0;
      }
    } else {
      // Pressed for less than 1s
      if (millis() - _time > _debounce_time) {
        // Resets state and only toggle the effect
        reset_state();
        return TOGGLE;
      }
    }
    // If in TAP mode, changes to HOLD mode (calculates tempo)
  } else if(_state==TAP){
    _state=HOLD;
    // Stores the current _time to calculate tempo
    _time=millis();
  }else if (_state == HOLD) {
    // If switch was pressed
    if (_trigger) {
      // Resets trigger
      _trigger = false;
      // Calculates current tempo
      unsigned long tempo = _trigger_time - _time;
      // Tempo HAS to be larger than debounce_time
      if (tempo >= _debounce_time) {        
        // Tempo has to be smaller than 3s
        if (tempo < 3000) {
          _time = _trigger_time;
          _tempo = tempo;
          // Confirmation that a tempo calculation was successful
          _got_tempo = true;
        }
      }
      // Swtich is not pressed ...
    } else {
      // ... for more than 3s ...
      if (millis() - _time > 3000) {
        // ... and tempo is not 0 ...
        if (_tempo > 0) {
          // Resets states
          reset_state();
          // Return TEMPO state (to inform the firmware that tempo calculation is complete)
          return TEMPO;
        }
      }
    }
  } else if (_state == HOLDB) {
    // If switch was pressed
    if (_trigger) {
      // Resets trigger
      _trigger = false;
      // Calculates current tempo
      unsigned long tempo = _trigger_time - _time;
      // Tempo HAS to be larger than debounce_time
      if (tempo >= _debounce_time) {
        // Tempo has to be smaller than 3s
        if (tempo < 3000) {
          _time = _trigger_time;
          _tempo = tempo;
          // Confirmation that a tempo calculation was successful
          _got_tempo = true;
        }
      }
      // Swtich is not pressed ...
    } else {      
      // ... for more than 3s ...
      if (millis() - _time > 3000) {        
        // ... and tempo is not 0 ...
        if (_tempo > 0) {
          // Resets states
          reset_state();
          // Return TEMPO state (to inform the firmware that tempo B calculation is complete)
          return TEMPOB;
        }
      }
    }
  }
  // Returns current state
  return _state;
}

void FootSwitch::reset_state() {
  _state = OPEN;
  _time = millis();
  _trigger = false;
  _got_tempo = false;
}

// Informs calculated tempo
unsigned long FootSwitch::get_tempo() {
  _got_tempo = false;
  return _tempo;
}

// Check if tempo was calculated
bool FootSwitch::got_tempo() {
  return _got_tempo;
}

// Sets state of the trigger (used by ISR)
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