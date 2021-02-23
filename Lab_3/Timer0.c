//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********Timer0.c*********
//EE445L Lab 02 Module for managing time
//Kyubum Shim, Zohan Marediya
//Initial Creation Date: February 9, 2021
//Lab Session: Kyubum(17240), Zohan (17235)
//TA: Blake Margolis
//Final Update: February 15, 2021

#include "Timer0.h"
#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>

Time currentTime = {0,0,0};
int timeFlag = 0;

void Timer0_Init(void){
	uint32_t volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
	delay=SYSCTL_RCGCTIMER_R;
	
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = 79999999;  // 4) reload value //interrupt every 30 secs
	
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x10000000; // 8) priority 2
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R |= 0x00000001;    // 10) enable TIMER0A
}

void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;
	static int count = 0;
	count++;
	timeFlag ++;
}
