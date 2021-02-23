//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********Switch.c**********
//Lab Authors: Kyubum Shim & Zohan Marediya
//Responsible: Kyubum Shim
//Initial Creation Date: 21.02.09
//EE445L Lab 02 Module for Button Interrupt
//Lab Session: 17240
//TA: Blake Margolis
//Previous: 7Seg
//Final Update: 21.02.13
//Hardware Usage: PF0:4 Pins
//PF0: SW1, PF4: SW2
//PF1: SW1 Ack, PF2: SW2 Ack, PF3: timer heartbeat

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Switch.h"
#include "../inc/ST7735.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/PLL.h"
#include "../inc/LaunchPad.h"
#include "../inc/CortexM.h"
#include "../inc/TExaS.h"

//Global Variable ENT & MENU, used in main.c
int ENT;
int MENU;

//PF1: Blink to process Menu
//PF2: Blink to process Enter
//PF3: Heartbeat
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//GPIO_PortF_Init block
void GPIO_PortF_Init(void){
	uint32_t volatile delay;
	SYSCTL_RCGCGPIO_R|=0x00000020; //Activate clk for PortF
	delay = SYSCTL_RCGCGPIO_R;

	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	
	//GPIO_PORTF_AMSEL_R = 0x00;  //Disable analog
	//GPIO_PORTF_DIR_R &=~0x00000011; 	//Make PF4, PF0 in
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_DIR_R |= 0x0E;		//
	GPIO_PORTF_DEN_R =0x1F;		//Digital I/O on PF0,4	
	GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4,0
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive
	//Done on purpose \/  
  GPIO_PORTF_IBE_R |= 0x11;    //     PF4,PF0 are both edges
  GPIO_PORTF_ICR_R |= 0x11;      // (e) clear flags 4,0
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 2

  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
	
	
 }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 //GPIOPortF_Handler block
 
 
 //*****************DelayMS*****************
//From Dr. Valvano's Launchpad.c
//  - busy wait n milliseconds
// Input: time to wait in msec
// Outputs: none
void static DelayMs(uint32_t n){
  volatile uint32_t time;
  while(n){
    time = 6665;  // 1msec, tuned at 80 MHz
    while(time){
      time--;
    }
    n--;
  }
}


//*****************GPIOPortF_Handler*****************
//Waits 10, adds 1 to whichever option pressed (PF0: MENU, PF4:ENT)
//When both rising and falling edges triggered, send 1 to MENU/ENT
//Didn't use IBE_R&=!0x11 because launchpad would occassionally register
//both edges
void GPIOPortF_Handler(void){
	static int menuCounter=0;
	static int enterCounter=0;
	//PF0 Pressed: MENU
	DelayMs(10);
	if((GPIO_PORTF_RIS_R&0x10)){
		GPIO_PORTF_ICR_R=0x00000010; //Acknowledge flag
		menuCounter+=1;
		enterCounter=0;
		PF1^=0x02;
	}
	//PF4 Pressed: ENT
	else if((GPIO_PORTF_RIS_R&0x01)){
		GPIO_PORTF_ICR_R=0x00000001; //Acknowledge flag
		menuCounter=0;
		enterCounter+=1;
		PF2^=0x04;
	}
	MENU=menuCounter%2;
	ENT=enterCounter%2;
		
}

