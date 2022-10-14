import time
from construct import *
import json5
import math
from pathlib import Path
#--------------------------------------------------
ICON = Struct(
    Const(b"ICON"),
    "length" / Int32ul,
    "data" / Bytes(this.length),
)

TXJ1 = Struct(
    Const(b"TXJ1"),
    "length" / Int32ul,
    "data" / Bytes(this.length),
)

TXE1 = Struct(
    Const(b"TXE1"),
    "length" / Int32ul,
    "description" / PaddedString(this.length, "ascii"),
)

INFO = Struct(
    Const(b"INFO"),
    "length" / Int32ul,
    "data" / Bytes(this.length - 4),
    "dspload" / Float32l,
)

DATA = Struct(
    Const(b"DATA"),
    "length" / Int32ul,
    "data" / Bytes(this.length),
)

PRMJ = Struct(
    Const(b"PRMJ"),
    "length" / Int32ul,
    "data" / Bytes(this.length),
)

PRME = Struct(
    Const(b"PRME"),
    "length" / Int32ul,
    "xml" / PaddedString(this.length, "ascii"),
)

ZD2 = Struct(
    Const(b"ZDLF"),
    "length" / Int32ul,

    "hexdump" / HexDump(Peek(Bytes(81))),

    "unknown" / Bytes(81),
    "version" / PaddedString(4, "ascii"),
    Const(b"\x00\x00"),
    "group" / Byte,
    "id" / Int32ul,

    "aname" / Peek(CString("ascii")),
    "bname" / Bytes(11),                # figure out how to write as PaddedString on rebuild
    "name" / IfThenElse(lambda ctx: ctx.aname.__len__() < 11,
        "name" / Computed(this.aname),
        "name" / Computed(this.bname),
    ),
    "groupname" / CString("ascii"),

    "hex3" / HexDump(Peek(Bytes(lambda this: 12 - len(this.groupname)))),
    "unknown3" / Bytes(lambda this: 12 - len(this.groupname)),
    "unknown4" / BitStruct("unknown4" / Array(8, BitsInteger(1))),
    Const(b"\x00\x00\x00"),

    "ICON" / ICON,
    "TXJ1" / TXJ1,
    "TXE1" / TXE1,
    "INFO" / INFO,
    "DATA" / DATA,

    "PRMJ" / PRMJ,
    "PRME" / PRME,
)

# Read data from file

path=Path('./')

dirs = [f.name for f in path.iterdir() if f.is_dir()]
for d in dirs:
    print(d)
    files=[f.name for f in (path/d).iterdir() if f.is_file()]
    
    effects=[["Bypass",0,"",1,0,[[0,0,0,0,"-"],[0,0,0,0,"-"],[0,0,0,0,"-"],[0,0,0,0,"-"],[0,0,0,0,"-"],[0,0,0,0,"-"],[0,0,0,0,"-"],[0,0,0,0,"-"]]]]
    delay_ids=[]
    xpedal_ids=[]
    
    t0=time.perf_counter()
    for f in files:
        fname=f        
        if fname.find(".BMP")>0 or fname.find(".h")>0:
            continue        
        infile = open(path/d/fname, "rb")
        config = ZD2.parse(infile.read())
        infile.close()
        
#         with open(path/d/(fname+'.BMP'),'wb') as f:
#             f.write(config['ICON']['data'])
        effect = [config['name'],config['id'],fname+'.BMP']
        if config['groupname']=='DELAY':
            delay_ids.append(config['id'])
        mmax=[]
        mdefault=[]

        data=config['DATA']['data']
        x=json5.loads(config['PRME']['xml'])
        OnOffstart=data.find(b'OnOff')        

        if OnOffstart!=0 :            
            for j in range(0,10):
                mmax.append(data[OnOffstart + j * 0x38 + 12] + data[OnOffstart + j*0x38+13]*256)
                mdefault.append(data[OnOffstart + j * 0x38 + 16] + data[OnOffstart + j * 0x38 + 17] * 256);
            numParams=len(x['Parameters'])
            effect.append(math.ceil(numParams/4)) #numslots
            effect.append(numParams) #numparams
            params=[]
            for j in range(numParams):
                params.append([x['Parameters'][j]['pedal'],mmax[j+2],mdefault[j+2],0,x['Parameters'][j]['name']])
                if x['Parameters'][j]['pedal']:
                    xpedal_ids.append(config['id'])
            if numParams<8: #max 8 parameters
                for j in range(numParams,8):
                    params.append([0,0,0,0,'-'])
            effect.append(params)
        effects.append(effect)
        
    with open(path/d/(d.replace(" ","").lower()+".h"),"w") as j:
        j.write("#ifndef "+d.replace(" ","").upper()+"_H\n")
        j.write("#define "+d.replace(" ","").upper()+"_H\n")
        j.write("#include effect_model.h\n\n")
        j.write("#define NEFFECTS "+str(len(effects))+"\n")
        j.write("#define NUM_SLOTS \n")
        j.write("#define NUM_PEDALS \n")
        j.write("#define PEDAL_ID \n")
        j.write("#define N_DELAYS "+str(len(delay_ids))+"\n")
        delays="long delay_ids[]={"
        for did in delay_ids:
            delays+=str(did)
            if delay_ids.index(did)<len(delay_ids)-1:
                delays+=","
        delays+="};\n"
        j.write(delays)
        effarr="Effect effects[NEFFECTS]={\n"
        print(len(effects))
        for i in range(len(effects)):
            e=effects[i]            
            effarr+="{\""+str(e[0])+"\","+str(e[1])+",\""+str(e[2])+"\","+str(e[3])+","+str(e[4])+",{"
            for k in range(8):
                effarr+="{"
                if e[5][k][0]:
                    effarr+="1"
                else:
                    effarr+="0"
                effarr+=","+str(e[5][k][1])+","+str(e[5][k][2])+","+str(e[5][k][3])+",\""+str(e[5][k][4])+"\"}"
                if k<7:
                    effarr+=","
            effarr+="}}"
            if effects.index(e) < len(effects)-1:
                effarr+=",\n"
            else:
                effarr+="\n"
        effarr+="};\n"
        j.write(effarr)
        j.write("#define N_X_PEDALS "+str(len(xpedal_ids))+"\n")
        xps="long xpedal_ids[]={"
        for xid in xpedal_ids:
            xps+=str(xid)
            if xpedal_ids.index(xid)<len(xpedal_ids)-1:
                xps+=","
        xps+="};\n"
        j.write(xps)
        j.write("#endif")