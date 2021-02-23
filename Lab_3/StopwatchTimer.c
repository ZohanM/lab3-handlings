//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********StopwatchTimer.c*********
//EE445L Lab 02 Module for using Stopwatch Mode
//Kyubum Shim, Zohan Marediya
//Initial Creation Date: February 9, 2021
//Lab Session: Kyubum(17240), Zohan (17235)
//TA: Blake Margolis
//Final Update: February 15, 2021

#include "StopwatchTimer.h"
#include "local/tm4c123gh6pm.h"
#include <stdint.h>

#define reloadVal 79999999

int stopwatchFlag = 0;

void StopwatchTimer_Init(void){
	SYSCTL_RCGCTIMER_R |= 0x04; //activate timer2
	TIMER2_CTL_R = 0x00; //disable timer2
	TIMER2_CFG_R = 0x00; // 32-bit mode
	TIMER2_TAMR_R = 0x02; //periodic mode
	TIMER2_TAILR_R = reloadVal; //1 sec interrupts
	TIMER2_TAPR_R = 0x00; //no prescale
	TIMER2_ICR_R = 0x01; //clear interrupt flag
//	TIMER2_IMR_R |= 0x01; // arm timer2 interrupt
	
	NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x60000000; //priority 3
	NVIC_EN0_R |= (1 << 23); //enable irq 23 in NVIC
}

void Timer2A_Handler(void){
	TIMER2_ICR_R = TIMER_ICR_TATOCINT;	//ack interrupt
	stopwatchFlag = 1;
}

void turnOnStopwatch(void){
	TIMER2_CTL_R = 0x00;
	TIMER2_TAV_R = reloadVal;
	TIMER2_IMR_R |= 0x01;
}

void turnOffStopwatch(void){
	TIMER2_IMR_R &= 0xFFFFFFFE;
	stopwatchFlag = 0;
	TIMER2_CTL_R = 0x00;
}

void startStopwatch(void){
	TIMER2_CTL_R |= 0x01;
}

void stopStopwatch(void){
	TIMER2_CTL_R = 0x00;
}
