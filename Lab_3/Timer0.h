//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********Timer0.h*********
//EE445L Lab 02 Module for managing time
//Kyubum Shim, Zohan Marediya
//Initial Creation Date: February 9, 2021
//Lab Session: Kyubum(17240), Zohan (17235)
//TA: Blake Margolis
//Final Update: February 15, 2021

#ifndef _TIMER_H
#define _TIMER_H

#include "local/tm4c123gh6pm.h"

typedef struct time{
	int hour;
	int minute;
	int second;
}Time;

extern Time currentTime;
extern int timeFlag;

void Timer0_Init(void);	//initializes the timer used for TIME
void Timer0_Handler(void); //handles and manages the TIME
#endif
