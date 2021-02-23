//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//***********LineDrawer.c***********
//Lab Authors: Kyubum Shim & Zohan Marediya
//Responsible: Kyubum Shim
//Initial Creation Date: 21.02.09
//EE445L Lab 02 Module for drawing thick lines
//Lab Session: 17240
//TA: Blake Margolis
//Previously LCD.c
//Final Update: 21.02.10
//Hardware Usage: ST7735 Pins


#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "LineDrawer.h"
#include "../inc/ST7735.h"
#include "../inc/tm4c123gh6pm.h"

void ST7735_LineDraw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

//************* ST7735_DrawFatPixel****************
//input of x,y axis and color
//Draws 4 pixels instead of 1
void ST7735_DrawFatPixel(uint16_t x, uint16_t y, uint16_t color){
	ST7735_DrawPixel(x,y,color);
	ST7735_DrawPixel(x+1,y,color);
	ST7735_DrawPixel(x,y+1,color);
	ST7735_DrawPixel(x+1,y+1,color);
}


//************* ST7735_DrawFatPin****************
//input of x,y axis and color
//Draws central pin to keep analog hands in place
void ST7735_DrawFatPin(uint16_t x, uint16_t y, uint16_t color){
	ST7735_DrawFatPixel(x,y,color);
	ST7735_DrawFatPixel(x+4,y,color);
	ST7735_DrawFatPixel(x,y+4,color);
	ST7735_DrawFatPixel(x-4,y,color);
	ST7735_DrawFatPixel(x,y-4,color);
	
}

//************* ST7735_Draw4Lines ***********
//input of x1, x2, y1, y2, and color
//Puts 4 Lines instead of 1
void ST7735_Draw4Lines(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2,uint16_t color){
	ST7735_DrawLine(x1,x2,y1,y2,color);
	ST7735_DrawLine(x1,x2,y1+1,y2+1,color);
	ST7735_DrawLine(x1+1,x2+1,y1,y2,color);
	ST7735_DrawLine(x1+1,x2+1,y1+1,y2+1,color);
}


//************* ST7735_DrawLine********************************************
//  Draws one line on the ST7735 color LCD
//  Inputs: (x1,y1) is the start point
//          (x2,y2) is the end point
// x1,x2 are horizontal positions, columns from the left edge
//               must be less than 128
//               0 is on the left, 126 is near the right
// y1,y2 are vertical positions, rows from the top edge
//               must be less than 160
//               159 is near the wires, 0 is the side opposite the wires
//        color 16-bit color, which can be produced by ST7735_Color565() 
// Output: none
void ST7735_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
	//If Vertical
	int wasVert=0;
	if(x1==x2){
		if(y1<y2&&!wasVert)	{
			ST7735_DrawFastVLine(x1,y1,y2-y1,color);
			wasVert=1;
		}
		else if(y1>y2&&!wasVert){ 
			ST7735_DrawFastVLine(x1,y2,y1-y2,color);
			wasVert=1;
		}
		else if(y1==y2&&!wasVert){
			ST7735_DrawFastVLine(x1,y1,y1,color);
			wasVert=0;
		}
		else wasVert=0;
	}
	//If Sloped
	else{
		// if dx is greater than dy  
		if(abs(y2 - y1) < abs(x2 - x1)){ 
			//Set smallX and bigX for less equations
			uint16_t smallX=x1;			uint16_t bigX=x2;
			if(x1 > x2){  smallX=x2;	bigX=x1;}
			
			//Mult b4 div to prevent underflow
			for(int x=smallX;x<bigX;x++) 
				ST7735_DrawPixel(x,y1+(y2-y1)*(x-x1)/(x2-x1),color);
		}
    // if dx is greater than dy  
		else{
			uint16_t smallY=y1;		uint16_t bigY=y2;
			if(y1 > y2){	smallY=y2; bigY=y1;}
			
			//Mult b4 div to prevent underflow
			for(int y=smallY;y<bigY;y++) 
				ST7735_DrawPixel(x1+(x2-x1)*(y-y1)/(y2-y1),y,color);
    
		}
  }
}

