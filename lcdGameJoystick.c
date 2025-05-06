
#include <stdlib.h>
#include <lpc214x.h>
#include "types.h"
#include "lcdLib.h"
#include "gpioLib.h"
#include "adcLib48.h"
#include "delayLib.h"


//Joystick
//0  -400  --> 0
//400-800  -->-1
//800-1023 --> 1
#define DEADZONE 100
#define JS_HIGHV 2.3
#define JS_LOWV	 0.98
#define JS_HIGH	 800
#define JS_LOW	 400
#define JS_ADC 0	//ADC0
#define VX_CHN 1	//A0.1
#define VY_CHN 2	//A0.2
#define VZ 27		//P1.27

int ofst  = 0;
int reset = 0;
int score = 0;
int frame = 0;

s8 trackRand[LCD_MAX_ROWS][LCD_MAX_COLS];

void addMan(int row,int col){
	static int prevRow=-1,prevCol=-1,prevFrame=-1,i;
	if(row==prevRow && col==prevCol && frame==prevFrame)return;

	
	if(trackRand[row][col]==(s8)255){
		while(READPIN(GPIO1,VZ)){
			moveLcdCursor(0,2);
			str2Lcd("!GAME OVER!");
			//delayMs(100);
			for(i=12000;i;i--)
				if(READPIN(GPIO1,VZ)==0){
					reset=1;
					return;
				}
			moveLcdCursor(0,2);
			str2Lcd("           ");
			for(i=12000;i;i--)
				if(READPIN(GPIO1,VZ)==0){
					reset=1;
					return;
				}
		}
	}
	
	
	if(row!=prevRow){//row change
		moveLcdCursor(row,col);
		char2Lcd(row?3+frame:0+frame);
		moveLcdCursor(!row,col);
		char2Lcd(trackRand[!row][col]);
	}else if(col!=prevCol){//col change
		moveLcdCursor(row,col);
		char2Lcd(row?3+frame:0+frame);
		moveLcdCursor(row,prevCol);
		char2Lcd(prevCol<col?(trackRand[row][col-1]):(trackRand[row][col+1]));
	}else{//frame change
		moveLcdCursor(row,col);
		char2Lcd(row?3+frame:0+frame);
	}
	
	prevRow=row;
	prevCol=col;
	prevFrame=frame;
	
	frame++;
    if(frame>2)frame=0;
}

//
void countdown(){
	int i;
	moveLcdCursor(0,5);
	str2Lcd("READY");
	delayMs(500);
	for(i=3;i>0;i--){
		moveLcdCursor(0,11);
		char2Lcd('0'+i);
		delayMs(500);
	}
	clearLcdDisplay();
}
//
void showScore(){
	moveLcdCursor(0,13);
	char2Lcd(frame%2+6);
	int2Lcd(score);
}
//
void initTrack(){
	int i,j;
	for(i=0;i<LCD_MAX_ROWS;i++)
		for(j=0;j<LCD_MAX_COLS;j++)
			trackRand[i][j]=' ';
}
//
void shiftTrack(){
	int i,j;
	for(i=0;i<LCD_MAX_ROWS;i++)
		for(j=0;j<LCD_MAX_COLS-1;j++)
			trackRand[i][j]=trackRand[i][j+1];
}
//
void dispTrack(){
	int i,j;
	for(i=0;i<LCD_MAX_ROWS;i++){
		moveLcdCursor(i,0);
		for(j=0;j<LCD_MAX_COLS;j++)
			char2Lcd(trackRand[i][j]);
	}
}
//
void addNewTrack(){
    static u32 seed = 0;
    static int lastRow = -1;
    int row, r;

    srand(seed++);
    r = rand()%100;

    if(r<80){//try insert%% 
        if(lastRow!= -1)row=((rand()%100)<40)?lastRow:!lastRow;//same row%%
        else row=rand()%2;

        if(trackRand[!row][LCD_MAX_COLS-2]==(s8)255){
            trackRand[0][LCD_MAX_COLS-1]=' ';
            trackRand[1][LCD_MAX_COLS-1]=' ';
            lastRow= -1;
        } else {
            trackRand[row][LCD_MAX_COLS-1] = 255;
            trackRand[!row][LCD_MAX_COLS-1]=' ';
            lastRow=row;
        }
    }else{
        trackRand[0][LCD_MAX_COLS-1]=' ';
        trackRand[1][LCD_MAX_COLS-1]=' ';
        lastRow= -1;
    }
}


//
void makeNewChars(){
	makeNewCharAt(manUp1,0);
	makeNewCharAt(manUp2,1);
	makeNewCharAt(manUp3,2);
	makeNewCharAt(manDown1,3);
	makeNewCharAt(manDown2,4);
	makeNewCharAt(manDown3,5);
	makeNewCharAt(starFilled,6);
	makeNewCharAt(starHollow,7);
}


//
int main(){
	int i,dly=1000,run=0;
	int x,y,xPrev=-1,yPrev=-1;
	int  row=0,col=0;

	initLcd();
	PINSEL1=((PINSEL1&~(3<<12*2))|(1<<12*2));
	PINSEL1=((PINSEL1&~(3<<13*2))|(1<<13*2));
	initAdc48(AD0);
	initTrack();
	makeNewChars();

	while(1){
		run++;
		shiftTrack();
		addNewTrack();
		dispTrack();
		if(!(run%LCD_MAX_COLS))score++;  // Increase score
		showScore();
		//delayMs(100);
		
		if(dly>300)dly-=10;  // speed up
		for(i=0;i<dly*4;i++){
			x=digitalReadAdc48(AD0,VX_CHN);
			y=digitalReadAdc48(AD0,VY_CHN);
			
			
			x=(x>JS_HIGH?1:(x<JS_LOW?0:-1));
			y=(y>JS_HIGH?1:(y<JS_LOW?0:-1));		
			if(x==-1 && yPrev==-1){
				if(y==1)row=0;
				else if(y==0)row=1;
			}else if(y==-1 && xPrev==-1){
				if(x==1){
					if(col<LCD_MAX_COLS-1)col++;
				}else if(!x){
					if(col)col--;
				}
			}
			addMan(row,col);
			
			xPrev=x,yPrev=y;
			
			if(reset)break;
		}
		if(reset){
			dly=1000,run=0,xPrev=-1,yPrev=-1,row=0,col=0;
			initTrack();
			reset=0;
			continue;
		}
	}
}

//

