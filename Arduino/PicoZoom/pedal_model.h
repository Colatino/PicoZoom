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

};