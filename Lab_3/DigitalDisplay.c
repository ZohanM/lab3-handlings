//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********DigitalDisplay.c**********
//Lab Authors: Kyubum Shim & Zohan Marediya
//Responsible: Kyubum Shim
//Initial Creation Date: 21.02.09
//EE445L Lab 02 Module for Digital Clock Display
//Lab Session: 17240
//TA: Blake Margolis
//Previous: 7Seg
//Final Update: 21.02.13
//Hardware Usage: ST7735 Pins

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "LineDrawer.h"
#include "DigitalDisplay.h"
#include "local/ST7735.h"
#include "local/tm4c123gh6pm.h"

const int offsetX1=2;
const int offsetX2=18;
const int offsetY1=20;
const int offsetY2=30;
const int offsetY3=40;
const int digitHr1X=10;
const int digitHr2X=30;
const int colonX1=60;
const int digitMn1X=70;
const int digitMn2X=90;
const int colonX2=40;
const int digitSc1X=45;
const int digitSc2X=65;


const int colonUpperY=26;
const int colonLowerY=34;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//************* ST7735_DrawX*************
//  Draws one digit using ST7735_DrawLine
//input: digit offset (12:34:56), writing color(white/black)
void ST7735_Draw0(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY3,color);
}

void ST7735_Draw1(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw2(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX1,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw3(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw4(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw5(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw6(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw7(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw8(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

void ST7735_Draw9(int digitOffset, int vertOffset, uint16_t color){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,color);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY2,color);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,color);
}

//********** ST7735_EraseAll**********
//input: digit offset (12:34), erase any trace
void ST7735_EraseAll(int digitOffset, int vertOffset){
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY1,ST7735_BLACK);
	ST7735_DrawLine(digitOffset+offsetX2,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,ST7735_BLACK);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY2,digitOffset+offsetX2,vertOffset+offsetY2,ST7735_BLACK);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX1,vertOffset+offsetY3,ST7735_BLACK);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY3,digitOffset+offsetX2,vertOffset+offsetY3,ST7735_BLACK);
	ST7735_DrawLine(digitOffset+offsetX1,vertOffset+offsetY1,digitOffset+offsetX2,vertOffset+offsetY3,ST7735_BLACK);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********ST7735_Draw7Seg***********
//input: digit, digit place(12:34), write(1=write in white, 0= erase in black)
//case 0:10; 0:9 for digit writing, 10 for erasing all, inc diagonal from white
void ST7735_Draw7Seg(int digit, int digitPlace, int write){
	int vertOffset=0;
	if(digitPlace>4) vertOffset=40;
	
	int digitOffset=digitHr1X;
	if(digitPlace==2) digitOffset=digitHr2X;
	else if (digitPlace==3) digitOffset=digitMn1X;
	else if(digitPlace==4) digitOffset=digitMn2X;
	else if (digitPlace==5) digitOffset=digitSc1X;
	else if (digitPlace==6) digitOffset=digitSc2X;
	uint16_t color=ST7735_WHITE;
	if(!write) color=ST7735_BLACK;
	
	switch(digit){
		case 0:
			ST7735_Draw0(digitOffset,vertOffset,color);
			break;	
		case 1:
			ST7735_Draw1(digitOffset,vertOffset,color);
			break;
		case 2:
			ST7735_Draw2(digitOffset,vertOffset,color);
			break;
		case 3:
			ST7735_Draw3(digitOffset,vertOffset,color);
			break;
		case 4:
			ST7735_Draw4(digitOffset,vertOffset,color);
			break;
		case 5:
			ST7735_Draw5(digitOffset,vertOffset,color);
			break;
		case 6:
			ST7735_Draw6(digitOffset,vertOffset,color);
			break;
		case 7:
			ST7735_Draw7(digitOffset,vertOffset,color);
			break;
		case 8:
			ST7735_Draw8(digitOffset,vertOffset,color);
			break;
		case 9:
			ST7735_Draw9(digitOffset,vertOffset,color);
			break;
		case 10:
			ST7735_EraseAll(digitOffset,vertOffset);
		break;
		default:
			ST7735_Draw0(digitOffset,vertOffset,color);			
	}
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//prevTime counter for checking if time update is required
//{hr1, hr2, mn1, mn2}
int prevTime[6]={11,11,11,11,11,11};

//************* ST7735_DrawDigital*******************
//input: time
//Main program for drawing the digital clock
//Doesn't account for overflow of t=86400 (24+hrs)
//Utilizes prevTime[4]

void ST7735_DrawDigital(int time, int update){
	int hr1=(((time/3600))/10);
	int hr2=((time/3600))%10;
	int mn1=(((time/60))%60)/10;
	int mn2=(((time/60))%60)%10;
	int sc1=(((time)%60))/10;
	int sc2=(((time))%60)%10;
	//Erase if time diff, update
	if(update){
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_Draw7Seg(hr1,1,1);
		ST7735_Draw7Seg(hr2,2,1);
		ST7735_DrawFatPixel(colonX1,colonUpperY,ST7735_WHITE);
		ST7735_DrawFatPixel(colonX1,colonLowerY,ST7735_WHITE);
		ST7735_Draw7Seg(mn1,3,1);
		ST7735_Draw7Seg(mn2,4,1);
		ST7735_DrawFatPixel(colonX2,colonUpperY+40,ST7735_WHITE);
		ST7735_DrawFatPixel(colonX2,colonLowerY+40,ST7735_WHITE);
		ST7735_Draw7Seg(sc1,5,1);
		ST7735_Draw7Seg(sc2,6,1);
	}
	
	else{	
		if(prevTime[0]!=hr1){
			ST7735_Draw7Seg(10,1,0);
			ST7735_Draw7Seg(hr1,1,1);
		}
		if(prevTime[1]!=hr2){ 
			ST7735_Draw7Seg(10,2,0);
			ST7735_Draw7Seg(hr2,2,1);
		}
		ST7735_DrawFatPixel(colonX1,colonUpperY,ST7735_WHITE);
		ST7735_DrawFatPixel(colonX1,colonLowerY,ST7735_WHITE);
		if(prevTime[2]!=mn1){
			ST7735_Draw7Seg(10,3,0);	
			ST7735_Draw7Seg(mn1,3,1);
		}
		if(prevTime[3]!=mn2){
			ST7735_Draw7Seg(10,4,0);
			ST7735_Draw7Seg(mn2,4,1);
		}
		ST7735_DrawFatPixel(colonX2,colonUpperY+40,ST7735_WHITE);
		ST7735_DrawFatPixel(colonX2,colonLowerY+40,ST7735_WHITE);
		if(prevTime[4]!=sc1){
			ST7735_Draw7Seg(10,5,0);	
			ST7735_Draw7Seg(sc1,5,1);
		}
		if(prevTime[5]!=sc2){
			ST7735_Draw7Seg(10,6,0);
			ST7735_Draw7Seg(sc2,6,1);
		}	
	}	
	prevTime[0]=hr1;
	prevTime[1]=hr2;
	prevTime[2]=mn1;
	prevTime[3]=mn2;
	prevTime[4]=sc1;
	prevTime[5]=sc2;
}

