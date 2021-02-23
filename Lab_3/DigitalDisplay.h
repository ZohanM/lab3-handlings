//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********DigitalDisplay.h**********
//Lab Authors: Kyubum Shim & Zohan Marediya
//Responsible: Kyubum Shim
//Initial Creation Date: 21.02.09
//EE445L Lab 02 Module for Analog Clock Display
//Lab Session: 17240
//TA: Blake Margolis
//Previous: 7Seg
//Final Update: 21.02.09
//Hardware Usage: ST7735 Pins

//************* ST7735_DrawDigital*********
//input: time (as seconds)
//Main program for drawing the digital clock
//Doesn't account for overflow of t=86400 (24+hrs)
void ST7735_DrawDigital(int time,int update);
