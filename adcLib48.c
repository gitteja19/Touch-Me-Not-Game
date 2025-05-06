#include <lpc214x.h>
#include "adcLib48.h"

void initAdc48(u8 adc){
	//set CLKDIV
	if(!adc){
		AD0CR=0X00000000;
		AD0CR=((CLKDIV<<CLKDIV_BITS)|(1<<PDN_BIT));
	}else if(adc==1){
		AD1CR=0X00000000;
		AD1CR=((CLKDIV<<CLKDIV_BITS)|(1<<PDN_BIT));
	}
	
}

f32 analogReadAdc48(u8 adc,u8 chn){
	return (ADC_STEP*(f32)(digitalReadAdc48(adc,chn)));
}


u32 digitalReadAdc48(u8 adc,u8 chn){
	//mask SEL & set SEL,START
	//chn :[0-7]
	if(!adc){
		AD0CR&=0xFFFFFF00;
		AD0CR|=((1<<chn)|(1<<START_BITS));
		while(!((AD0GDR>>DONE_BIT)&1));//wait for conversion
		AD0CR&=~(1<<START_BITS);//stop adc
		return ((AD0GDR>>RESULT_BITS)&0x3FF);
		
	}else if(adc==1){
		AD1CR&=0xFFFFFF00;
		AD1CR|=((1<<chn)|(1<<START_BITS));
		while(!((AD1GDR>>DONE_BIT)&1));//wait for conversion
		AD1CR&=~(1<<START_BITS);//stop adc
		return ((AD1GDR>>RESULT_BITS)&0x3FF);
	}
	return 0;
}
