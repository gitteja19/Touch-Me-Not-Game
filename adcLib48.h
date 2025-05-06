
#ifndef _ADCLIB48_H
#define _ADCLIB48_H

#include "types.h"

#define AD0 0
#define AD1 1

///* A/D Converter 0 (AD0) */
//#define AD0CR           (*((volatile unsigned long *) 0xE0034000))
//#define AD0DR          ((vu32*)(0xE0034010))
//	

///* A/D Converter 1 (AD1) */
//#define AD1CR           (*((volatile unsigned long *) 0xE0060000))
//#define AD1DR          ((vu32*)(0xE0060010))

#define VDDA 3.3
#define ADC_STEP (VDDA/1023)

//clocks
#define FOSC	12000000	//12MHz
#define CCLK 	(5*FOSC) 	//60MHz
#define PCLK 	(CCLK/4)	//15MHz
#define ADC_CLK 3000000		//03MHz

//sfr-ADxCR macros
#define CLKDIV		((PCLK/ADC_CLK)-1)
#define CLKDIV_BITS 8	//15-8
#define PDN_BIT 	21
#define START_BITS 	24 	//26-24
#define BURST_BIT 	16

//sfr-ADxDRy macros
#define RESULT_BITS 6  //15-6
#define CHN_BITS 	24 //26-24
#define DONE_BIT	31 //
#define OVRN_BIT	30 //

//Analog functions
void initAdc48(u8);
f32 analogReadAdc48(u8,u8);
u32 digitalReadAdc48(u8,u8);



#endif
