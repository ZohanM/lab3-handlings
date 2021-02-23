//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********Timer1.c*********
//EE445L Lab 02 Module for tracking inactivity and 
//handling timeout
//Kyubum Shim, Zohan Marediya
//Initial Creation Date: February 9, 2021
//Lab Session: Kyubum(17240), Zohan (17235)
//TA: Blake Margolis
//Final Update: February 15, 2021

#include "Timer1.h"
#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>

#define reloadVal 79999999
//79999999->7999999

int inactivityLimit;
int timedoutFlag;
int currentInactivity;

void Timer1_Init(int limit){
	SYSCTL_RCGCTIMER_R |= 0x02; //activate timer1
	TIMER1_CTL_R = 0x00; //disable timer1
	inactivityLimit = limit;
	TIMER1_CFG_R = 0x00; // 32-bit mode
	TIMER1_TAMR_R = 0x02; //periodic mode
	TIMER1_TAILR_R = reloadVal; //1 sec interrupts
	TIMER1_TAPR_R = 0x00; //no prescale
	TIMER1_ICR_R = 0x01; //clear interrupt flag
	TIMER1_IMR_R |= 0x01; // arm timer1 interrupt
	
	NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF0FFF)|0x00004000; //Priority 1 for now, change it later
	NVIC_EN0_R |= (1 << 21); //enable irq 21 in NVIC
	TIMER1_CTL_R |= 0x01; //enable timer1
}

void Timer1A_Handler(){
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;	//ack interrupt
	currentInactivity++;
	if(currentInactivity == inactivityLimit){
		timedoutFlag = 1;
	}
}

void handleTimeout(int mode){
	if(mode == disableTimeout){
		TIMER1_IMR_R &= 0xFFFFFFFE; //disable interrupt
	}else if(mode == enableTimeout){
		TIMER1_TAV_R = reloadVal;
		TIMER1_IMR_R |= 0x01;
	}else{
		currentInactivity = 0;
		TIMER1_TAV_R = reloadVal;
	}
}
