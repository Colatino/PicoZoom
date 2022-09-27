#ifndef PEDAL_H
#define PEDAL_H

#include <Arduino.h>

typedef enum {
  OPEN,
  PRESS,
  HOLD
} foot_switch_state_t;

typedef enum {
  RUNNING,
  IDLE,
  TAPPING,
  BUSY
} pedal_state_t;

class FootSwitch {
  int _pin;
  volatile bool _trigger;
  volatile foot_switch_state_t cur_state;
  volatile unsigned long _cur_time;
  unsigned long _time;
  foot_switch_state_t _state;

public:
  FootSwitch();

  void begin(int pin, int debounce_time) {
    _pin = pin;
    _trigger = false;
    _trigger_state = OPEN;
    _state = OPEN;
    _time = 0;
    _trigger_time = 0;
    _debounce_time = debounce_time;
    attachInterrupt(digitalPinToInterrupt(pin), foot_isr, CHANGE);
  }

  foot_switch_state_t task() {
    if (_trigger) {
      //Only valid if not holding the pushbutton
      if (_state != HOLD) {
        // Valid change in state
        if (_cur_time - _time >= _debounce_time) {
          _state = _cur_state;
          _time = _cur_time;
        }
      }
    } else {
      if (_state == PRESS) {
        // Pressing for more than 2 seconds activate HOLD state
        if (millis() - _time > 2000) {
          _state = HOLD;
          //Update _time??
          //_time=millis();
        }
      }
    }
    return _state;
  }

  void reset_state() {
    _state = OPEN;
  }

private:
  void foot_isr() {
    _trigger = true;
    _trigger_state = digitalRead(pin) ? OPEN : PRESS;
    _trigger_time = millis();
  }
};

class Pedal {
  FootSwitch* foots;
  int _num_pedals;
  foot_switch_state_t* state_array;
  pedal_state_t pedal_state;
  unsigned long _idle_enter_time;

public:
  Pedal(int* pins, int num_pedals, int debounce_time) {
    _idle_enter_time = 0;
    pedal_state = IDLE;
    _num_pedals = num_pedals;
    state_array = new foot_switch_state_t[num_pedals];
    foots = new FootSwitch[num_pedals];

    // Initialize foot pedals
    for (int i = 0; i < num_pedals; i++) {
      foots.begin(pins[i], debounce_time);
      state_array[i] = OPEN;
    }
  }

  void task() {
    for (int i = 0; i < _num_pedals; i++) {
      state_array[i] = foots[i].task();
    }
  }
};