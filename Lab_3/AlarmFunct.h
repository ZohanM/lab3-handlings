//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********AlarmFunct.c**********
//Lab Authors: Kyubum Shim & Zohan Marediya
//Initial Creation Date: 21.02.09
//EE445L Lab 02 Module for Sound output
//Lab Session: 17240
//TA: Blake Margolis
//Previously LCD.c
//Final Update: 21.02.10
//Hardware Usage: ST7735 Pins

#ifndef _ALARMFUNCT_H
#define _ALARMFUNCT_H

//************* AlarmFunct.h*********
#include <stdint.h>
//Uses Systick
void Sound_Init(uint32_t period);
	
//Systick will send either 0 or 1 for Sound_Out
void Sound_Out(uint32_t data);

//0 = off 1 = on
void Sound_Set(uint8_t setting);
#endif
