#define PI 3.14


//************* ST7735_Draw4Lines ***********
//Puts 4 pixels instead of 1
void ST7735_Draw4Lines(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2,uint16_t color);


//************* ST7735_LineDraw********************************************
//  Draws one line on the ST7735 color LCD
void ST7735_LineDraw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);



void ST7735_drawClockFace(void);

void ST7735_drawHand(int time,int draw);
