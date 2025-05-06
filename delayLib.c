//software delays library
#include "types.h"
const u32 CC =60000000; //12MHz

void delayS(u32 dly){
	dly*=12000000;
	//dly*=(CC/5);
	while(dly--);
}

void delayMs(u32 dly){
	dly*=12000;
	//dly*=(CC/5000);
	while(dly--);
}

void delayUs(u32 dly){
	dly*=12;
	//dly*=(CC/5000000);
	while(dly--);
}
