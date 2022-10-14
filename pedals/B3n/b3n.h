#ifndef B3N_H
#define B3N_H
#include effect_model.h

#define NEFFECTS 104
#define NUM_SLOTS 
#define NUM_PEDALS 
#define PEDAL_ID 
#define N_DELAYS 7
long delay_ids[]={134217760,134217744,134217888,134217824,134217808,134217792,134217776};
Effect effects[NEFFECTS]={
{"Bypass",0,"",1,0,{{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"160 Comp",25165872,"160_COMP.ZD2.BMP",1,4,{{0,60,38,0,"THRSH"},{0,90,30,0,"Ratio"},{0,1,1,0,"Knee"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AC1x18",92274784,"AC_1X18.ZD2.BMP",1,4,{{0,100,83,0,"DYN20"},{0,100,57,0,"DYN57"},{0,100,38,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AC 370",75497568,"AC_370.ZD2.BMP",2,8,{{0,100,50,0,"Bass"},{0,31,16,0,"MID-F"},{0,100,50,0,"MID"},{0,100,50,0,"Treble"},{0,100,20,0,"Gain"},{0,1,0,0,"BRGHT"},{0,100,45,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"AG4x10TW",92274752,"AG4X10TW.ZD2.BMP",1,4,{{0,100,50,0,"DYN20"},{0,100,50,0,"DYN57"},{0,100,50,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AG 750",75497536,"AG750.ZD2.BMP",2,8,{{0,100,50,0,"Bass"},{0,100,50,0,"MID"},{0,100,50,0,"Treble"},{0,100,50,0,"Gain"},{0,1,0,0,"BRGHT"},{0,1,0,0,"Deep"},{0,100,58,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"Air",150994960,"AIR.ZD2.BMP",1,4,{{0,99,19,0,"Size"},{0,10,5,0,"REF"},{0,100,60,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AM1x15",92274832,"AM1X15.ZD2.BMP",1,4,{{0,100,50,0,"DYN20"},{0,100,50,0,"DYN57"},{0,100,50,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AnalogDly",134217760,"ANALOGDL.ZD2.BMP",1,4,{{0,4022,359,0,"Time"},{0,100,28,0,"F.B"},{0,100,40,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"A-Filter",41943088,"A_FILTER.ZD2.BMP",1,4,{{0,1,0,0,"Mode"},{0,9,7,0,"Sense"},{0,10,7,0,"Peak"},{0,100,10,0,"Dry"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FlipTop",75497616,"B15N.ZD2.BMP",2,8,{{0,1,0,0,"BRGHT"},{0,80,48,0,"Treble"},{0,80,40,0,"MID"},{0,80,64,0,"Bass"},{0,100,30,0,"Gain"},{0,3,0,0,"Ultra"},{0,100,70,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"Bass DRV",58720272,"BASSDRV.ZD2.BMP",2,8,{{0,100,40,0,"Bass"},{0,100,30,0,"Treble"},{0,100,40,0,"PRSNC"},{0,100,50,0,"Blend"},{0,100,60,0,"Gain"},{0,100,68,0,"VOL"},{0,1,1,0,"MID-F"},{0,100,70,0,"MID"}}},
{"BassWah",192938000,"BASSWAH.ZD2.BMP",1,4,{{1,100,50,0,"FREQ"},{0,100,50,0,"Range"},{0,100,20,0,"Dry"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Bass BB",58720320,"BASS_BB.ZD2.BMP",1,4,{{0,100,84,0,"Gain"},{0,20,13,0,"Bass"},{0,20,16,0,"Treble"},{0,100,35,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BassPhase",109052032,"BASS_PHA.ZD2.BMP",1,4,{{0,1,1,0,"Color"},{0,100,100,0,"Depth"},{0,100,55,0,"Rate"},{0,100,56,0,"RESO"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Bass Cry",41943104,"BA_CRY.ZD2.BMP",1,4,{{0,9,3,0,"Range"},{0,10,9,0,"RESO"},{0,19,17,0,"Sense"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BaFzSmile",58720448,"BA_FZSML.ZD2.BMP",1,4,{{0,100,43,0,"Gain"},{0,100,70,0,"Tone"},{0,100,100,0,"BAL"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BassGEQ",41943120,"BA_GEQ.ZD2.BMP",2,8,{{0,48,24,0,"50"},{0,48,24,0,"120"},{0,48,24,0,"400"},{0,48,24,0,"500"},{0,48,24,0,"800"},{0,48,24,0,"4.5k"},{0,48,24,0,"10k"},{0,100,80,0,"VOL"}}},
{"BassMetal",58720464,"BA_METAL.ZD2.BMP",1,4,{{0,100,67,0,"Gain"},{0,100,85,0,"Tone"},{0,100,100,0,"BAL"},{0,100,48,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BassOctFZ",58720480,"BA_OCTFZ.ZD2.BMP",1,4,{{0,100,73,0,"Boost"},{0,100,50,0,"Tone"},{0,100,34,0,"Fuzz"},{0,100,48,0,"Dry"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BassPEQ",41943152,"BA_PEQ.ZD2.BMP",1,4,{{0,37,8,0,"FREQ"},{0,67,5,0,"Q"},{0,80,40,0,"Gain"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Bass Pre",58720352,"BA_PRE.ZD2.BMP",1,4,{{0,10,3,0,"Bass"},{0,20,14,0,"MID"},{0,10,3,0,"Treble"},{0,100,64,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BassTsDRV",58720384,"BA_TSDRV.ZD2.BMP",1,4,{{0,100,74,0,"Gain"},{0,100,57,0,"Tone"},{0,100,80,0,"BAL"},{0,100,82,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BlueB BOD",58720416,"BBB_OD.ZD2.BMP",1,4,{{0,100,50,0,"Gain"},{0,100,50,0,"Nature"},{0,100,100,0,"Blend"},{0,100,50,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BlackOpt",25165840,"BLACKOPT.ZD2.BMP",1,4,{{0,100,50,0,"Comp"},{0,100,50,0,"Lo"},{0,100,50,0,"Hi"},{0,100,76,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BMAN100",75497504,"BMAN100.ZD2.BMP",2,8,{{0,90,40,0,"Bass"},{0,31,14,0,"MID-F"},{0,90,45,0,"MID"},{0,90,53,0,"Treble"},{0,90,45,0,"Gain"},{0,1,0,0,"Deep"},{0,90,45,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"Bomber",117440528,"BOMBER.ZD2.BMP",1,4,{{0,99,49,0,"Decay"},{0,10,4,0,"Tone"},{0,100,30,0,"Mix"},{0,1,1,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BassA-Wah",41943056,"B_ATWAH.ZD2.BMP",1,4,{{0,19,11,0,"Sense"},{0,10,8,0,"RESO"},{0,100,50,0,"Dry"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Ba Detune",109052000,"B_DETUNE.ZD2.BMP",1,4,{{0,50,35,0,"Cent"},{0,50,0,0,"PreD"},{0,10,8,0,"Tone"},{0,100,60,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Ba Octave",109051984,"B_OCTAVE.ZD2.BMP",1,4,{{0,100,80,0,"Oct"},{0,10,3,0,"Lo"},{0,10,8,0,"Hi"},{0,100,100,0,"Dry"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Bass OD",58720368,"B_OD.ZD2.BMP",1,4,{{0,100,0,0,"Gain"},{0,100,20,0,"Tone"},{0,100,50,0,"BAL"},{0,100,88,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Ba PDLMnP",192938048,"B_PDLMNP.ZD2.BMP",1,4,{{1,100,0,0,"Bend"},{0,8,0,0,"Color"},{0,10,10,0,"Tone"},{0,1,0,0,"Mode"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Ba PDLPit",192938032,"B_PDLPIT.ZD2.BMP",1,4,{{1,100,0,0,"Bend"},{0,8,0,0,"Color"},{0,10,10,0,"Tone"},{0,1,0,0,"Mode"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BaMnPitch",109052016,"B_PITCH.ZD2.BMP",1,4,{{0,25,0,0,"Shift"},{0,50,25,0,"Fine"},{0,10,7,0,"Tone"},{0,100,50,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BassStCho",109051936,"B_ST_CHO.ZD2.BMP",1,4,{{0,100,75,0,"Depth"},{0,49,26,0,"Rate"},{0,10,3,0,"LoCut"},{0,100,76,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BaVinFLNG",109051968,"B_VFLNG.ZD2.BMP",1,4,{{0,100,47,0,"Depth"},{0,78,7,0,"Rate"},{0,20,18,0,"RESO"},{0,10,1,0,"LoCut"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"CloneCho",100663552,"CLONECHO.ZD2.BMP",1,4,{{0,1,1,0,"Depth"},{0,100,23,0,"Rate"},{0,100,100,0,"Tone"},{0,100,100,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"CoronaTri",100663600,"CRN_TRI.ZD2.BMP",1,4,{{0,100,100,0,"Depth"},{0,100,25,0,"Speed"},{0,100,100,0,"Tone"},{0,100,100,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Dark OD",58720400,"DARK_OD.ZD2.BMP",1,4,{{0,100,60,0,"Gain"},{0,2,2,0,"ATTCK"},{0,100,50,0,"Blend"},{0,100,75,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Dark Pre",58720304,"DARK_PRE.ZD2.BMP",2,8,{{0,100,50,0,"Bass"},{0,100,50,0,"L-MID"},{0,100,50,0,"H-MID"},{0,100,50,0,"Treble"},{0,100,50,0,"Blend"},{0,100,50,0,"Gain"},{0,100,65,0,"VOL"},{0,2,2,0,"BOOST"}}},
{"DYN Comp",25165920,"DCOMP.ZD2.BMP",1,4,{{0,10,6,0,"Sense"},{0,1,0,0,"ATTCK"},{0,100,50,0,"Tone"},{0,100,50,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Defret",125829184,"DEFRET.ZD2.BMP",1,4,{{0,30,11,0,"Sense"},{0,9,7,0,"Color"},{0,49,36,0,"Tone"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Delay",134217744,"DELAY.ZD2.BMP",1,4,{{0,4022,559,0,"Time"},{0,100,30,0,"F.B"},{0,100,70,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"DI-5",58720336,"DI5.ZD2.BMP",1,4,{{0,100,60,0,"Gain"},{0,6,0,0,"Tone"},{0,1,0,0,"HiCut"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"D.I Plus",58720288,"DI_PLUS.ZD2.BMP",2,8,{{0,100,50,0,"Bass"},{0,100,50,0,"MID"},{0,100,50,0,"Treble"},{0,1,1,0,"Color"},{0,100,50,0,"CL VOL"},{0,100,70,0,"BLEND"},{0,100,70,0,"GAIN"},{0,100,75,0,"DS VOL"}}},
{"Dual DLY",134217888,"DUALDIGD.ZD2.BMP",2,8,{{0,2005,500,0,"TimeA"},{0,110,50,0,"F.B A"},{0,2005,375,0,"TimeB"},{0,110,50,0,"F.B B"},{0,100,25,0,"DlyMx"},{0,100,50,0,"BAL"},{0,101,30,0,"Depth"},{0,50,25,0,"Speed"}}},
{"DualComp",25165888,"DUAL_CMP.ZD2.BMP",1,4,{{0,9,9,0,"FREQ"},{0,50,15,0,"LoCMP"},{0,50,24,0,"HiCMP"},{0,100,75,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"EB4x10TW",92274816,"EB4X10TW.ZD2.BMP",1,4,{{0,100,70,0,"DYN20"},{0,100,85,0,"DYN57"},{0,100,44,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"EBH360",75497600,"EB_HD360.ZD2.BMP",2,8,{{0,40,25,0,"Bass"},{0,31,20,0,"MID-F"},{0,40,20,0,"MID"},{0,40,20,0,"Treble"},{0,100,30,0,"BRGHT"},{0,100,20,0,"Drive"},{0,100,50,0,"VOL"},{0,40,20,0,"CHARA"}}},
{"EG FLTR",33554560,"EGFILTER.ZD2.BMP",2,8,{{0,100,100,0,"FREQ1"},{0,100,16,0,"FREQ2"},{0,100,35,0,"RESO"},{0,5,4,0,"Type"},{0,100,25,0,"Speed"},{0,100,100,0,"BAL"},{0,100,72,0,"VOL"},{0,2,2,0,"CNTRL"}}},
{"EnvFilter",41943200,"ENV_FLTR.ZD2.BMP",1,4,{{0,100,8,0,"THRSH"},{0,100,66,0,"ATTCK"},{0,1,0,0,"Mode"},{0,100,70,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"EP Stomp",50331680,"EP_STOMP.ZD2.BMP",1,4,{{0,100,35,0,"Gain"},{0,20,10,0,"Bass"},{0,20,8,0,"Treble"},{0,100,62,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Exciter",33554608,"EXCITER.ZD2.BMP",1,4,{{0,100,0,0,"Bass"},{0,100,0,0,"Treble"},{0,100,80,0,"VOL"},{0,1,0,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FD-B4x12",92274720,"FD_B4X12.ZD2.BMP",1,4,{{0,100,50,0,"DYN20"},{0,100,50,0,"DYN57"},{0,100,50,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Glam Comp",25165936,"GLAMCOMP.ZD2.BMP",1,4,{{0,100,91,0,"Comp"},{0,10,8,0,"Shape"},{0,100,73,0,"VOL"},{0,100,51,0,"DryMx"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Hall",150994992,"HALL.ZD2.BMP",1,4,{{0,99,48,0,"PreD"},{0,29,9,0,"Decay"},{0,100,46,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"HD Hall",150995008,"HD_HALL.ZD2.BMP",1,4,{{0,199,80,0,"PreD"},{0,100,45,0,"Decay"},{0,100,62,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"High EQ",41943189,"HIGH_EQ.ZD2.BMP",1,4,{{0,1,0,0,"Type"},{0,55,16,0,"FREQ"},{0,48,36,0,"Gain"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Hold DLY",134217824,"HOLDDLY.ZD2.BMP",2,8,{{0,4022,559,0,"Time"},{0,100,30,0,"F.B"},{0,10,10,0,"HiDMP"},{0,100,100,0,"Tone"},{0,100,70,0,"Mix"},{0,1,0,0,"P-P"},{0,1,0,0,"Tail"},{0,1,0,0,"Hold"}}},
{"HPS",100663504,"HPS.ZD2.BMP",1,4,{{0,9,6,0,"Scale"},{0,11,0,0,"Key"},{0,10,6,0,"Tone"},{0,100,70,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Kick FLNG",100663520,"KICKFLNG.ZD2.BMP",2,8,{{0,100,4,0,"PreD"},{0,100,61,0,"Depth"},{0,100,41,0,"Rate"},{0,100,73,0,"ON/OFF"},{0,100,63,0,"RESO"},{0,100,50,0,"Mix"},{0,1,0,0,"RST-F"},{0,1,0,0,"LFO"}}},
{"LMT-76",25165856,"LMT1176.ZD2.BMP",1,4,{{0,80,40,0,"Input"},{0,3,0,0,"Ratio"},{0,60,10,0,"REL"},{0,80,38,0,"Output"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"LoopRoll",117440576,"LOOPROLL.ZD2.BMP",1,4,{{0,4006,3992,0,"Time"},{0,75,75,0,"Duty"},{0,100,100,0,"BAL"},{0,1,1,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Low EQ",41943184,"LOW_EQ.ZD2.BMP",1,4,{{0,1,0,0,"Type"},{0,55,10,0,"FREQ"},{0,48,36,0,"Gain"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MB Comp",25165904,"MB_COMP.ZD2.BMP",1,4,{{0,100,70,0,"Comp"},{0,100,50,0,"LoTHR"},{0,100,50,0,"HiTHR"},{0,100,25,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Mini MkB",75497584,"MINIMARK.ZD2.BMP",1,4,{{0,100,62,0,"Gain"},{0,100,50,0,"VNTG"},{0,100,40,0,"Shape"},{0,100,37,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MkB2x8TW",92274800,"MKB2X8TW.ZD2.BMP",1,4,{{0,100,80,0,"DYN20"},{0,100,80,0,"DYN57"},{0,100,50,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ModDelay",134217808,"MODDELAY.ZD2.BMP",1,4,{{0,2014,499,0,"Time"},{0,100,50,0,"F.B"},{0,100,62,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"NYC Muff",50331856,"NYC_MUFF.ZD2.BMP",1,4,{{0,100,70,0,"SUSTN"},{0,100,55,0,"Tone"},{0,100,100,0,"BAL"},{0,100,58,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"OptComp",16777344,"OPTCOMP.ZD2.BMP",1,4,{{0,10,7,0,"Drive"},{0,100,50,0,"Lo"},{0,100,50,0,"Hi"},{0,100,60,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Output VP",201326576,"OUT_VP.ZD2.BMP",1,1,{{0,5075,4947,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Reso",192938016,"PDL_RESO.ZD2.BMP",1,4,{{1,49,11,0,"FREQ"},{0,10,7,0,"RESO"},{0,100,50,0,"Dry"},{0,100,92,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Vol",184549392,"PDL_VOL.ZD2.BMP",1,4,{{1,100,100,0,"VOL"},{0,100,0,0,"Min"},{0,100,100,0,"Max"},{0,1,0,0,"Curve"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Phaser",100663360,"PHASER.ZD2.BMP",1,4,{{0,3,3,0,"Color"},{0,100,100,0,"Depth"},{0,77,11,0,"Rate"},{0,100,50,0,"RESO"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PH+Dist",125829200,"PH_DIST.ZD2.BMP",1,4,{{0,3,3,0,"Mode"},{0,50,3,0,"Rate"},{0,10,10,0,"RESO"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PitchSHFT",100663472,"PITCHSHF.ZD2.BMP",1,4,{{0,25,19,0,"Shift"},{0,50,25,0,"Fine"},{0,10,7,0,"Tone"},{0,100,40,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Plate",150995056,"PLATEREV.ZD2.BMP",1,4,{{0,199,8,0,"PreD"},{0,100,52,0,"Decay"},{0,100,44,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"RC Boost",50331696,"RCBOOST.ZD2.BMP",1,4,{{0,100,58,0,"Gain"},{0,100,48,0,"Bass"},{0,100,52,0,"Treble"},{0,100,48,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ReverseDL",134217792,"REVERSED.ZD2.BMP",1,4,{{0,2005,990,0,"Time"},{0,100,20,0,"F.B"},{0,100,50,0,"BAL"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Room",150994976,"ROOM.ZD2.BMP",1,4,{{0,99,4,0,"PreD"},{0,29,9,0,"Decay"},{0,100,60,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SeqFLTR",33554496,"SEQFLTR.ZD2.BMP",1,4,{{0,6,6,0,"Step"},{0,7,6,0,"PTTRN"},{0,77,25,0,"Speed"},{0,10,10,0,"RESO"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SlowATTCK",16777264,"SLWATK.ZD2.BMP",1,4,{{0,49,20,0,"Time"},{0,10,10,0,"Curve"},{0,100,100,0,"Tone"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Splitter",41943168,"SPLITTER.ZD2.BMP",1,4,{{0,15,2,0,"FREQ"},{0,50,16,0,"Lo"},{0,50,19,0,"Hi"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Spring",150995024,"SPRING.ZD2.BMP",1,4,{{0,99,0,0,"PreD"},{0,29,19,0,"Decay"},{0,100,50,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Squeak",50331952,"SQUEAK.ZD2.BMP",1,4,{{0,100,47,0,"Gain"},{0,100,60,0,"FLTR"},{0,100,79,0,"VOL"},{0,100,0,0,"DryMx"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"StdSyn",125829136,"STDSYN.ZD2.BMP",1,4,{{0,100,10,0,"Sense"},{0,3,0,0,"Sound"},{0,10,7,0,"Tone"},{0,100,50,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"St Ba GEQ",41943136,"ST_B_GEQ.ZD2.BMP",2,8,{{0,48,24,0,"50"},{0,48,24,0,"120"},{0,48,24,0,"400"},{0,48,24,0,"500"},{0,48,24,0,"800"},{0,48,24,0,"4.5k"},{0,48,24,0,"10k"},{0,100,80,0,"VOL"}}},
{"SuperCho",100663568,"SUPERCHO.ZD2.BMP",1,4,{{0,100,50,0,"Depth"},{0,100,50,0,"Rate"},{0,100,50,0,"Tone"},{0,100,42,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SVT4x10TW",92274712,"SV4X10TW.ZD2.BMP",1,4,{{0,100,50,0,"DYN20"},{0,100,50,0,"DYN57"},{0,100,50,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AMPG SVT",75497488,"SVT.ZD2.BMP",2,8,{{0,80,40,0,"Bass"},{0,31,13,0,"MID-F"},{0,80,40,0,"MID"},{0,80,40,0,"Treble"},{0,100,30,0,"Gain"},{0,4,0,0,"Ultra"},{0,100,71,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"SVT8x10",92274704,"SVT_8X10.ZD2.BMP",1,4,{{0,100,50,0,"DYN20"},{0,100,50,0,"DYN57"},{0,100,50,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SMR400",75497520,"SWR400.ZD2.BMP",2,8,{{0,60,45,0,"Bass"},{0,31,10,0,"MID-F"},{0,60,30,0,"MID"},{0,60,30,0,"Treble"},{0,100,50,0,"Gain"},{0,100,0,0,"ENHNC"},{0,100,68,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"SMR4x10TW",92274736,"SWR_4X10.ZD2.BMP",1,4,{{0,100,50,0,"DYN20"},{0,100,75,0,"DYN57"},{0,100,60,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SynTlk",125829152,"SYNTLK.ZD2.BMP",1,4,{{0,100,40,0,"Decay"},{0,3,1,0,"Type"},{0,10,8,0,"Tone"},{0,100,50,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TapeEcho",134217776,"TAPEECHO.ZD2.BMP",1,4,{{0,2014,559,0,"Time"},{0,100,64,0,"F.B"},{0,100,56,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TE400SMX",75497552,"TE400SMX.ZD2.BMP",2,8,{{0,2,2,0,"Style"},{0,60,31,0,"Bass"},{0,60,33,0,"MID"},{0,60,41,0,"Treble"},{0,100,20,0,"Gain"},{0,2,0,0,"Shape"},{0,100,60,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"TE4x10",92274768,"TE_4X10.ZD2.BMP",1,4,{{0,100,50,0,"DYN20"},{0,100,50,0,"DYN57"},{0,100,50,0,"Bottom"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TheVibe",100663392,"THEVIBE.ZD2.BMP",1,4,{{0,50,25,0,"Speed"},{0,100,60,0,"Depth"},{0,1,1,0,"Mode"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Tremolo",100663312,"TREMOLO.ZD2.BMP",1,4,{{0,2,0,0,"Wave"},{0,100,90,0,"Depth"},{0,110,50,0,"Rate"},{0,100,62,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TS+Boost",50331904,"TS_BOOST.ZD2.BMP",2,8,{{0,100,34,0,"Gain"},{0,100,50,0,"Tone"},{0,100,75,0,"VOL"},{0,2,1,0,"Comp"},{0,100,60,0,"BOOST"},{0,100,40,0,"BASS"},{0,100,50,0,"TREBLE"},{0,1,0,0,"CONNECT"}}},
{"VooDoo-B",58720432,"VOODOO_B.ZD2.BMP",1,4,{{0,100,41,0,"Gain"},{0,100,46,0,"Tone"},{0,100,100,0,"Blend"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ZNR",16777280,"ZNR.ZD2.BMP",1,4,{{0,1,1,0,"DETCT"},{0,100,100,0,"Depth"},{0,100,30,0,"THRSH"},{0,100,0,0,"Decay"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Z-Syn",125829168,"Z_SYN.ZD2.BMP",2,8,{{0,10,2,0,"FREQ"},{0,20,8,0,"Range"},{0,100,72,0,"Decay"},{0,20,18,0,"RESO"},{0,1,0,0,"Wave"},{0,10,7,0,"Tone"},{0,100,80,0,"BAL"},{0,100,80,0,"VOL"}}},
{"Z Tron",41943072,"Z_TRON.ZD2.BMP",1,4,{{0,19,16,0,"Sense"},{0,10,7,0,"RESO"},{0,100,25,0,"Dry"},{0,100,83,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}}
};
#define N_X_PEDALS 5
long xpedal_ids[]={192938000,192938048,192938032,192938016,184549392};
#endif