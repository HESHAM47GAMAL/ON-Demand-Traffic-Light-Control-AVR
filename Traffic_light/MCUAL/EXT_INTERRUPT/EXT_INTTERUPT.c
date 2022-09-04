/******************************************
* Module: EXT_INTERRUPT
*
* File Name: EXT_INTERRUPT.c
*
* Description: source file for AVR external interrupt
*
* Author: Hesham Shehata
*
******************************************/

#include "EXT_INTTERUPT.h"

void GLOBAL_INTERRUPT_ENABLE(void)
{
	sei();
}

void GLOBAL_INTERRUPT_DISABLE(void)
{
	cli();
}

void INT0_init( EXT_triggerType triggerType,GPIO_PinDirectionTypes direction)
{
	DIO_setupPinDirection(PORTD_ID,PIN2_ID,direction);/*set pin as input pin  or input pulled up*/
	MCUCR = (MCUCR & 0xFC) | triggerType;/*set type of trigger*/
	SET_BIT(GICR ,6); /*enable INT0*/
}

void INT1_init( EXT_triggerType triggerType ,GPIO_PinDirectionTypes direction)
{
	DIO_setupPinDirection(PORTD_ID,PIN3_ID,direction);/*set pin as input pin  or input pulled up*/
	MCUCR = (MCUCR & 0xF3) | (triggerType << 2);/*set type of trigger*/
	SET_BIT(GICR ,7); /*enable INT1*/
}

void INT2_init( EXT_triggerType triggerType ,GPIO_PinDirectionTypes direction)
{
	DIO_setupPinDirection(PORTB_ID,PIN2_ID,direction);/*set pin as input pin  or input pulled up*/
	/*set type of trigger*/
	if( triggerType == FALLING_EDGE_TRIGGER)
		CLEAR_BIT(MCUCSR,6);
	else if(triggerType == RISING_EDGE_TRIGGER)
		SET_BIT(MCUCSR,6);
	SET_BIT(GICR,5);/*enable INT2*/
}

void INT0_deInit(void)
{
	CLEAR_BIT(GICR ,6);
}

void INT1_deInit(void)
{
	CLEAR_BIT(GICR ,7);
}

void INT2_deInit(void)
{
	CLEAR_BIT(GICR ,5);
}