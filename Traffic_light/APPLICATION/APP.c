/*
 * APP.c
 *
 * Created: 8/16/2022 7:55:33 PM
 *  Author: 20112
 */ 

#include "APP.h"

car_lightState state = NORMAL_STATE; /*variable contain current mode if it "normal" or "button pressed at red" or "button pressed at green or yellow"*/
uint8_t car_GREEN_YELLOW_RED = 0; /*variable contain number indicate for which led in car traffic light is on  green = 0 , yellow = 1 , red = 2*/
ISR_state ISR_currentState = NO_INTERRUPT_HAPPEN; /*variable used to indicate if interrupt and function related to interrupt is run or no interrupt happen
NO_INTERRUPT_HAPPEN : no interrupt happen and when buttton press code in isr will run
DOING_INTERRUPT_HAPPEN : there are interrupt happen from time and all function related to it not ended yet
*/

ISR(INT0)
{
	if( ISR_currentState == NO_INTERRUPT_HAPPEN)/*check if there are no function related to ISR is still run */
	{
		LED_stopBlink();/*end any delay happen or blink*/
		if ( (car_GREEN_YELLOW_RED == 0) || (car_GREEN_YELLOW_RED == 1))//check if current led on is green or yellow to run case 2
				{state = YELLOW_GREEN_CAR_STATE;}//update state to case 1
		else if( (car_GREEN_YELLOW_RED == 2)) //check if current led on is red to run case 1
		{state = RED_LED_CAR_STATE;}//update state to case 2
	}

}


void APP_init(void)
{
	/*initialize led for car & pedestrian*/
	LED_init(PORTA_ID,PIN0_ID);
	LED_init(PORTA_ID,PIN1_ID);
	LED_init(PORTA_ID,PIN2_ID);
	LED_init(PORTB_ID,PIN0_ID);
	LED_init(PORTB_ID,PIN1_ID);
	LED_init(PORTB_ID,PIN2_ID);
	
	/*init timer0*/
	Timer0_ConfigType config_TIMER0 = {NORMAL_MODE,F_CPU_1024};
	TIMER0_init(&config_TIMER0);
	/*ENABLE GLOBAL Interrupt*/
	GLOBAL_INTERRUPT_ENABLE();
	
	/*set INT0*/
	INT0_init(FALLING_EDGE_TRIGGER,INPUT_PIN_PULLUP);
	
	/*initialize LCD & human move & hand*/
	LCD_init();
	LCD_humanMoveInit();
	LCD_handInit();
}

void APP_start(void)
{
	while(1)
	{
		CAR_trafficLight();/*start will normal mode and will be here until pedestrian press button*/
		if(state == RED_LED_CAR_STATE)
			CAR_redLedState();/*run case 1*/
		if(state == YELLOW_GREEN_CAR_STATE)
			CAR_yellowGreenLedState();/*run case 2*/
	}
}

void CAR_yellowGreenLedState(void)
{
	ISR_currentState = DOING_INTERRUPT_HAPPEN; /*update variable that function related to interrupt is run to avoid run iNT0 until finish it*/
	/*at first turn pedestrians red led on*/
	LED_on(PORTB_ID,PIN2_ID);
	/*then blink yellow led for car and pedestrian for 5 sec*/
	LED_blinkForTwoPins(PORTA_ID,PIN1_ID,PORTB_ID,PIN1_ID,5000000);
	LCD_clearScreen(); /*clean lcd to remove hand sign */
	LCD_humanMoveDisplay(0,6);/*display human move sign*/
	/*car red led on & pedestrian green led on & pedestrian red led off for 5 sec*/
	LED_off(PORTB_ID,PIN2_ID);
	LED_on(PORTA_ID,PIN2_ID);
	LED_onWithDelay(PORTB_ID,PIN0_ID,5000000);
	CAR_endOfTwoStates();
	/*then return to normal mode again*/
	state = NORMAL_STATE;/*update to return run normal state for car traffic light*/
}

void CAR_redLedState(void)
{
	ISR_currentState = DOING_INTERRUPT_HAPPEN; /*update variable that function related to interrupt is run to avoid run iNT0 until finish it*/
	/*at first turn pedestrians red led off*/
	LED_off(PORTB_ID,PIN2_ID);
	/*case 1 : will turn car red led & pedestrian green led on for five second*/
	LED_on(PORTA_ID,PIN2_ID);
	LCD_clearScreen(); /*clean lcd to remove hand sign */
	LCD_humanMoveDisplay(0,6);/*display human move sign*/
	LED_onWithDelay(PORTB_ID,PIN0_ID,5000000);
	CAR_endOfTwoStates();
	/*then return to normal mode again*/
	state = NORMAL_STATE;/*update to return run normal state for car traffic light*/
}

void CAR_endOfTwoStates(void)
{
	/*then turn  car red led  off & and still pedestrain green led on */
	LED_off(PORTA_ID,PIN2_ID);
	/*then blink yellow led for car and pedestrain for 5 sec*/
	LED_blinkForTwoPins(PORTA_ID,PIN1_ID,PORTB_ID,PIN1_ID,5000000);
	/*then pedestrian green led is off*/
	LED_off(PORTB_ID,PIN0_ID);
	/*then turn pedestrian red led on*/
	LED_on(PORTB_ID,PIN2_ID);
}

void CAR_trafficLight(void)
{
	ISR_currentState = NO_INTERRUPT_HAPPEN;/*/*update variable that no function related to interrupt is run & return to normal state again*/
	LCD_clearScreen(); /*clean lcd to remove human move sign */
	LCD_handDisplay(0,2);/*display hand sign in lcd*/
	/* turn pedestrian red led on as pedestrians can't across way*/
	LED_on(PORTB_ID,PIN2_ID);
	/*turn led green on for 5 sec then turn off*/
	if(state == NORMAL_STATE)/*check if happen interrupt and move to case 1 0r case 2 so won't run this and move to case 1 or case 2*/
	{
		car_GREEN_YELLOW_RED = 0;/*update variable value to indicate that current green led on */
		LED_onWithDelay(PORTA_ID,PIN0_ID,5000000);
		LED_off(PORTA_ID,PIN0_ID);
	}
	
	/*blink led yellow on for 5 sec then turn off*/
	if(state == NORMAL_STATE)/*check if happen interrupt and move to case 1 0r case 2 so won't run this and move to case 1 or case 2*/
	{
		car_GREEN_YELLOW_RED = 1;/*update variable value to indicate that current yellow led on */
		LED_blink(PORTA_ID,PIN1_ID,5000000);
		LED_off(PORTA_ID,PIN1_ID);/*as if blinking stop while led is on  --> turn led of*/
	}
	/*turn led red on for 5 sec then turn off*/
	if(state == NORMAL_STATE)/*check if happen interrupt and move to case 1 0r case 2 so won't run this and move to case 1 or case 2*/
	{
		car_GREEN_YELLOW_RED =2; /*update variable value to indicate that current red led on */
		LED_onWithDelay(PORTA_ID,PIN2_ID,5000000);
		LED_off(PORTA_ID,PIN2_ID);
	}
	/*blink led yellow on for 5 sec then turn off */
	if(state == NORMAL_STATE)/*check if happen interrupt and move to case 1 0r case 2 so won't run this and move to case 1 or case 2*/
	{
		car_GREEN_YELLOW_RED =1; /*update variable value to indicate that current yellow led on */
		LED_blink(PORTA_ID,PIN1_ID,5000000);
		LED_off(PORTA_ID,PIN1_ID);/*as if blinking stop while led is on */
	}
		

	
}