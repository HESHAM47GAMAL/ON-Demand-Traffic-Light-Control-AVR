/******************************************
* Module: LED
*
* File Name: LED.c
*
* Description: source file for AVR LED Driver
*
* Author: Hesham Shehata
*
******************************************/


#include "LED.h"
uint8_t stop_blink = 0; /*variable that end led blinking after end delay loop  zero: no need to end blink  , one :end blinking */
/*********************************************************
*               Implement
*********************************************************/
void LED_init(uint8_t PORT_X , uint8_t PIN_NUM)
{
	DIO_setupPinDirection(PORT_X , PIN_NUM , OUTPUT_PIN); //set for this pin as output pin as put one for this pin in DDR
}

void LED_on(uint8_t PORT_X , uint8_t PIN_NUM)
{
	DIO_writePin(PORT_X,PIN_NUM,LOGIC_HIGH); // set pin for this port 
}

void LED_off(uint8_t PORT_X , uint8_t PIN_NUM)
{
	DIO_writePin(PORT_X,PIN_NUM,LOGIC_LOW); // clear pin for this port 
}

void LED_toggle(uint8_t PORT_X , uint8_t PIN_NUM)
{
	DIO_togglePin(PORT_X,PIN_NUM); //toggle pin value
}

void LED_onWithDelay(uint8_t PORT_X , uint8_t PIN_NUM,uint32_t T_delay)
{
	LED_on(PORT_X,PIN_NUM);
	TIMER0_Delay_ms(T_delay);
}

void LED_offWithDelay(uint8_t PORT_X , uint8_t PIN_NUM,uint32_t T_delay)
{
	LED_off(PORT_X,PIN_NUM);
	TIMER0_Delay_ms(T_delay);
}

void LED_blink(uint8_t PORT_X , uint8_t PIN_NUM,uint32_t time_of_blinking)
{
	stop_blink = 0;
	uint8_t num_of_iterate = time_of_blinking / 1000000 ;
	while(num_of_iterate  > 0)
	{
			LED_on(PORT_X,PIN_NUM);
			TIMER0_Delay_ms(499900);// 499.9ms
			if( stop_blink == 1)
				break;
			LED_off(PORT_X,PIN_NUM);
			TIMER0_Delay_ms(499900);
			if( stop_blink == 1)
				break;
			num_of_iterate--;
	}
}

void LED_stopBlink(void)
{
	TIMER0_endDelay();
	stop_blink = 1;
}

void LED_blinkForTwoPins(uint8_t PORT_X_1 , uint8_t PIN_NUM_1,uint8_t PORT_X_2 , uint8_t PIN_NUM_2,uint32_t time_of_blinking)
{
	stop_blink = 0;
	uint8_t num_of_iterate = time_of_blinking / 1000000 ;
	while(num_of_iterate  > 0)
	{
		LED_on(PORT_X_1,PIN_NUM_1);
		LED_on(PORT_X_2,PIN_NUM_2);
		TIMER0_Delay_ms(499900);// 499.9ms
		if( stop_blink == 1)
		break;
		LED_off(PORT_X_1,PIN_NUM_1);
		LED_off(PORT_X_2,PIN_NUM_2);
		TIMER0_Delay_ms(499900);
		if( stop_blink == 1)
		break;
		num_of_iterate--;
	}
}