//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********StopwatchTimer.h*********
//EE445L Lab 02 Module for using Stopwatch Mode
//Kyubum Shim, Zohan Marediya
//Initial Creation Date: February 9, 2021
//Lab Session: Kyubum(17240), Zohan (17235)
//TA: Blake Margolis
//Final Update: February 15, 2021

#ifndef _STOPWATCHTIMER_H
#define _STOPWATCHTIMER_H

extern int stopwatchFlag;

void StopwatchTimer_Init(void);

void Timer2A_Init(void);

void turnOnStopwatch(void);

void turnOffStopwatch(void);

void startStopwatch(void);

void stopStopwatch(void);

#endif
