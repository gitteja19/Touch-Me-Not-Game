
#ifndef _LCDLIB_H
#define _LCDLIB_H

#include "types.h"

#define LCD_PINS_4B 20 	//@p1.[23-20]:D[7-4]
#define LCD_PINS_8B 16 	//@p1.[23-16]:D[7-0]

#define LCD_RS 	16		//@p0.16
#define LCD_RW 	26 		//@p1.26
#define LCD_EN 	17		//@p0.17

#define LCD_DATA 1
#define LCD_CMD  0
#define LCD_INT 2

//4-Bit mode
#define LCD 32		//16*2
#define LCD_MODE 8  //8 for 8-bit mode

//*****command hex macros*****//
//funcn set
#define LCD_INIT8 0x30
#define LCD_INIT4 0x20
//basic
#define LCD_CLR 0x01
#define LCD_HOMECUR 0x02
//SET CURSOR move direction
#define LCD_SETCURINC 0x06
#define LCD_SETDISPSHIFT 0x05
//cursor/display/blynk
#define LCD_DISPON 0x0C
#define LCD_DISPON_BLKON 0x0D
#define LCD_DISPON_CURON 0x0E
#define LCD_DISPON_CURON_BLKON 0x0F
//move cursor/shift display
//-shift cur/disp by 1 char l/r
#define LCD_DISPSHIFT_R 0x1C
#define LCD_DISPSHIFT_L 0x18
#define LCD_CURSHIFT_R 	0x14
#define LCD_CURSHIFT_L 	0x10
//interface
#if LCD_MODE==8
#define LCD_16x1 0x30
#define LCD_16x2 0x3C//0x3C,0x38 - big,small
#define LCD_20x4 0x38
#elif LCD_MODE==4
#define LCD_16x1 0x20
#define LCD_16x2 0x28
#define LCD_20x4 0x28
#endif

#if LCD==16
	#define LCD_DIM LCD_16x1
	#define LCD_MAX_ROWS 1
	#define LCD_MAX_COLS 16
#elif LCD==32
	#define LCD_DIM LCD_16x2
	#define LCD_MAX_ROWS 2
	#define LCD_MAX_COLS 16
#elif LCD==80
	#define LCD_DIM LCD_20x4
	#define LCD_MAX_ROWS 4
	#define LCD_MAX_COLS 20
#endif



//cursor to CGRAM
#define LCD_CGRAM 0x40
//cursor to DDRAM/display
#define LCD_ROW0 0x80//0x80|0x00
#define LCD_ROW1 0xC0//0x80|0x40
#define LCD_ROW2 0x94//0x80|0x14
#define LCD_ROW3 0xD4//0x80|0x54
//***

//custom chars
extern const s8 bell[];
extern const s8 heartNull[];
extern const s8 heartFull[];
extern const s8 manDown[];
extern const s8 manUp[];
extern const s8 manUp1[];
extern const s8 manUp2[];
extern const s8 manUp3[];
extern const s8 manDown1[];
extern const s8 manDown2[];
extern const s8 manDown3[];

extern const s8 scoreIcon1[];
extern const s8 scoreIcon2[];

extern const s8 unlockIcon[];
extern const s8 lockIcon[];

extern const s8 intruderIcon[];

extern const s8 starHollow[]; 
extern const s8 starFilled[];

extern const s8 manNeut[];
extern const s8 nazi[];
extern const s8 rightArw[];
extern const s8 leftArw[];
extern const s8 upArw[];
extern const s8 downArw[];
extern const s8 bat0[];
extern const s8 bat1[];
extern const s8 bat2[];
extern const s8 bat3[];
extern const s8 bat4[];
extern const s8 bat5[];

//*****FUNCTION DECLARATIONS*****
/*
void initLcd4Bit(void);
void writeLcd4Bit(u8 word,u8 dc);
void lcdString4BitPos(s8 *str,u8 row);
void lcdChar4BitPos(u8 ch,u8 row,u8 col);

void initLcd8Bit(void);
void writeLcd8Bit(u8 word,u8 dc);
void lcdString8BitPos(s8 *str,u8 row);
void lcdChar8BitPos(u8 ch,u8 row,u8 col);
*/
	
void initLcd(void);
void writeLcd(s8 word,s16 dc);
void moveLcdCursor(s16 row,s16 col);
void makeNewCharAt(const s8 *pixels,s16 asc);

void char2Lcd(s8 ch);
void str2Lcd(const s8 *str);
void int2Lcd(s32 inum);
void uInt2Lcd(u32 inum);
void flt2Lcd(f32 fnum);
void f32StrLcd(f32);

void str2LcdPos(s8 *str,s16 row,s16 col);
void char2LcdPos(s8 ch,s16 row,s16 col);

void clearLcdDisplay(void);
void clearLcdRow(s16 row);

//special
void bin2Lcd(u32 n,s16 bits);
void hex2Lcd(u32 n);
void oct2Lcd(u32 n);
void scrllStr2Lcd(s8 *str,s16 row);

#endif
