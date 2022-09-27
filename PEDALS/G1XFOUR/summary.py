import json
'''
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
'''
f=open("summary.json","r");

data=json.loads(f.read())

f.close()

summary='{'

for e in data:
    f=e['FX']
    
    summary+='{\"'+f['n']+'\",'+str(f['id'])+',\"'+f['fn']+'\",'+str(f['ns'])+','+str(f['np'])+',{'
    for p in e['P']:
        summary+='{'+str(1 if p['p'] else 0)+','+str(p['mmax'])+','+str(p['mdef'])+','+'0'+',\"'+p['n']+'\"},'
    if f['np']<8:
        for i in range(f['np'],8):
            summary+='{0,0,0,0,\"-\"},'
    summary=summary[:len(summary)-1]+'},'

summary=summary[:len(summary)-1]+'}'