#include "pedal.h"

class FootSwitch {
  int pin;
  volatile int cur_state;
  volatile unsigned long cur_time;
  int last_state;
  int last_time;

public:
  FootSwitch(int pin, int debounce_time) {
    _pin = pin;
    _last_state = HIGH;
    _cur_state = HIGH;
    _last_time = 0;
    _cur_time = 0;
    _debounce_time = debounce_time;
    attachInterrupt(digitalPinToInterrupt(pin), foot_isr, CHANGE);
  }

  bool changed() {
    // Changed state
    if (_cur_state != _last_state) {
      if (_cur_time - _last_time >= _debounce_time) {
        _last_time = _cur_time;
        _last_state = _cur_state;
        return true;
      }
    }
    return false;
  }

private:
  void foot_isr() {
    cur_state = digitalRead(pin);
    cur_time = millis();
  }
};

class Pedal {
  // Variáveis membro da classe
  // São inicializadas no startup do programa
  int ledPin;    // número do pino do LED
  long OnTime;   // milissegundos do tempo ligado
  long OffTime;  // milissegundos do tempo desligado

  // Essas mantém o estado atual
  int ledState;                  // ledState usada para guardar o estado do LED
  unsigned long previousMillis;  // vai guardar o último acionamento do LED

public:
  PiscaLed(int pin, long on, long off) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);

    OnTime = on;
    OffTime = off;

    ledState = LOW;
    previousMillis = 0;
  }
};