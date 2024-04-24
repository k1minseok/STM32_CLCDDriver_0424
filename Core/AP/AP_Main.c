/*
 * AP_Main.c
 *
 *  Created on: Apr 23, 2024
 *      Author: k1min
 */

#include "AP_Main.h"
#include "stdio.h"

Button_t Button_1, Button_2, Button_3;
LED_t LED_1, LED_2, LED_3;
uint8_t modeState;

void sys_init()
{
	button_init(&Button_1, GPIOC, GPIO_PIN_10);
	button_init(&Button_2, GPIOC, GPIO_PIN_11);
	button_init(&Button_3, GPIOC, GPIO_PIN_12);

	LED_init(&LED_1, GPIOC, GPIO_PIN_8);
	LED_init(&LED_2, GPIOC, GPIO_PIN_6);
	LED_init(&LED_3, GPIOC, GPIO_PIN_5);

	LCD_init();

	modeState = defaultLED;
}

int APMain()
{
	sys_init();

	LCD_writeStringXY(0, 0, "Hello STM32!");
	LCD_writeStringXY(1, 0, "KCCISTC Harman");

	char buff[50];

	while (1)
	{
		modeStateCheck();
		modeStateRun();

		sprintf(buff, "MODE : %d         ", modeState);
		LCD_writeStringXY(1, 0, buff);
	}

	return 0;
}



void modeStateCheck()
{
	if (button_getState(&Button_1) == ACT_PUSHED)
	{
		modeState = LED1_ON;
		LED_OFF(&LED_1);
		LED_OFF(&LED_2);
		LED_OFF(&LED_3);
	}
	if (button_getState(&Button_2) == ACT_PUSHED)
	{
		modeState = LED2_3_ON;
		LED_OFF(&LED_1);
		LED_OFF(&LED_2);
		LED_OFF(&LED_3);
	}
	if (button_getState(&Button_3) == ACT_PUSHED)
	{
		modeState = LED1_3_ON;
		LED_OFF(&LED_1);
		LED_OFF(&LED_2);
		LED_OFF(&LED_3);
	}
}
void modeStateRun()
{
	static uint32_t prevTime = 0;
	uint32_t curTime = HAL_GetTick();

	switch (modeState)
	{
		case LED1_ON:
			if(curTime - prevTime < 200)
				return;
			prevTime = curTime;
//			if (timeTick != 0)
//				return;
			LED_toggle(&LED_1);
			LED_OFF(&LED_2);
			LED_OFF(&LED_3);
//			timeTick = 200;
			break;

		case LED2_3_ON:
			if(curTime - prevTime < 100)
				return;
			prevTime = curTime;
//			if (timeTick != 0)
//				return;
			LED_toggle(&LED_2);
			LED_toggle(&LED_3);
			LED_OFF(&LED_1);
//			timeTick = 100;
			break;

		case LED1_3_ON:
			if(curTime - prevTime < 1000)
				return;
			prevTime = curTime;
//			if (timeTick != 0)
//				return;
			LED_toggle(&LED_1);
			LED_toggle(&LED_3);
			LED_OFF(&LED_2);
//			timeTick = 1000;
			break;

		case defaultLED:
			if(curTime - prevTime < 500)
				return;
			prevTime = curTime;
//			if (timeTick != 0)
//				return;
			LED_toggle(&LED_1);
			LED_toggle(&LED_2);
			LED_toggle(&LED_3);
//			timeTick = 500;
			break;
	}
}
