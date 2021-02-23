//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//**********main.c*********
//EE445L Lab 02 main program for managing all modules
//and creating a clock with the added functionality of
//handling 10 alarms, setting time, and a stopwatch mode
//Kyubum Shim, Zohan Marediya
//Initial Creation Date: February 9, 2021
//Lab Session: Kyubum(17240), Zohan (17235)
//TA: Blake Margolis
//Final Update: February 15, 2021


#include "local/ST7735.h"
#include <stdint.h>
#include "local/tm4c123gh6pm.h"
#include "local/PLL.h"
#include "local/LaunchPad.h"
#include "local/CortexM.h"
#include "local/TExaS.h"
#include "Timer0.h"
#include "Switch.h"
#include "AnalogDisplay.h"
#include "DigitalDisplay.h"
#include "Timer1.h"
#include "StopwatchTimer.h"
#include "AlarmFunct.h"

//###########################################################	//menu/modes variables
#define menuOptionSize 6
enum States{setTimeMenu, setAlarmMenu, toggleAlarmMenu, clearAlarmsMenu, displayModeMenu, stopWatchMode, drawClockState, mainMenu};
char* menuOptions[menuOptionSize] = {"Set Time", "Set Alarm", "Toggle Alarm", "Clear Alarms", "Display Mode", "Stop Watch"};
//########################################################### //display mode for clock
int displayMode;
enum clock{digitalClock, analogClock};
//########################################################### //alarms variables
#define alarmLimit 10
int alarmEnabled = 1;
Time alarms[alarmLimit];
int totalAlarms = 0;
//###########################################################
static int updateCheck=0;
int tweakScreenFlag = 0;
Time stopwatchTime = {0,0,0};

void UIHandler(int option){
	//Clock Faces
	if(option==0){
	ST7735_DrawString(0, 15, "SW1: Menu", ST7735_CYAN);
	}
	//Menu Options
	else if(option==1){
		ST7735_DrawString(0, 14, "SW1: Down", ST7735_CYAN);
		ST7735_DrawString(0, 15, "SW2: Enter", ST7735_CYAN);
	}
	//Stopwatch Options
	else if(option==2){
		ST7735_DrawString(0, 14, "SW1: Exit", ST7735_CYAN);
		ST7735_DrawString(0, 15, "SW2: Start/Pause", ST7735_CYAN);
	}
	
}

void updateTime(Time *time);
int checkforAlarms(void){
	if(!alarmEnabled){
		return -1;	//alarms are toggled off
	}
	for(int i = 0; i < totalAlarms; i++){
		if(currentTime.hour == alarms[i].hour &&
			currentTime.minute == alarms[i].minute){
			return i;
		}
	}
	return -1; //no alarms are set to go off
}

void waitforAlarm(int alarmNum){
	updateCheck = 1;
	ST7735_FillScreen(ST7735_BLACK);
	int xStart = 0;
	int yStart = 5;
	ST7735_DrawString(xStart, yStart, "AHHH WAKE UP", ST7735_RED);
	
	Sound_Set(1);
	ENT = 0;
	while(ENT == 0){	// block until 1 minute is up OR ent is pressed to ack alarm
		if(timeFlag == 1){
			updateTime(&currentTime);
			timeFlag = 0;
		}
	}
	Sound_Set(0);
	ENT = 0;
}

void handleStopwatch(int keyPressed){
	if(keyPressed == 0){
		turnOnStopwatch();
	}else if(keyPressed % 2 == 1){
		//ST7735_FillScreen(ST7735_BLACK);
		ST7735_DrawString(4, 13, "  Activated  ", ST7735_CYAN);
		startStopwatch();
	}else{
		//ST7735_FillScreen(ST7735_BLACK);
		ST7735_DrawString(4, 13, "  Deactivated  ", ST7735_CYAN);
		stopStopwatch();
	}
	int timeInSeconds = (stopwatchTime.hour * 60 * 60) + stopwatchTime.minute * 60 + stopwatchTime.second;	
	int xStart = 6;
	if(tweakScreenFlag==0){
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_DrawDigital(timeInSeconds, 1);
		ST7735_DrawString(4, 13, "Not Activated", ST7735_CYAN);
		ST7735_DrawString(xStart, 10, "Stop Watch", ST7735_CYAN);
		UIHandler(2);
	}

	ST7735_DrawDigital(timeInSeconds, 0);
}

void drawClock(){
	int timeInSeconds = (currentTime.hour * 60 * 60) + currentTime.minute * 60 + currentTime.second;
	
	if(updateCheck){
		ST7735_FillScreen(ST7735_BLACK);
		updateCheck=0;
		if(displayMode == analogClock){
			ST7735_DrawString(4, 0, "Analog Clock", ST7735_CYAN);
			ST7735_DrawClockFace();
		}
		else {
			ST7735_DrawDigital(timeInSeconds,1);
			ST7735_DrawString(4, 0, "Digital Clock", ST7735_CYAN);
		}
	}else if(displayMode == analogClock){
		ST7735_DrawAnalog(timeInSeconds);
	}else if(displayMode == digitalClock){
		ST7735_DrawDigital(timeInSeconds,0);
	}
		UIHandler(0);
}

void setTime(int buttonClicks,int enterPressed, Time *tempTime){

	updateCheck=1;
	if(enterPressed >= 2) return;
		
	int yStart = 3;
	int xStart = 0;
	int numOffset = 15;
		
	int charSizeX = 6;
	int charSizeY = 10;
	
	if(tweakScreenFlag == 0){
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_DrawString(5, 0,"Set Time", ST7735_CYAN);
		
		ST7735_DrawString(xStart, yStart, "Current Hour: ", ST7735_CYAN);
		ST7735_DrawString(xStart, yStart + 1, "Current Minute: ", ST7735_CYAN);
		UIHandler(1);
	}else{
		//coverup old numbers
		ST7735_FillRect(charSizeX * (xStart + numOffset), charSizeY * yStart, 2 * (charSizeX), charSizeY, ST7735_BLACK);
		ST7735_FillRect(charSizeX * (xStart + numOffset), charSizeY * (yStart+1), 2 * (charSizeX), charSizeY, ST7735_BLACK);
		//coverup old pointer
		ST7735_DrawString(20,yStart, "X", ST7735_BLACK);
		ST7735_DrawString(20,yStart+1, "X", ST7735_BLACK);
	}

	if(enterPressed == 0){
		tempTime->hour = (buttonClicks) % 24;
	}else{
		tempTime->minute = (buttonClicks) % 60;
	}
	
	ST7735_SetCursor(xStart + numOffset, yStart);
	ST7735_OutUDec(tempTime->hour);
	
	ST7735_SetCursor(xStart + numOffset, yStart + 1);
	ST7735_OutUDec(tempTime->minute);
	
	//draw the pointer pointing to the min/hour
	if(enterPressed == 1){
		yStart++;
	}
	ST7735_DrawString(20,yStart, "X", ST7735_YELLOW);
}

void setAlarm(int buttonClicks,int enterPressed, Time *newAlarm){
	updateCheck=1;
	if(enterPressed >= 2) return;	//invalid input
	
	int yStart = 3;
	int xStart = 0;
	int numOffset = 17;
	
	int charSizeX = 6;
	int charSizeY = 10;
	
	if(tweakScreenFlag == 0){
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_DrawString(5, 0,"Set Alarm", ST7735_CYAN);
		
		ST7735_DrawString(xStart, yStart, "Set Alarm Hour: ", ST7735_CYAN);
		ST7735_DrawString(xStart, yStart + 1, "Set Alarm Minute: ", ST7735_CYAN);
		UIHandler(1);
	}else{
		//coverup old numbers
		ST7735_FillRect(charSizeX * (xStart + numOffset), charSizeY * yStart, 2 * (charSizeX), charSizeY, ST7735_BLACK);
		ST7735_FillRect(charSizeX * (xStart + numOffset), charSizeY * (yStart+1), 2 * (charSizeX), charSizeY, ST7735_BLACK);
		//coverup old pointer
		ST7735_DrawString(20,yStart, "X", ST7735_BLACK);
		ST7735_DrawString(20,yStart+1, "X", ST7735_BLACK);

	}
	
	if(enterPressed == 0){
		newAlarm->hour = (buttonClicks) % 24;
	}else{
		newAlarm->minute = (buttonClicks) % 60;
	}
	
	//draw alarm hour
	ST7735_SetCursor(xStart + numOffset, yStart);
	ST7735_OutUDec(newAlarm->hour);
	
	//draw alarm minute	
	ST7735_SetCursor(xStart + numOffset, yStart + 1);
	ST7735_OutUDec(newAlarm->minute);
	
	//draw the pointer pointing to the min/hour
	if(enterPressed == 1){
		yStart++;
	}
	ST7735_DrawString(20,yStart, "X", ST7735_YELLOW);
}

void toggleAlarm(int menuPressed){
	updateCheck=1;
	int yStart = 3;
	int xStart = 0;
	
	if(tweakScreenFlag == 0){
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_DrawString(0, 0, "Toggle Alarm", ST7735_CYAN);
		ST7735_DrawString(xStart,yStart,"Off",ST7735_CYAN);
		ST7735_DrawString(xStart,yStart + 1,"On",ST7735_CYAN);
		UIHandler(1);
	}else{
		ST7735_DrawString(xStart + 4, yStart, "X", ST7735_BLACK);	//covering up old pointers
		ST7735_DrawString(xStart + 4, yStart + 1, "X", ST7735_BLACK);
	}
	//draw pointer to current choice
	ST7735_DrawString(xStart + 4, yStart + (menuPressed % 2), "X", ST7735_YELLOW);
	alarmEnabled = menuPressed % 2;
}

void clearAlarms(int menuPressed){
	int yStart = 5;
	if(tweakScreenFlag == 0){
		ST7735_FillScreen(ST7735_BLACK);
		UIHandler(1);
		
		ST7735_DrawString(0, 0, "Are you sure you want", ST7735_CYAN);
		ST7735_DrawString(1, 1, "to clear all alarms?", ST7735_CYAN);
		
		ST7735_DrawString(7, yStart, "Yes", ST7735_CYAN);
		ST7735_DrawString(7, yStart + 1, "No!", ST7735_CYAN);
	}else{
		ST7735_DrawString(11,yStart, "X", ST7735_BLACK);
		ST7735_DrawString(11,yStart + 1, "X", ST7735_BLACK);
	}
	ST7735_DrawString(11,yStart + (menuPressed % 2), "X",  ST7735_YELLOW);
}

void changeDisplayMode(int menuPressed){
	ST7735_DrawString(0, 14, "SW1: Move Down", ST7735_CYAN);
	ST7735_DrawString(0, 15, "SW2: Enter", ST7735_CYAN);

	updateCheck=1;
	int yStart = 4;
	int xStart = 0;
	
	if(tweakScreenFlag == 0){
		ST7735_FillScreen(ST7735_BLACK);
		ST7735_DrawString(2, 0, "Display Mode", ST7735_CYAN);
		
		ST7735_DrawString(xStart, yStart    , "   Digital Mode" , ST7735_CYAN);
		ST7735_DrawString(xStart, yStart + 1, "   Analog Mode", ST7735_CYAN);
	}else{
		ST7735_DrawString(xStart, yStart, "X", ST7735_BLACK);
		ST7735_DrawString(xStart, yStart + 1, "X", ST7735_BLACK);
	}


	//draw pointer to current choice
	ST7735_DrawString(xStart, yStart + (menuPressed % 2), "X", ST7735_YELLOW);
	displayMode = (menuPressed % 2);
}

void handleMenu(int menuIndex){
	ST7735_DrawString(0, 0, "Main Menu", ST7735_CYAN);


	updateCheck = 1;
	int yStart = 3;//place of the first text
	int charSizeX = 6;
	int charSizeY = 10;
	if(tweakScreenFlag==0){
		ST7735_FillScreen(ST7735_BLACK);
		
		//write all options
		for(int i = 0; i < menuOptionSize; i++){
			ST7735_DrawString(0,yStart+i, menuOptions[i], ST7735_CYAN);
		}
		UIHandler(1);
	}
	ST7735_FillRect(20 * charSizeX, charSizeY * (menuIndex + yStart - 1),charSizeX, charSizeY, ST7735_BLACK);	//clear old pointers
	ST7735_FillRect(20 * charSizeX, charSizeY * (menuIndex + yStart),charSizeX, charSizeY, ST7735_BLACK);	//clear old pointers
	
	//draw Pointer to the current Choice
	ST7735_DrawString(20,menuIndex + yStart, "X", ST7735_YELLOW);
}

void updateTime(Time *time){
	if(time->second%2) PF3 &= ~0x08;
	else PF3|=0x08;
	if(time->second == 59){
		time->second = 0;
		if(time->minute == 59){
			time->minute = 0;
			time->hour = (time->hour + 1) % 24;
		}else{
			time->minute = (time->minute + 1) % 60;
		}
	}else{
		time->second++;
	}
}

int main(void){
	PLL_Init(Bus80MHz);
	
	
	DisableInterrupts();
	//Output_Init();
	//initializations
	ST7735_InitR(INITR_REDTAB);
	Timer0_Init();
	Timer1_Init(20);
	StopwatchTimer_Init();
	Sound_Init(80000000/400);
	GPIO_PortF_Init();
	EnableInterrupts();


	int currentState = drawClockState;
	ST7735_DrawDigital(0,1);
	ST7735_DrawString(4, 0, "Digital Clock", ST7735_CYAN);
	
	int menuIndex = 0;
	int enterPressed = 0;
	int menuPressed = 0;
	Time tempTime = {0,0,0};
	
	while(1){
		
		while(timeFlag == 0 && MENU == 0  && ENT == 0 && timedoutFlag == 0 && stopwatchFlag == 0){};
//		while(MENU == 0  && ENT == 0 && timedoutFlag == 0 && stopwatchFlag == 0){};
		
		//update time		
		if(timeFlag){	
			updateTime(&currentTime);
			timeFlag = 0;
			int alarmNum = -1;
			if(currentTime.second == 0){
				alarmNum = checkforAlarms();	//ring alarm if time matches
			}
			if(alarmNum != -1){
				ENT = 0;	//enter is the way to exit alarm
				int oldMENU = MENU;	//ignore menu click while handling alarm
				waitforAlarm(alarmNum);
				handleTimeout(resetTimeout);
				MENU = oldMENU;
			}
		}
		
		if(stopwatchFlag){
			updateTime(&stopwatchTime);
			stopwatchFlag = 0;
		}
		
		//ignore whatever the user WAS doing and reset back to displaying the clock
		if(timedoutFlag){	
			ST7735_FillScreen(ST7735_BLACK);
			
			currentState = drawClockState;
			updateCheck=1;
			drawClock();
			timedoutFlag = 0;
			continue;
		}
		
		//user input so reset inactivity timeout
		if(MENU || ENT){
			updateCheck = 1;
			handleTimeout(resetTimeout);
		}
		
		int tempState = currentState;
		//determine next state
		switch(currentState){
			case drawClockState:
				if(MENU){
					currentState = mainMenu;
					handleTimeout(enableTimeout);
				}
				menuIndex = 0;
				break;
			case mainMenu:
				updateCheck = 1;
				if(ENT){
					currentState = menuIndex;
					enterPressed = 0;
					menuPressed = 0;
					break;
				}
				if(MENU){
					menuIndex++;
				}
				if(menuIndex == menuOptionSize) currentState = drawClockState;
				break;
			case setTimeMenu:
				updateCheck = 1;
				if(ENT){
					enterPressed++;
					menuPressed = 0;
				}
				if(MENU){
					menuPressed++;
				}
				if(enterPressed == 2){
					currentState = drawClockState;
					currentTime.hour = tempTime.hour;
					currentTime.minute = tempTime.minute;
					currentTime.second = 0;
					tempTime.hour = 0;
					tempTime.minute = 0;
					tempTime.second = 0;
				}
				break;
			case setAlarmMenu:
				updateCheck = 1;
				if(ENT){
					enterPressed++;
					menuPressed = 0;
				}
				if(MENU){
					menuPressed++;
				}
				if(enterPressed == 2){
					currentState = drawClockState;
					if(totalAlarms == alarmLimit) totalAlarms = alarmLimit;
					else totalAlarms++;
				}
				break;
			case toggleAlarmMenu:
				updateCheck = 1;
				if(ENT){
					enterPressed++;
				}
				if(MENU){
					menuPressed++;
				}
				if(enterPressed == 1){
					currentState = drawClockState;
				}
				break;
			case displayModeMenu:
				updateCheck = 1;
				if(ENT){
					enterPressed++;
				}
				if(MENU){
					menuPressed++;
				}
				if(enterPressed == 1){
					currentState = drawClockState;
				}
				break;
			case stopWatchMode:
				updateCheck = 1;
				//ST7735_FillScreen(ST7735_BLACK);
				if(ENT) enterPressed++;
				if(MENU){
					currentState = drawClockState;
					turnOffStopwatch();
					stopwatchTime.hour = 0;
					stopwatchTime.minute = 0;
					stopwatchTime.second = 0;
				}
				break;
			case clearAlarmsMenu:
				if(MENU) menuPressed++;
				if(ENT){
					if(menuPressed % 2 == 0){
						totalAlarms = 0;
					}
					currentState = drawClockState;
				}
				break;
		}
		
		ENT = 0;
		MENU = 0;
		
		if(currentState == tempState){
			tweakScreenFlag = 1;
		}
		
		if(currentState == drawClockState){
			handleTimeout(disableTimeout);
			drawClock();
		}else if(currentState == mainMenu){
			handleMenu(menuIndex);
		}else if(currentState == setTimeMenu){
			setTime(menuPressed,enterPressed, &tempTime);
		}else if(currentState == setAlarmMenu){
			setAlarm(menuPressed,enterPressed, &alarms[totalAlarms % alarmLimit]);
		}else if(currentState == toggleAlarmMenu){
			toggleAlarm(menuPressed);
		}else if(currentState == displayModeMenu){
			changeDisplayMode(menuPressed);
		}else if(currentState == stopWatchMode){
			handleStopwatch(enterPressed);
		}else if(currentState == clearAlarmsMenu){
			clearAlarms(menuPressed);
		}
		tweakScreenFlag = 0;
	}
}
