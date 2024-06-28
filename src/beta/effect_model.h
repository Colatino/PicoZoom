#ifndef EFFECT_MODEL_H
#define EFFECT_MODEL_H

struct Parameter {
  bool pedal;
  int maxval;
  int defval;
  int curval = 0;
  char parname[9];
};

struct Effect {
  // Name of the effect
  char fxname[10];
  // ID of the effect
  long id;
  // Name of the file
  char filename[17];
  // Number of slots used by the effect
  byte nslots;
  // Number of parameters
  byte nparam;
  Parameter params[8];
};



#endif