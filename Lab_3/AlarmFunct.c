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

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "local/tm4c123gh6pm.h"
#include "AlarmFunct.h"

const int A=500;
uint8_t Index=0;
int soundOn = 0;
int count = 0;

//************* PORTD_Init()****************
//DAC PD0 to be used for sound output
//Called by Sound_Init(uint32_t period)
void PortD_Init(){
	SYSCTL_RCGCGPIO_R |= 0x08;
	while((SYSCTL_RCGCGPIO_R & 0x08)==0){};
	GPIO_PORTD_AMSEL_R &= ~0x01;	//PD0 disable analog 
	GPIO_PORTD_PCTL_R &= ~0x0000000F;
	GPIO_PORTD_DIR_R |= 0x01; //PD0 Output
	GPIO_PORTD_AFSEL_R &=~0x01; //PD0 regular function
	GPIO_PORTD_DEN_R |= 0x01; //PD0 digital io
}

//************* Sound_Init()****************
//Input: Period
//Uses Systick, calls PortD_Init()
void Sound_Init(uint32_t period){
	PortD_Init();
	Index=0;
	NVIC_ST_CTRL_R=0; //Disable systick
	NVIC_ST_RELOAD_R = period-1; //Reload
	NVIC_ST_CURRENT_R=0; //Clr
	NVIC_SYS_PRI3_R=(NVIC_SYS_PRI3_R&0x00FFFFFF)|(0x20000000);//Pri 1
	NVIC_ST_CTRL_R |= 0x0007;	//Enable systick w/ core clk & interrupt
}

//************* Sound_Out()****************
//Input: Data out
//Output: PortD0 Sound
//Systick will send either 0 or 1 for Sound_Out
void Sound_Out(uint32_t data){
		if(data == 0){
			GPIO_PORTD_DATA_R &= ~0x01;
		}else{
			GPIO_PORTD_DATA_R |= 0x01;
		}
}

//************* SysTick_Handler()****************
//Systick toggles PD0 on or off
void SysTick_Handler(void){
	count++;
	if(soundOn){
		Sound_Out(count % 2);
	}else{
		Sound_Out(0);
	}
}

void Sound_Set(uint8_t setting){
	soundOn = setting % 2;
}
