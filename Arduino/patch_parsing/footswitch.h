#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H
#include <Arduino.h>

typedef enum {
  OPEN,
  PRESS,
  HOLD,
  TOGGLE,
  TEMPO
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
};

#endif