//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//***********LineDrawer.h***********
//Lab Authors: Kyubum Shim & Zohan Marediya
//Responsible: Kyubum Shim
//Initial Creation Date: 21.02.09
//EE445L Lab 02 Module for drawing thick lines
//Lab Session: 17240
//TA: Blake Margolis
//Previously LCD.c
//Final Update: 21.02.10
//Hardware Usage: ST7735 Pins

//************* ST7735_DrawFatPixel****************
//input of x,y axis and color
//Draws 4 pixels instead of 1
void ST7735_DrawFatPixel(uint16_t x, uint16_t y, uint16_t color);

//************* ST7735_DrawFatPin****************
//input of x,y axis and color
//Draws central pin to keep analog hands in place
void ST7735_DrawFatPin(uint16_t x, uint16_t y, uint16_t color);

//************* ST7735_Draw4Lines ***********
//input of x1, x2, y1, y2, and color
//Puts 4 Lines instead of 1
void ST7735_Draw4Lines(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2,uint16_t color);

//************* ST7735_LineDraw********************************************
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
void ST7735_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
