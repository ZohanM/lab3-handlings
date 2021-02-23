//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********Timer1.h*********
//EE445L Lab 02 Module for tracking inactivity and 
//handling timeout
//Kyubum Shim, Zohan Marediya
//Initial Creation Date: February 9, 2021
//Lab Session: Kyubum(17240), Zohan (17235)
//TA: Blake Margolis
//Final Update: February 15, 2021

#ifndef _TIMER1_H
#define _TIMER1_H

extern int inactivityLimit;
extern int timedoutFlag;

enum timeoutModes{disableTimeout, enableTimeout, resetTimeout};

void Timer1_Init(int);

void Timer1A_Handler(void);

void handleTimeout(int);
#endif
