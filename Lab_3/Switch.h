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

//Used in main.c
extern int ENT;
extern int MENU;
//PF0: MENU
//PF1: Blink to process Menu
//PF2: Blink to process Enter
//PF3: Heartbeat
//PF4: ENT
void GPIO_PortF_Init(void);

//*****************GPIOPortF_Handler*****************
//Waits 10, adds 1 to whichever option pressed (PF0: MENU, PF4:ENT)
//When both rising and falling edges triggered, send 1 to MENU/ENT
//Didn't use IBE_R&=!0x11 because launchpad would occassionally register
//both edges
void GPIOPortF_Handler(void);
