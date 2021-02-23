//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********AnalogDisplay.h**********
//Lab Authors: Kyubum Shim & Zohan Marediya
//Responsible: Kyubum Shim
//Initial Creation Date: 21.02.09
//EE445L Lab 02 Module for Analog Clock Display
//Lab Session: 17240
//TA: Blake Margolis
//Previous: 7Seg
//Final Update: 21.02.14
//Hardware Usage: ST7735 Pins

//**********ST7735_DrawClockFace**********
//Draws Clock Face
void ST7735_DrawClockFace(void);

//**********ST7735_drawAnalog**********
//input: time (as seconds)
//Converts input time to angles, gets the tip of the hour and minute hands
//Draws clock face
//Updates time by erasing previous values(stored in prevPlot {mnY, mnX, hrY, hrX})
//Draws with new values using ST7735_Draw4Lines in ST7735.h
void ST7735_DrawAnalog(int time);
