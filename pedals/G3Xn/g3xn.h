#ifndef G3XN_H
#define G3XN_H
#include effect_model.h

#define NEFFECTS 158
#define NUM_SLOTS 
#define NUM_PEDALS 
#define PEDAL_ID 
#define N_DELAYS 17
long delay_ids[]={134217760,134217936,134217744,134217888,134217872,134217824,134217984,134217808,134217952,134217904,134217856,134217792,134217920,134218000,134218016,134217968,134217776};
Effect effects[NEFFECTS]={
{"Bypass",0,"",1,0,{{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Aco.Sim",50331840,"ACOSIM.ZD2.BMP",1,4,{{0,100,80,0,"Top"},{0,100,50,0,"Body"},{0,100,100,0,"Tone"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Air",150994960,"AIR.ZD2.BMP",1,4,{{0,99,19,0,"Size"},{0,10,5,0,"REF"},{0,100,60,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Ambience",150995120,"AMBIENCE.ZD2.BMP",1,4,{{0,200,29,0,"PreD"},{0,100,70,0,"Decay"},{0,100,50,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AnalogCho",100663632,"ANA234CH.ZD2.BMP",1,4,{{0,100,52,0,"Depth"},{0,100,54,0,"Rate"},{0,100,49,0,"Tone"},{0,100,82,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AnalogDly",134217760,"ANALOGDL.ZD2.BMP",1,4,{{0,4022,359,0,"Time"},{0,100,28,0,"F.B"},{0,100,40,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"A-Pan DLY",134217936,"APANDLY.ZD2.BMP",2,8,{{0,2014,222,0,"Time"},{0,100,87,0,"F.B"},{0,100,53,0,"Mix"},{0,1,1,0,"Link"},{0,52,26,0,"Cycle"},{0,50,50,0,"Width"},{0,10,0,0,"Clip"},{0,1,0,0,"INPUT"}}},
{"AutoPan",117440544,"AUTOPAN.ZD2.BMP",1,4,{{0,78,5,0,"Rate"},{0,50,50,0,"Width"},{0,10,0,0,"Clip"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"AutoWah",33554448,"AUTOWAH.ZD2.BMP",1,4,{{0,1,1,0,"Mode"},{0,9,7,0,"Sense"},{0,10,8,0,"RESO"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BendCho",100663616,"BENDCHO.ZD2.BMP",1,4,{{0,1,0,0,"Mode"},{0,100,40,0,"Depth"},{0,50,50,0,"Time"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BGN4x12",83886160,"BGN4X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"HG THRTTL",50331872,"BGTHRTTL.ZD2.BMP",1,4,{{0,100,78,0,"Gain"},{0,100,56,0,"Tone"},{0,100,46,0,"MdCut"},{0,100,54,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BG GRID",50331888,"BG_GRID.ZD2.BMP",1,4,{{0,100,68,0,"Gain"},{0,100,50,0,"Tone"},{0,100,100,0,"BAL"},{0,100,74,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BG MK1",67108928,"BG_MK1.ZD2.BMP",2,8,{{0,100,49,0,"Bass"},{0,100,55,0,"MID"},{0,100,53,0,"Treble"},{0,100,55,0,"PRSNC"},{0,100,72,0,"Gain1"},{0,100,70,0,"Gain2"},{0,100,58,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"BG MK3",67108930,"BG_MK3.ZD2.BMP",2,8,{{0,100,52,0,"Bass"},{0,100,85,0,"MID"},{0,100,40,0,"Treble"},{0,100,40,0,"PRSNC"},{0,100,75,0,"Gain1"},{0,100,75,0,"Gain2"},{0,100,78,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"BlackOpt",25165840,"BLACKOPT.ZD2.BMP",1,4,{{0,100,50,0,"Comp"},{0,100,50,0,"Lo"},{0,100,50,0,"Hi"},{0,100,76,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"BlackWah",184549408,"BLCK_WAH.ZD2.BMP",1,4,{{1,100,50,0,"FREQ"},{0,100,50,0,"Range"},{0,100,0,0,"Dry"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Bomber",117440528,"BOMBER.ZD2.BMP",1,4,{{0,99,49,0,"Decay"},{0,10,4,0,"Tone"},{0,100,30,0,"Mix"},{0,1,1,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Chamber",150995152,"CHAMBER.ZD2.BMP",1,4,{{0,200,24,0,"PreD"},{0,100,50,0,"Decay"},{0,100,48,0,"Mix"},{0,1,1,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Chorus",100663328,"CHORUS.ZD2.BMP",1,4,{{0,100,40,0,"Depth"},{0,49,24,0,"Rate"},{0,10,7,0,"Tone"},{0,100,50,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ChromeWah",184549424,"CHRM_WAH.ZD2.BMP",1,4,{{1,100,50,0,"FREQ"},{0,100,50,0,"Range"},{0,100,0,0,"Dry"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Church",150995104,"CHURCH.ZD2.BMP",1,4,{{0,200,96,0,"PreD"},{0,100,49,0,"Decay"},{0,100,46,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"CloneCho",100663552,"CLONECHO.ZD2.BMP",1,4,{{0,1,1,0,"Depth"},{0,100,23,0,"Rate"},{0,100,100,0,"Tone"},{0,100,100,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Comp",16777232,"COMP.ZD2.BMP",1,4,{{0,10,6,0,"Sense"},{0,1,0,0,"ATTCK"},{0,10,6,0,"Tone"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"CoronaTri",100663600,"CRN_TRI.ZD2.BMP",1,4,{{0,100,100,0,"Depth"},{0,100,25,0,"Speed"},{0,100,100,0,"Tone"},{0,100,100,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Cry",33554480,"CRY.ZD2.BMP",1,4,{{0,9,6,0,"Range"},{0,10,8,0,"RESO"},{0,19,16,0,"Sense"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Delay",134217744,"DELAY.ZD2.BMP",1,4,{{0,4022,559,0,"Time"},{0,100,30,0,"F.B"},{0,100,70,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Detune",100663456,"DETUNE.ZD2.BMP",1,4,{{0,50,35,0,"Cent"},{0,50,0,0,"PreD"},{0,10,8,0,"Tone"},{0,100,52,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"DIST Plus",50332000,"DISTPLUS.ZD2.BMP",1,4,{{0,100,70,0,"Gain"},{0,100,100,0,"VOL"},{0,100,0,0,"DryMx"},{0,2,0,0,"Comp"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"DIST 1",50331936,"DIST_1.ZD2.BMP",1,4,{{0,100,61,0,"Gain"},{0,100,41,0,"Tone"},{0,100,100,0,"VOL"},{0,1,0,0,"Comp"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Dual DLY",134217888,"DUALDIGD.ZD2.BMP",2,8,{{0,2005,500,0,"TimeA"},{0,110,50,0,"F.B A"},{0,2005,375,0,"TimeB"},{0,110,50,0,"F.B B"},{0,100,25,0,"DlyMx"},{0,100,50,0,"BAL"},{0,101,30,0,"Depth"},{0,50,25,0,"Speed"}}},
{"Duo Phase",100663664,"DUO_PHA.ZD2.BMP",2,8,{{0,99,62,0,"DPT A"},{0,77,5,0,"RateA"},{0,10,6,0,"ResoA"},{0,2,0,0,"Link"},{0,99,36,0,"DPT B"},{0,51,46,0,"RATE B"},{0,10,0,0,"RESO B"},{0,100,80,0,"VOL"}}},
{"DYN Drive",50331744,"DYNDRIVE.ZD2.BMP",1,4,{{0,100,78,0,"Gain"},{0,100,67,0,"Tone"},{0,1,1,0,"Mode"},{0,100,46,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"DZ4x12F",83886224,"DZ4X12F.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"DZ DRV",67109008,"DZ_DRV.ZD2.BMP",2,8,{{0,100,50,0,"Bass"},{0,100,70,0,"MID"},{0,100,60,0,"Treble"},{0,100,40,0,"PRSNC"},{0,100,60,0,"Gain"},{0,100,80,0,"VOL"},{0,100,0,0,"Deep"},{0,100,0,0,"MID CUT"}}},
{"EarlyRef",150995072,"EARLYREF.ZD2.BMP",1,4,{{0,29,14,0,"Decay"},{0,20,20,0,"Shape"},{0,10,6,0,"Tone"},{0,100,50,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"EG FLTR",33554560,"EGFILTER.ZD2.BMP",2,8,{{0,100,100,0,"FREQ1"},{0,100,16,0,"FREQ2"},{0,100,35,0,"RESO"},{0,5,4,0,"Type"},{0,100,25,0,"Speed"},{0,100,100,0,"BAL"},{0,100,72,0,"VOL"},{0,2,2,0,"CNTRL"}}},
{"EP Stomp",50331680,"EP_STOMP.ZD2.BMP",1,4,{{0,100,35,0,"Gain"},{0,20,10,0,"Bass"},{0,20,8,0,"Treble"},{0,100,62,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Exciter",33554608,"EXCITER.ZD2.BMP",1,4,{{0,100,0,0,"Bass"},{0,100,0,0,"Treble"},{0,100,80,0,"VOL"},{0,1,0,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FD2x12",83886112,"FD2X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FD-B4x10",83886119,"FDB4X10.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FD-DX1x12",83886122,"FDDX1X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FD MA2x12",83886123,"FDMA2X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FD Spring",150995040,"FDSPRING.ZD2.BMP",1,4,{{0,1,0,0,"Color"},{0,100,100,0,"Lo"},{0,100,100,0,"Hi"},{0,100,50,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"FD B-MAN",67108903,"FD_BMAN.ZD2.BMP",2,8,{{0,1,1,0,"Input"},{0,110,30,0,"Bass"},{0,110,90,0,"MID"},{0,110,40,0,"Treble"},{0,110,50,0,"PRSNC"},{0,110,30,0,"Gain"},{0,110,50,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"FD DLXR",67108906,"FD_DLXR.ZD2.BMP",2,8,{{0,1,0,0,"Input"},{0,90,33,0,"Bass"},{0,90,55,0,"Treble"},{0,90,50,0,"Gain"},{0,90,90,0,"VOL"},{0,90,80,0,"DEPTH"},{0,100,40,0,"SPEED"},{0,9,0,0,"TRM VOL"}}},
{"FD MASTER",67108907,"FD_MSTR.ZD2.BMP",2,8,{{0,90,40,0,"Gain"},{0,90,60,0,"Bass"},{0,90,60,0,"MID"},{0,90,60,0,"Treble"},{0,1,1,0,"Fat"},{0,90,40,0,"VOL"},{0,100,50,0,"TONE"},{0,8,2,0,"SOLO"}}},
{"FD TWNR",67108896,"FD_TWINR.ZD2.BMP",2,8,{{0,90,38,0,"Bass"},{0,90,40,0,"MID"},{0,90,35,0,"Treble"},{0,1,0,0,"BRGHT"},{0,90,30,0,"Gain"},{0,90,70,0,"VOL"},{0,90,40,0,"DEPTH"},{0,100,40,0,"SPEED"}}},
{"FilterDly",134217872,"FLTRDLY.ZD2.BMP",1,4,{{0,2014,499,0,"Time"},{0,100,50,0,"F.B"},{0,100,90,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"GateRev",150995168,"GATE_REV.ZD2.BMP",1,4,{{0,4,0,0,"Color"},{0,100,55,0,"Decay"},{0,100,50,0,"Tone"},{0,100,60,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"GoldDrive",50331712,"GOLD_DRV.ZD2.BMP",1,4,{{0,100,69,0,"Gain"},{0,100,50,0,"Bass"},{0,100,56,0,"Treble"},{0,100,43,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"GrayComp",16777312,"GRAYCOMP.ZD2.BMP",1,4,{{0,100,63,0,"SUSTN"},{0,100,50,0,"Lo"},{0,100,50,0,"Hi"},{0,100,88,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Gt GEQ",33554512,"GT_GEQ.ZD2.BMP",2,8,{{0,48,24,0,"160"},{0,48,24,0,"400"},{0,48,24,0,"800"},{0,48,24,0,"3.2k"},{0,48,24,0,"6.4k"},{0,48,24,0,"12k"},{0,100,80,0,"VOL"},{0,48,24,0,"CH SEL"}}},
{"Gt GEQ 7",33554515,"GT_GEQ_7.ZD2.BMP",2,8,{{0,48,24,0,"100"},{0,48,24,0,"200"},{0,48,24,0,"400"},{0,48,24,0,"800"},{0,48,24,0,"1.6k"},{0,48,24,0,"3.2k"},{0,48,24,0,"6.4k"},{0,100,80,0,"VOL"}}},
{"Hall",150994992,"HALL.ZD2.BMP",1,4,{{0,99,48,0,"PreD"},{0,29,9,0,"Decay"},{0,100,46,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"HD Hall",150995008,"HD_HALL.ZD2.BMP",1,4,{{0,199,80,0,"PreD"},{0,100,45,0,"Decay"},{0,100,62,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Hold DLY",134217824,"HOLDDLY.ZD2.BMP",2,8,{{0,4022,559,0,"Time"},{0,100,30,0,"F.B"},{0,10,10,0,"HiDMP"},{0,100,100,0,"Tone"},{0,100,70,0,"Mix"},{0,1,0,0,"P-P"},{0,1,0,0,"Tail"},{0,1,0,0,"Hold"}}},
{"HoldVerb",150995184,"HOLDVERB.ZD2.BMP",2,8,{{0,199,8,0,"PreD"},{0,100,52,0,"Decay"},{0,100,44,0,"Mix"},{0,1,0,0,"Tail"},{0,100,58,0,"Color"},{0,100,97,0,"LoDMP"},{0,100,95,0,"HiDMP"},{0,1,0,0,"Hold"}}},
{"HotSpice",117440592,"HOTSPICE.ZD2.BMP",1,4,{{0,100,11,0,"Bend"},{0,100,57,0,"Buzz"},{0,100,36,0,"+1oct"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"HPS",100663504,"HPS.ZD2.BMP",1,4,{{0,9,6,0,"Scale"},{0,11,0,0,"Key"},{0,10,6,0,"Tone"},{0,100,70,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"HW 100",67108960,"HW100.ZD2.BMP",2,8,{{0,1,1,0,"Input"},{0,100,40,0,"Bass"},{0,100,80,0,"MID"},{0,100,60,0,"Treble"},{0,100,60,0,"PRSNC"},{0,100,50,0,"Gain"},{0,100,60,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"HW4x12",83886176,"HW4X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ICE Delay",134217984,"ICE_DLY.ZD2.BMP",1,4,{{0,30,28,0,"INTVL"},{0,1255,1248,0,"Time"},{0,100,46,0,"F.B"},{0,100,36,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MS 45os",67108890,"JTM45OS.ZD2.BMP",2,8,{{0,100,30,0,"Bass"},{0,100,70,0,"MID"},{0,100,65,0,"Treble"},{0,100,30,0,"PRSNC"},{0,101,61,0,"Input1"},{0,101,0,0,"Input2"},{0,100,80,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"Kick FLNG",100663520,"KICKFLNG.ZD2.BMP",2,8,{{0,100,4,0,"PreD"},{0,100,61,0,"Depth"},{0,100,41,0,"Rate"},{0,100,73,0,"ON/OFF"},{0,100,63,0,"RESO"},{0,100,50,0,"Mix"},{0,1,0,0,"RST-F"},{0,1,0,0,"LFO"}}},
{"LFO FLTR",33554640,"LFO_FLTR.ZD2.BMP",1,4,{{0,100,100,0,"Depth"},{0,77,57,0,"Rate"},{0,10,8,0,"RESO"},{0,3,0,0,"Wave"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"LMT-76",25165856,"LMT1176.ZD2.BMP",1,4,{{0,80,40,0,"Input"},{0,3,0,0,"Ratio"},{0,60,10,0,"REL"},{0,80,38,0,"Output"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"LoopRoll",117440576,"LOOPROLL.ZD2.BMP",1,4,{{0,4006,3992,0,"Time"},{0,75,75,0,"Duty"},{0,100,100,0,"BAL"},{0,1,1,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"LowPassFL",33554592,"LOWPASSF.ZD2.BMP",1,4,{{0,100,56,0,"FREQ"},{0,201,50,0,"Sense"},{0,21,3,0,"RESO"},{0,100,100,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MA2x12",83886240,"MA2X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MATCH30",67109024,"MATCH_30.ZD2.BMP",2,8,{{0,101,36,0,"Gain1"},{0,100,47,0,"Bass1"},{0,100,49,0,"TRBL1"},{0,101,0,0,"Gain2"},{0,5,1,0,"Tone2"},{0,100,0,0,"Cut"},{0,101,34,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"MK1 1x12",83886144,"MK1_1X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MK3 1x12",83886146,"MK3_1X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ModDelay",134217808,"MODDELAY.ZD2.BMP",1,4,{{0,2014,499,0,"Time"},{0,100,50,0,"F.B"},{0,100,62,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MonoPitch",100663488,"MONOPITC.ZD2.BMP",1,4,{{0,25,0,0,"Shift"},{0,50,25,0,"Fine"},{0,10,6,0,"Tone"},{0,100,50,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MS 1959",67108888,"MS1959.ZD2.BMP",2,8,{{0,100,50,0,"Bass"},{0,100,70,0,"MID"},{0,100,60,0,"Treble"},{0,100,40,0,"PRSNC"},{0,101,61,0,"Input1"},{0,101,0,0,"Input2"},{0,100,80,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"MS4x12",83886096,"MS4X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MS4x12AL",83886106,"MS4X12AL.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MS4x12GB",83886104,"MS4X12GB.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MS 800",67108880,"MS800.ZD2.BMP",2,8,{{0,1,1,0,"Input"},{0,100,50,0,"Bass"},{0,100,50,0,"MID"},{0,100,50,0,"Treble"},{0,100,30,0,"PRSNC"},{0,100,70,0,"Gain"},{0,100,70,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"MetalWRLD",50331776,"MTLWRLD.ZD2.BMP",1,4,{{0,100,60,0,"Gain"},{0,100,50,0,"Bass"},{0,100,50,0,"Treble"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"MuteSW",16777296,"MUTESW.ZD2.BMP",1,4,{{0,100,13,0,"Edge"},{0,100,100,0,"Speed"},{0,1,0,0,"INVRT"},{0,2,1,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"NYC Muff",50331856,"NYC_MUFF.ZD2.BMP",1,4,{{0,100,70,0,"SUSTN"},{0,100,55,0,"Tone"},{0,100,100,0,"BAL"},{0,100,58,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"NoiseGate",16777328,"N_GATE.ZD2.BMP",1,4,{{0,1,1,0,"DETCT"},{0,100,100,0,"Depth"},{0,100,54,0,"THRSH"},{0,100,0,0,"Decay"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Octave",100663424,"OCTAVE.ZD2.BMP",1,4,{{0,100,80,0,"OCT1"},{0,100,15,0,"OCT2"},{0,10,8,0,"Tone"},{0,100,100,0,"Dry"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"OctFuzz",50331808,"OCTFUZZ.ZD2.BMP",1,4,{{0,100,65,0,"Boost"},{0,1,1,0,"Color"},{0,100,50,0,"Tone"},{0,100,68,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"OptComp",16777344,"OPTCOMP.ZD2.BMP",1,4,{{0,10,7,0,"Drive"},{0,100,50,0,"Lo"},{0,100,50,0,"Hi"},{0,100,60,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ORG120",67108992,"ORG_120.ZD2.BMP",2,8,{{0,1,1,0,"Input"},{0,5,3,0,"Color"},{0,100,50,0,"Bass"},{0,100,60,0,"Treble"},{0,100,50,0,"PRSNC"},{0,100,53,0,"Gain"},{0,100,100,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"ORG4x12",83886208,"ORG_4X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"OSC Echo",184549568,"OSC_ECHO.ZD2.BMP",1,4,{{1,100,0,0,"OSC"},{0,481,311,0,"T-Min"},{0,481,81,0,"T-Max"},{0,100,80,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"OutputBST",50331984,"OUT_BST.ZD2.BMP",1,4,{{0,9,4,0,"Range"},{0,100,30,0,"Boost"},{0,100,50,0,"Tone"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Output VP",201326576,"OUT_VP.ZD2.BMP",1,1,{{0,5075,4947,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ParaEQ",33554544,"PARAEQ.ZD2.BMP",1,4,{{0,30,8,0,"FREQ"},{0,67,1,0,"Q"},{0,48,24,0,"Gain"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ParticleR",150995136,"PARTICLE.ZD2.BMP",1,4,{{0,2,0,0,"Mode"},{0,100,75,0,"Decay"},{0,100,60,0,"Mix"},{0,1,1,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"P-BitCRSH",184549616,"PDL_BITC.ZD2.BMP",1,4,{{1,50,2,0,"SMPL"},{0,13,5,0,"Bit"},{0,10,8,0,"Tone"},{0,100,90,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Delay",184549536,"PDL_DLY.ZD2.BMP",1,4,{{1,100,100,0,"InLvl"},{0,4022,359,0,"Time"},{0,100,40,0,"F.B"},{0,100,100,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Drive",184549504,"PDL_DRV.ZD2.BMP",1,4,{{1,100,50,0,"Gain"},{0,100,74,0,"Tone"},{0,100,48,0,"PRSNC"},{0,100,61,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL FLNGR",184549632,"PDL_FLNG.ZD2.BMP",1,4,{{1,100,50,0,"FREQ"},{0,20,18,0,"RESO"},{0,10,8,0,"HiDMP"},{0,100,65,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL MnPit",184549472,"PDL_MNPT.ZD2.BMP",1,4,{{1,100,0,0,"Bend"},{0,8,0,0,"Color"},{0,10,10,0,"Tone"},{0,1,0,0,"Mode"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL PHSR",184549520,"PDL_PHA.ZD2.BMP",1,4,{{1,49,11,0,"Rate"},{0,100,100,0,"Depth"},{0,100,50,0,"RESO"},{0,3,3,0,"Color"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Pitch",184549456,"PDL_PIT.ZD2.BMP",1,4,{{1,100,0,0,"Bend"},{0,8,0,0,"Color"},{0,10,10,0,"Tone"},{0,1,0,0,"Mode"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Reso",192938016,"PDL_RESO.ZD2.BMP",1,4,{{1,49,11,0,"FREQ"},{0,10,7,0,"RESO"},{0,100,50,0,"Dry"},{0,100,92,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Rev",184549552,"PDL_REV.ZD2.BMP",1,4,{{1,100,100,0,"InLvl"},{0,99,48,0,"PreD"},{0,29,14,0,"Decay"},{0,100,80,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Roto",184549600,"PDL_ROT.ZD2.BMP",1,4,{{1,1,0,0,"Mode"},{0,100,20,0,"Drive"},{0,100,50,0,"BAL"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Vibe",184549488,"PDL_VIBE.ZD2.BMP",1,4,{{1,50,25,0,"Speed"},{0,100,60,0,"Depth"},{0,1,1,0,"Mode"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PDL Vol",184549392,"PDL_VOL.ZD2.BMP",1,4,{{1,100,100,0,"VOL"},{0,100,0,0,"Min"},{0,100,100,0,"Max"},{0,1,0,0,"Curve"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PhaseDly",134217952,"PHASEDLY.ZD2.BMP",2,8,{{0,2014,2006,0,"Time"},{0,100,24,0,"F.B"},{0,100,56,0,"Mix"},{0,1,1,0,"Tail"},{0,3,2,0,"COLOR"},{0,100,100,0,"DEPTH"},{0,77,59,0,"RATE"},{0,100,48,0,"RESO"}}},
{"Phaser",100663360,"PHASER.ZD2.BMP",1,4,{{0,3,3,0,"Color"},{0,100,100,0,"Depth"},{0,77,11,0,"Rate"},{0,100,50,0,"RESO"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Pitch DLY",134217904,"PITCHDLY.ZD2.BMP",1,4,{{0,30,21,0,"Pitch"},{0,1999,89,0,"Time"},{0,100,80,0,"F.B"},{0,100,80,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"PitchSHFT",100663472,"PITCHSHF.ZD2.BMP",1,4,{{0,25,19,0,"Shift"},{0,50,25,0,"Fine"},{0,10,7,0,"Tone"},{0,100,40,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Plate",150995056,"PLATEREV.ZD2.BMP",1,4,{{0,199,8,0,"PreD"},{0,100,52,0,"Decay"},{0,100,44,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"P-P Delay",134217856,"P_P_DLY.ZD2.BMP",1,4,{{0,4022,559,0,"Time"},{0,100,30,0,"F.B"},{0,100,70,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"RackComp",16777248,"RACKCOMP.ZD2.BMP",1,4,{{0,50,40,0,"THRSH"},{0,9,5,0,"Ratio"},{0,9,6,0,"ATTCK"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"RC Boost",50331696,"RCBOOST.ZD2.BMP",1,4,{{0,100,58,0,"Gain"},{0,100,48,0,"Bass"},{0,100,52,0,"Treble"},{0,100,48,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"RCT4x12",83886192,"RCT4X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Recti ORG",67108976,"RCT_ORG.ZD2.BMP",2,8,{{0,1,0,0,"Mode"},{0,100,52,0,"Bass"},{0,100,65,0,"MID"},{0,100,67,0,"Treble"},{0,100,62,0,"PRSNC"},{0,100,70,0,"Gain"},{0,100,62,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"RedCR+BST",50331920,"REDCRBST.ZD2.BMP",2,8,{{0,100,68,0,"Gain"},{0,100,50,0,"Tone"},{0,100,52,0,"PRSNC"},{0,100,61,0,"VOL"},{0,2,1,0,"Comp"},{0,1,1,0,"LO/HI"},{0,100,42,0,"BOOST"},{0,1,1,0,"CONNECT"}}},
{"RedCrunch",50331760,"REDCRUNC.ZD2.BMP",1,4,{{0,100,68,0,"Gain"},{0,100,47,0,"Tone"},{0,100,48,0,"PRSNC"},{0,100,61,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Resonance",33554464,"RESONANC.ZD2.BMP",1,4,{{0,1,1,0,"Mode"},{0,9,4,0,"Sense"},{0,10,8,0,"RESO"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ReverseDL",134217792,"REVERSED.ZD2.BMP",1,4,{{0,2005,990,0,"Time"},{0,100,20,0,"F.B"},{0,100,50,0,"BAL"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"RingMod",100663440,"RINGMOD.ZD2.BMP",1,4,{{0,49,27,0,"FREQ"},{0,10,10,0,"Tone"},{0,100,50,0,"BAL"},{0,100,88,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"RndmFLTR",33554576,"RNDMFLTR.ZD2.BMP",1,4,{{0,2,2,0,"Type"},{0,77,34,0,"Speed"},{0,100,90,0,"BAL"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Room",150994976,"ROOM.ZD2.BMP",1,4,{{0,99,4,0,"PreD"},{0,29,9,0,"Decay"},{0,100,60,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SeqFLTR",33554496,"SEQFLTR.ZD2.BMP",1,4,{{0,6,6,0,"Step"},{0,7,6,0,"PTTRN"},{0,77,25,0,"Speed"},{0,10,10,0,"RESO"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SlapBackD",134217920,"SLAPBKD.ZD2.BMP",1,4,{{0,300,98,0,"Time"},{0,100,29,0,"F.B"},{0,100,40,0,"Mix"},{0,2,0,0,"SubDv"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Slicer",100663536,"SLICER.ZD2.BMP",1,4,{{0,19,0,0,"PTTRN"},{0,77,24,0,"Speed"},{0,50,20,0,"THRSH"},{0,100,87,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SlowATTCK",16777264,"SLWATK.ZD2.BMP",1,4,{{0,49,20,0,"Time"},{0,10,10,0,"Curve"},{0,100,100,0,"Tone"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SlwAtkDly",134218000,"SLWATKDL.ZD2.BMP",1,4,{{0,49,24,0,"Swell"},{0,1914,489,0,"Time"},{0,100,71,0,"F.B"},{0,100,64,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SoftEcho",134218016,"SOFTECHO.ZD2.BMP",1,4,{{0,1,1,0,"MOD"},{0,562,387,0,"Time"},{0,100,47,0,"F.B"},{0,100,69,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SpaceHole",150995088,"SPC_HOLE.ZD2.BMP",2,8,{{0,1000,80,0,"PreD"},{0,200,50,0,"Decay"},{0,100,45,0,"F.B"},{0,100,40,0,"Mix"},{0,100,58,0,"Depth"},{0,100,39,0,"Speed"},{0,100,29,0,"Size"},{0,1,0,0,"INPUT"}}},
{"Spring",150995024,"SPRING.ZD2.BMP",1,4,{{0,99,0,0,"PreD"},{0,29,19,0,"Decay"},{0,100,50,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SpotBoost",50331824,"SPTBOOST.ZD2.BMP",1,4,{{0,100,35,0,"Boost"},{0,20,10,0,"Bass"},{0,20,8,0,"Treble"},{0,1,1,0,"ON/OFF"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Squeak",50331952,"SQUEAK.ZD2.BMP",1,4,{{0,100,47,0,"Gain"},{0,100,60,0,"FLTR"},{0,100,79,0,"VOL"},{0,100,0,0,"DryMx"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Step",33554624,"STEP.ZD2.BMP",1,4,{{0,100,60,0,"Depth"},{0,78,25,0,"Rate"},{0,10,8,0,"RESO"},{0,10,10,0,"Shape"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"StereoCho",100663344,"STEREOCH.ZD2.BMP",1,4,{{0,100,80,0,"Depth"},{0,49,29,0,"Rate"},{0,10,7,0,"Tone"},{0,100,60,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"StonePha",100663584,"STONEPHA.ZD2.BMP",1,4,{{0,1,0,0,"Color"},{0,100,100,0,"Depth"},{0,100,50,0,"Rate"},{0,100,40,0,"RESO"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"St Gt GEQ",33554528,"ST_GT_GE.ZD2.BMP",2,8,{{0,48,24,0,"160"},{0,48,24,0,"400"},{0,48,24,0,"800"},{0,48,24,0,"3.2k"},{0,48,24,0,"6.4k"},{0,48,24,0,"12k"},{0,100,80,0,"VOL"},{0,48,24,0,"CH SEL"}}},
{"SuperCho",100663568,"SUPERCHO.ZD2.BMP",1,4,{{0,100,50,0,"Depth"},{0,100,50,0,"Rate"},{0,100,50,0,"Tone"},{0,100,42,0,"Mix"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"SweetDrv",50331728,"SWEETDRV.ZD2.BMP",1,4,{{0,100,78,0,"Gain"},{0,100,50,0,"Tone"},{0,100,67,0,"Focus"},{0,100,62,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TapeEcho3",134217968,"TAPEECH3.ZD2.BMP",2,8,{{0,100,50,0,"Gain"},{0,100,62,0,"Hi"},{0,100,47,0,"Lo"},{0,100,80,0,"VOL"},{0,1005,350,0,"TIME"},{0,100,20,0,"F.B"},{0,100,50,0,"MIX"},{0,100,50,0,"REC LV"}}},
{"TapeEcho",134217776,"TAPEECHO.ZD2.BMP",1,4,{{0,2014,559,0,"Time"},{0,100,64,0,"F.B"},{0,100,56,0,"Mix"},{0,1,0,0,"Tail"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TB MK1.5",50331792,"TB_MK15.ZD2.BMP",1,4,{{0,100,90,0,"ATTCK"},{0,100,100,0,"Tone"},{0,1,1,0,"Color"},{0,100,92,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TheVibe",100663392,"THEVIBE.ZD2.BMP",1,4,{{0,50,25,0,"Speed"},{0,100,60,0,"Depth"},{0,1,1,0,"Mode"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Tremolo",100663312,"TREMOLO.ZD2.BMP",1,4,{{0,2,0,0,"Wave"},{0,100,90,0,"Depth"},{0,110,50,0,"Rate"},{0,100,62,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"TS+Boost",50331904,"TS_BOOST.ZD2.BMP",2,8,{{0,100,34,0,"Gain"},{0,100,50,0,"Tone"},{0,100,75,0,"VOL"},{0,2,1,0,"Comp"},{0,100,60,0,"BOOST"},{0,100,40,0,"BASS"},{0,100,50,0,"TREBLE"},{0,1,0,0,"CONNECT"}}},
{"TS Drive",50331664,"TS_DRIVE.ZD2.BMP",1,4,{{0,100,74,0,"Gain"},{0,1,0,0,"Boost"},{0,100,57,0,"Tone"},{0,100,82,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"UK2x12",83886128,"UK2X12.ZD2.BMP",1,4,{{0,1,0,0,"MIC"},{0,100,50,0,"D57:D421"},{0,100,50,0,"Hi"},{0,100,50,0,"Lo"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"UK 30A",67108912,"UK30A.ZD2.BMP",2,8,{{0,100,49,0,"Bass"},{0,100,38,0,"Treble"},{0,100,78,0,"Cut"},{0,100,30,0,"Gain"},{0,100,84,0,"VOL"},{0,100,0,0,"Depth"},{0,110,50,0,"Speed"},{0,8,2,0,"SOLO"}}},
{"UpOctBSTR",50331968,"UPOCTBST.ZD2.BMP",1,4,{{0,100,65,0,"UpOct"},{0,100,47,0,"DryMx"},{0,100,75,0,"Bottom"},{0,100,70,0,"PRSNC"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"Vibrato",100663408,"VIBRATO.ZD2.BMP",1,4,{{0,100,40,0,"Depth"},{0,78,30,0,"Rate"},{0,10,7,0,"Tone"},{0,100,72,0,"BAL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"VinFLNGR",100663376,"VINFLNGR.ZD2.BMP",1,4,{{0,50,4,0,"PreD"},{0,100,47,0,"Depth"},{0,78,7,0,"Rate"},{0,20,18,0,"RESO"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"VioletDST",50332048,"VIOLETDS.ZD2.BMP",1,4,{{0,100,70,0,"Gain"},{0,100,80,0,"Tone"},{0,2,2,0,"Voice"},{0,100,70,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"VoiceWah",184549584,"VOICE_WH.ZD2.BMP",1,4,{{1,100,0,0,"Vowel"},{0,2,1,0,"PTTRN"},{0,100,50,0,"Voice"},{0,1,0,0,"Mode"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"WAH100",184549440,"WH100.ZD2.BMP",1,4,{{1,50,25,0,"FREQ"},{0,100,40,0,"Depth"},{0,100,0,0,"Dry"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"WarpPhase",100663648,"WRPPHASE.ZD2.BMP",1,4,{{0,1,0,0,"Mode"},{0,77,24,0,"Speed"},{0,10,7,0,"RESO"},{0,100,80,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"XtasyBlue",67108944,"XTACYBLU.ZD2.BMP",2,8,{{0,100,50,0,"Bass"},{0,100,50,0,"MID"},{0,100,50,0,"Treble"},{0,100,40,0,"PRSNC"},{0,1,1,0,"STRCT"},{0,100,60,0,"Gain"},{0,100,42,0,"VOL"},{0,8,2,0,"SOLO"}}},
{"Zen O.DRV",50332016,"ZEN_DRV.ZD2.BMP",1,4,{{0,100,70,0,"Gain"},{0,100,60,0,"Tone"},{0,100,80,0,"Voice"},{0,100,70,0,"VOL"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}},
{"ZNR",16777280,"ZNR.ZD2.BMP",1,4,{{0,1,1,0,"DETCT"},{0,100,100,0,"Depth"},{0,100,30,0,"THRSH"},{0,100,0,0,"Decay"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"},{0,0,0,0,"-"}}}
};
#define N_X_PEDALS 17
long xpedal_ids[]={184549408,184549424,184549568,184549616,184549536,184549504,184549632,184549472,184549520,184549456,192938016,184549552,184549600,184549488,184549392,184549584,184549440};
#endif