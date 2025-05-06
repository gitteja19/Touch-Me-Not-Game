#include "types.h"
#include "delayLib.h"
#include "gpioLib.h"
#include "lcdLib.h"



//custom pixies
const s8 bell[]		={0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
const s8 heartNull[]={0x00,0x0A,0x15,0x11,0x11,0x0A,0x04,0x00};
const s8 heartFull[]={0x00,0x0A,0x1F,0x1F,0x1F,0x0E,0x04,0x00};
const s8 manDown[]	={0x0E,0x0E,0x04,0x0E,0x15,0x04,0x0A,0x0A};
const s8 manUp[]	={0x0E,0x0E,0x15,0x0E,0x04,0x04,0x0A,0x11};

const s8 manUp1[]={0x0E,0x0E,0x15,0x0E,0x04,0x04,0x0A,0x11}; // Initial
const s8 manUp2[]={0x0E,0x0E,0x04,0x0E,0x15,0x0A,0x04,0x11}; // Right hand forward
const s8 manUp3[]={0x0E,0x0E,0x15,0x0E,0x04,0x11,0x0A,0x04}; // Left hand forward

const s8 manDown1[]={0x0E,0x0E,0x04,0x0E,0x15,0x04,0x0A,0x0A}; // Initial
const s8 manDown2[]={0x0E,0x0E,0x04,0x0E,0x15,0x04,0x11,0x04}; // One leg up
const s8 manDown3[]={0x0E,0x0E,0x04,0x0E,0x15,0x04,0x04,0x11}; // Other leg up

const s8 scoreIcon1[]={0x1C,0x3E,0x7F,0x7F,0x7F,0x3E,0x1C,0x00}; // Frame 1
const s8 scoreIcon2[]={0x1C,0x3E,0x7F,0x7F,0x7F,0x3E,0x1C,0x00}; // Frame 2

const s8 lockIcon[]  ={0x00,0x0E,0x11,0x1F,0x15,0x1F,0x1F,0x00};
const s8 unlockIcon[]={0x0E,0x11,0x01,0x1F,0x15,0x1F,0x1F,0x00};

const s8 intruderIcon[]={0x0E,0x15,0x15,0x04,0x0A,0x11,0x0E,0x00};


const s8 starHollow[]={0x04,0x0E,0x15,0x04,0x15,0x0E,0x04,0x00}; 
const s8 starFilled[]={0x04,0x0E,0x1F,0x0E,0x1F,0x0E,0x04,0x00}; 


const s8 manNeut[]	={0x0E,0x0E,0x04,0x0E,0x15,0x04,0x0A,0x0A};//NOT DONE
const s8 nazi[]		={0x0E,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F};//NOT DONE
const s8 rightArw[]	={0x00,0x04,0x02,0x1F,0x02,0x04,0x00,0x00};
const s8 leftArw[]	={0x00,0x04,0x08,0x1F,0x08,0x04,0x00,0x00};
const s8 upArw[]	={0x04,0x0E,0x15,0x04,0x04,0x04,0x04,0x00};
const s8 downArw[]	={0x04,0x04,0x04,0x04,0x15,0x0E,0x04,0x00};
const s8 bat0[]		={0x0E,0x1F,0x11,0x11,0x11,0x11,0x11,0x1F};
const s8 bat1[]		={0x0E,0x1F,0x11,0x11,0x11,0x11,0x1F,0x1F};
const s8 bat2[]		={0x0E,0x1F,0x11,0x11,0x11,0x1F,0x1F,0x1F};
const s8 bat3[]		={0x0E,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F};
const s8 bat4[]		={0x0E,0x1F,0x11,0x1F,0x1F,0x1F,0x1F,0x1F};
const s8 bat5[]		={0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};

 /*
/////4 BIT MODE
void initLcd4Bit(){
	//start
	delayMs(50);
	//8Bit-function set
	writeLcd4Bit(0x03,CMD);
	delayMs(5);
	//8Bit-function set
	writeLcd4Bit(0x03,CMD);
	delayMs(1);
	//8Bit-function set
	writeLcd4Bit(0x03,CMD);
	
	//4Bit-function set
	writeLcd4Bit(0x02,CMD);
	
	//4Bit,row,line - FS
	writeLcd4Bit(0x28,CMD);
	//Display,Cursor,Block ON/OFF
	writeLcd4Bit(0x0C,CMD);
	//clear Display
	writeLcd4Bit(0x01,CMD);
//Entry Mode
	writeLcd4Bit(0x06,CMD);
	delayMs(1);
}

//
void writeLcd4Bit(u8 word,u8 dc){
	//data or cmd
	if(dc)SETPIN(GPIO1,RS);//dc=1->DATA
	else  CLRPIN(GPIO1,RS);//dc=0->CMD
	//write upper nibble
	WRITE4PINS(GPIO1,LCDPINS_4B,(word >> 4));
	//pulse to notify LCD
	SETPIN(GPIO1,EN);
	delayMs(1);
	CLRPIN(GPIO1,EN);
	//write lower nibble
	WRITE4PINS(GPIO1,LCDPINS_4B,(word & 0x0F));
	//pulse to notify LCD
	SETPIN(GPIO1,EN);
	delayMs(1);
	CLRPIN(GPIO1,EN);
	//wait to process
	delayMs(1);
}
//
void lcdString4BitPos(s8 *str,u8 row){
	if(row==0)writeLcd8Bit(0x80|ROW0,CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd8Bit(0x80|ROW1,CMD);	//go to row2
    while(*str){
        writeLcd4Bit(*str++,DATA);
    }
}
//
void lcdChar4BitPos(u8 ch,u8 row,u8 col){
	//col [0-15]
	if(row==0)writeLcd8Bit(0x80|(ROW0+col),CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd8Bit(0x80|(ROW1+col),CMD);	//go to row2
	writeLcd4Bit(ch,DATA);
}
//

/////8 BIT MODE
void initLcd8Bit(){
	//start
	delayMs(50);
	//8Bit-function set
	writeLcd8Bit(0x30,CMD);
	delayMs(5);
	//8Bit-function set
	writeLcd8Bit(0x30,CMD);
	delayMs(1);
	//8Bit-function set
	writeLcd8Bit(0x30,CMD);
	
	
	//8Bit,row,line - FS
	writeLcd8Bit(0x38,CMD);
	//Display,Cursor,Block ON/OFF
	writeLcd8Bit(0x0C,CMD);
	//clear Display
	writeLcd8Bit(0x01,CMD);
	//Entry Mode
	writeLcd8Bit(0x06,CMD);
	delayMs(1);
}
//
void writeLcd8Bit(u8 word,u8 dc){
	//data or cmd
	if(dc)SETPIN(GPIO1,RS);//dc=1->DATA
	else  CLRPIN(GPIO1,RS);//dc=0->CMD
	//WRITE BYTE
	WRITE8PINS(GPIO1,LCDPINS_8B,word);
	//pulse to notify LCD
	SETPIN(GPIO1,EN);
	delayMs(1);
	CLRPIN(GPIO1,EN);
	//wait to process
	delayMs(1);
}
//
void lcdString8BitPos(s8 *str,u8 row){
	if(row==0)writeLcd8Bit(0x80|ROW0,CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd8Bit(0x80|ROW1,CMD);	//go to row2
    while(*str){
        writeLcd8Bit(*str++,DATA);
    }
}
//
void lcdChar8BitPos(u8 ch,u8 row,u8 col){
	//col [0-15]
	if(row==0)writeLcd8Bit(0x80|(ROW0+col),CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd8Bit(0x80|(ROW1+col),CMD);	//go to row2
	writeLcd8Bit(ch,DATA);
}
//
*/

/////GENERAL 
void initLcd(){
	//GPIO cnfg
	//lcd RS pins as gpio_out
	INITPIN(GPIO0,LCD_RS,1);
	//lcd RW pins as gpio_out
	//INITPIN(GPIO1,LCD_RW,1);
	//lcd EN pins as gpio_out
	INITPIN(GPIO0,LCD_EN,1);
#if LCD_MODE==4
	INIT4PINS(GPIO1,LCD_PINS_4B,0xF);
#elif LCD_MODE==8
	INIT8PINS(GPIO1,LCD_PINS_8B,0xFF);
#endif
	////start lcd init
	delayMs(15);
	//8Bit-function set
	writeLcd(LCD_INIT8,LCD_CMD);
	delayMs(5);
	//8Bit-function set
	writeLcd(LCD_INIT8,LCD_CMD);
	delayUs(200);
	//8Bit-function set
	writeLcd(LCD_INIT8,LCD_CMD);
	delayUs(200);
#if LCD_MODE==4
	//4Bit-function set
	writeLcd(LCD_INIT4,LCD_INT);
#endif
	//set interface len
	writeLcd(LCD_DIM,LCD_CMD);
	//Display,Cursor,Block ON/OFF
	writeLcd(LCD_DISPON,LCD_CMD);
	//clear Display
	writeLcd(LCD_CLR,LCD_CMD);
	//Entry Mode
	writeLcd(LCD_SETCURINC,LCD_CMD);
	delayMs(2);
}
//
void writeLcd(s8 word,s16 dc){
	//data or cmd
	if(dc==1)SETPIN(GPIO0,LCD_RS);//dc=1->DATA
	else if(dc==0) CLRPIN(GPIO0,LCD_RS);//dc=0->CMD
	else if(dc==2){//dc=2->INIT
		CLRPIN(GPIO0,LCD_RS);
		//write upper nibble
		WRITE4PINS(GPIO1,LCD_PINS_4B,(word >> 4));
		//pulse to notify LCD
		SETPIN(GPIO0,LCD_EN);
		delayUs(1);
		CLRPIN(GPIO0,LCD_EN);
		return;
	}
#if LCD_MODE==8
	//WRITE BYTE
	WRITE8PINS(GPIO1,LCD_PINS_8B,word);
	//pulse to notify LCD
	SETPIN(GPIO0,LCD_EN);
	delayUs(1);
	CLRPIN(GPIO0,LCD_EN);
#elif LCD_MODE==4
	//write upper nibble
	WRITE4PINS(GPIO1,LCD_PINS_4B,(word >> 4));
	//pulse to notify LCD
	SETPIN(GPIO0,LCD_EN);
	delayUs(1);
	CLRPIN(GPIO0,LCD_EN);
	//write lower nibble
	WRITE4PINS(GPIO1,LCD_PINS_4B,(word & 0x0F));
	//pulse to notify LCD
	SETPIN(GPIO0,LCD_EN);
	delayUs(1);
	CLRPIN(GPIO0,LCD_EN);
#endif
	//wait to process
	//<=30 250khz fail
	delayUs(60);
}
//
void makeNewCharAt(const s8 *pixels,s16 asc){
	u16 i;
	if(asc>8)return;//invalid ascii
	//generate custom char at asc
	writeLcd(LCD_CGRAM+asc*8,LCD_CMD);
	for(i=0;i<8;i++)char2Lcd(pixels[i]);
}
//
void char2Lcd(s8 ch){
	writeLcd(ch,LCD_DATA);
}
//
void str2Lcd(const s8 *str){
	while(*str){
		writeLcd(*(str++),LCD_DATA);	
	}
}
//
void moveLcdCursor(s16 row,s16 col){
	//col [0-15]
	if(row==0)writeLcd(LCD_ROW0+col,LCD_CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd(LCD_ROW1+col,LCD_CMD);	//go to row2
	else if(row==2)writeLcd(LCD_ROW2+col,LCD_CMD);	//go to row3
	else if(row==3)writeLcd(LCD_ROW3+col,LCD_CMD);	//go to row4
}
//
void str2LcdPos(s8 *str,s16 row,s16 col){
	//col [0-15]
	if(row==0)writeLcd((LCD_ROW0+col),LCD_CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd((LCD_ROW1+col),LCD_CMD);	//go to row2
	
	while(*str){
		writeLcd(*(str++),LCD_DATA);	
	}
}
//
void char2LcdPos(s8 ch,s16 row,s16 col){
	//col [0-15]
	if(row==0) writeLcd((LCD_ROW0+col),LCD_CMD);		//go to row1,col
	else if(row==1) writeLcd((LCD_ROW1+col),LCD_CMD);	//go to row2,col
	
	writeLcd(ch,LCD_DATA);
}
//
void clearLcdDisplay(){
    writeLcd(0x01,LCD_CMD);  // Clear display command
    delayMs(2);
}
//
void clearLcdRow(s16 row){
	u8 col;
	//set cursor
	if(row==0)writeLcd(LCD_ROW0,LCD_CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd(LCD_ROW1,LCD_CMD);	//go to row2
	else if(row==2)writeLcd(LCD_ROW2,LCD_CMD);	//go to row3
	else if(row==3)writeLcd(LCD_ROW3,LCD_CMD);	//go to row4
	//clear row
	for(col=0;col<LCD_MAX_COLS;col++){  //columns per row
		writeLcd(' ',LCD_DATA);
    }
	//reset cursor
	if(row==0)writeLcd(LCD_ROW0,LCD_CMD);		//go to row1, addr 0x00  ORed with 0x80: D7 must be set to move cursor
	else if(row==1)writeLcd(LCD_ROW1,LCD_CMD);	//go to row2
	else if(row==2)writeLcd(LCD_ROW2,LCD_CMD);	//go to row3
	else if(row==3)writeLcd(LCD_ROW3,LCD_CMD);	//go to row4
}
//
void int2Lcd(s32 inum){
	//int2str- -1342 : "2431-"
	s8 str[11];
	s16 sign,i;
	sign=0,i=0;
	if(inum<0){
		sign=1;
		inum*=-1;
	}
	do{
		str[i++]='0'+(inum%10);
		inum/=10;
	}while(inum);
	if(sign)str[i++]='-';
	//pf str
	for(--i;i>=0;i--){
		writeLcd(str[i],LCD_DATA);
	}
}
//
void uInt2Lcd(u32 inum){
	//int2arr- -1342 : "2431-"
	s8 str[10];
	s16 i;
	i=0;
	do{
		str[i++]='0'+(inum%10);
		inum/=10;
	}while(inum);

	//pf arr
	for(--i;i>=0;i--){
		writeLcd(str[i],LCD_DATA);
	}
}
//
void flt2Lcd(f32 fnum){
	//max 3 dig after .
	u32 iNum,i;
	if(fnum<0){
		char2Lcd('-');
		fnum=-fnum;
	}
	
	iNum=fnum;
	fnum-=iNum;
	uInt2Lcd(iNum);
	char2Lcd('.');
	for(i=0;i<2;i++){
		fnum*=10;
		iNum= fnum;
		char2Lcd(iNum+'0');
		fnum-=iNum;
	}
}
//
void f32StrLcd(f32 fnum){
	
}
//
void bin2Lcd(u32 num,s16 bits){
	s16 i;
	for(i=bits;i>=0;i--){
		writeLcd(('0'+((num>>i)&1)),LCD_DATA);
	}
}
//
void hex2Lcd(u32 num){
	s8 str[8];
	s16 i,t;
	i=0;
	do{
		t=(num%16);
		if(t<10)str[i++]='0'+t;
		else str[i++]='A'+t-10;
		num/=16;
	}while(num);
	//pf str
	for(--i;i>=0;i--){
		writeLcd(str[i],LCD_DATA);
	}
}
//
void oct2Lcd(u32 num){
	s8 str[8];
	s16 i;
	i=0;
	do{
		str[i++]='0'+(num%8);
		num/=8;
	}while(num);
	//pf str
	for(--i;i>=0;i--){
		writeLcd(str[i],LCD_DATA);
	}
}
//
/*
void scrllStr2Lcd(s8*str,s8 row){
	s32 len=0,i=0,j,k,l;
	s8 *temp=str;
	//strlen implementation
	while(*temp){
		len++;
		temp++;
	}
	//scrlling
	while(1){
		j= 15-((i++)%16);
		moveLcdCursor(row,j);
		//strprint
		if(j){
			//right bound and Normal
			for(k=0;k<16-j;k++){
				if(k>=len)break;
				char2Lcd(str[k]);
			}
			delayMs(200);
			clearLcdRow(row);
		}else if(j==0){
			//left bound
			for(l=0;l<len;l++){
				moveLcdCursor(row,j);
				for(k=0;k<16-j;k++){
					if(k+l>=len)break;
					char2Lcd(str[k+l]);
				}
				delayMs(200);
				clearLcdRow(row);
			}
		}	
		
	}
}
*/
//
void scrllStr2Lcd(s8*str,s16 row){
	s32 len=0,i=0,j,k,l,m;
	s8 *temp=str;
	//strlen implementation
	while(*temp){
		len++;
		temp++;
	}
	//scrlling
	while(1){
		j= LCD_MAX_COLS-1-((i++)%LCD_MAX_COLS);
		//strprint
		if(j){
			//right bound and Normal
			m=1;
		}else if(j==0){
			//left bound
			m=len;
		}
		for(l=0;l<m;l++){
				moveLcdCursor(row,j);
				for(k=0;k<LCD_MAX_COLS-j;k++){
					if(k+l>=len)break;
					char2Lcd(str[k+l]);
				}
				delayMs(60);
				clearLcdRow(row);
			}	
		
	}
}
//
