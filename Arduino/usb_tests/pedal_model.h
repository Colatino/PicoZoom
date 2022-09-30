#ifndef PEDAL_MODEL_H
#define PEDAL_MODEL_H

struct Parameter{
  bool pedal;
  int maxval;
  int defval;
  int curval=0;
  char parname[9];
};

struct Effect{
  char fxname[10];
  long id;
  char filename[17];
  byte nslots;
  byte nparam;
  Parameter params[8];
};

class Model{
  int _n_effects;
  int _cur_effect;
  Effect* effects;

  public:
  Model();

  void init(int neff){
    _n_effects=neff;
    effects=new Effect[neff];
  }
  void add_effects(Effect* new_effects){
    memcpy(effects,new_effects,sizeof(new_effects));
  }

  int get_n_effects(){
    return _n_effects;
  }
};

#endif