/******************************************
* Module: DIO(GPIO)
*
* File Name: DIO.c
*
* Description: source file for AVR DIO Driver
*
* Author: Hesham Shehata
*
******************************************/

#include "DIO.h"
/*********************************************************
*               Implement
*********************************************************/
void DIO_setupPinDirection(uint8_t PORT_X ,uint8_t PIN_NUM,GPIO_PinDirectionTypes DIRECTION )
{
	if( (PIN_NUM >= NUM_OF_PIN_PER_PORT) || (PORT_X >= NUM_OF_PORT) )
	{
		
		//Error handling ,Nothing to do
	}
	else
	{
		switch(PORT_X)
		{
			case PORTA_ID:
				if(DIRECTION == INPUT_PIN)
				{
					CLEAR_BIT(DDRA,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
				}
				else if(DIRECTION == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT(DDRA,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
					SET_BIT(PORTA,PIN_NUM);// put "one" in this bit in port to activate pull up internal
				}
				else if(DIRECTION == OUTPUT_PIN)
				{
					SET_BIT(DDRA,PIN_NUM);//put "one" in this bit in DDR to make it output pin
				}
				else
				{
					/*  worng direction*/
				}
				break;
			case PORTB_ID:
				if(DIRECTION == INPUT_PIN)
				{
					CLEAR_BIT(DDRB,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
				}
				else if(DIRECTION == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT(DDRB,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
					SET_BIT(PORTB,PIN_NUM);// put "one" in this bit in port to activate pull up internal
				}
				else if(DIRECTION == OUTPUT_PIN)
				{
					SET_BIT(DDRB,PIN_NUM);//put "one" in this bit in DDR to make it output pin
				}
				else
				{
					/*  wrong direction*/
				}
				break;
			case PORTC_ID:
				if(DIRECTION == INPUT_PIN)
				{
					CLEAR_BIT(DDRC,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
				}
				else if(DIRECTION == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT(DDRC,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
					SET_BIT(PORTC,PIN_NUM);// put "one" in this bit in port to activate pull up internal
				}
				else if(DIRECTION == OUTPUT_PIN)
				{
					SET_BIT(DDRC,PIN_NUM);//put "one" in this bit in DDR to make it output pin
				}
				else
				{
					/*  wrong direction*/
				}
				break;
			case PORTD_ID:
				if(DIRECTION == INPUT_PIN)
				{
					CLEAR_BIT(DDRD,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
				}
				else if(DIRECTION == INPUT_PIN_PULLUP)
				{
					CLEAR_BIT(DDRD,PIN_NUM);//put "zero" in this bit in DDR to make it input pin
					SET_BIT(PORTD,PIN_NUM);// put "one" in this bit in port to activate pull up internal
				}
				else if(DIRECTION == OUTPUT_PIN)
				{
					SET_BIT(DDRD,PIN_NUM);//put "one" in this bit in DDR to make it output pin
				}
				else
				{
					/*  wrong direction*/
				}
				break;
		}
		
	}
}


void DIO_writePin(uint8_t PORT_X ,uint8_t PIN_NUM,uint8_t value )
{
	if( (PIN_NUM >= NUM_OF_PIN_PER_PORT) || (PORT_X >= NUM_OF_PORT) )
	{
		//Error handling ,Nothing to do
	}
	
	else
	{
		switch(PORT_X)
		{
			case PORTA_ID:
				if(BIT_IS_SET(DDRA,PIN_NUM))//check if this pin is output pin ,as if output will set or clear else will do nothing
				{
					if( value == LOGIC_HIGH)
						SET_BIT(PORTA,PIN_NUM);//write 1 in bit
					else if(value == LOGIC_LOW)
						CLEAR_BIT(PORTA,PIN_NUM);//write 0 in bit
					else
					{
						//nothing to do
					}
				}
				break;
			case PORTB_ID:
				if(BIT_IS_SET(DDRB,PIN_NUM))//check if this pin is output pin ,as if output will set or clear else will do nothing
				{
					if( value == LOGIC_HIGH)
						SET_BIT(PORTB,PIN_NUM);//write 1 in bit
					else if(value == LOGIC_LOW)
						CLEAR_BIT(PORTB,PIN_NUM);//write 0 in bit
					else
					{
						//nothing to do
					}
				}
				break;
			case PORTC_ID:
				if(BIT_IS_SET(DDRC,PIN_NUM))//check if this pin is output pin ,as if output will set or clear else will do nothing
				{
					if( value == LOGIC_HIGH)
						SET_BIT(PORTC,PIN_NUM);//write 1 in bit
					else if(value == LOGIC_LOW)
						CLEAR_BIT(PORTC,PIN_NUM);//write 0 in bit
					else
					{
						//nothing to do
					}
				}
				break;
			case PORTD_ID:
				if(BIT_IS_SET(DDRD,PIN_NUM))//check if this pin is output pin ,as if output will set or clear else will do nothing
				{
					if( value == LOGIC_HIGH)
						SET_BIT(PORTD,PIN_NUM);//write 1 in bit
					else if(value == LOGIC_LOW)
						CLEAR_BIT(PORTD,PIN_NUM);//write 0 in bit
					else
					{
						//nothing to do
					}
				}
				break;
			
		}
	}
}


uint8_t DIO_readPin(uint8_t PORT_X ,uint8_t PIN_NUM)
{
	uint8_t return_value = LOGIC_LOW;
	if( (PIN_NUM >= NUM_OF_PIN_PER_PORT) || (PORT_X >= NUM_OF_PORT) )
	{
		//Error handling ,Nothing to do
	}
	else
	{
		switch(PORT_X)
		{
			case PORTA_ID:
				if(BIT_IS_SET(PINA,PIN_NUM))//mean bit contain logic high
					return_value = LOGIC_HIGH; // return logic high
				else //mean bit contain logic low
					return_value = LOGIC_LOW;
				break;
			case PORTB_ID :
				if(BIT_IS_SET(PINB,PIN_NUM))//mean bit contain logic high
					return_value = LOGIC_HIGH; // return logic high
				else //mean bit contain logic low
					return_value = LOGIC_LOW;
				break;
			case PORTC_ID :
				if(BIT_IS_SET(PINC,PIN_NUM))//mean bit contain logic high
					return_value = LOGIC_HIGH; // return logic high
				else //mean bit contain logic low
					return_value = LOGIC_LOW;
				break;
			case PORTD_ID :
				if(BIT_IS_SET(PIND,PIN_NUM))//mean bit contain logic high
					return_value = LOGIC_HIGH; // return logic high
				else //mean bit contain logic low
					return_value = LOGIC_LOW;
				break;
			
		}
	}
	return return_value;
}

void DIO_togglePin(uint8_t PORT_X ,uint8_t PIN_NUM)
{
	if( (PIN_NUM >= NUM_OF_PIN_PER_PORT) || (PORT_X >= NUM_OF_PORT) )
	{
		//Error handling ,Nothing to do
	}
	else
	{
		switch(PORT_X)
		{
			case PORTA_ID:
				if(BIT_IS_SET(DDRA,PIN_NUM))//check if this pin is output pin ,as if output will toggle else will do nothing
					TOGGLE_BIT(PORTA,PIN_NUM);
				break;
			case PORTB_ID:
				if(BIT_IS_SET(DDRB,PIN_NUM))//check if this pin is output pin ,as if output will toggle else will do nothing
					TOGGLE_BIT(PORTB,PIN_NUM);
				break;
			case PORTC_ID:
				if(BIT_IS_SET(DDRC,PIN_NUM))//check if this pin is output pin ,as if output will toggle else will do nothing
					TOGGLE_BIT(PORTC,PIN_NUM);
				break;
			case PORTD_ID:
				if(BIT_IS_SET(DDRD,PIN_NUM))//check if this pin is output pin ,as if output will toggle else will do nothing
					TOGGLE_BIT(PORTD,PIN_NUM);
					break;
		}
	}
}

void DIO_setupPortDirection(uint8_t PORT_X , GPIO_PortDirectionTypes DIRECTION)
{
	if(  (PORT_X >= NUM_OF_PORT) )
	{
		//Error handling ,Nothing to do
	}
	else
	{
		switch(PORT_X)
		{
			case PORTA_ID:
				DDRA = DIRECTION;
				if(DIRECTION == INPUT_PORT_PULLUP)
					PORTA = 0xFF;
				break;
			case PORTB_ID:
				DDRB = DIRECTION;
				if(DIRECTION == INPUT_PORT_PULLUP)
					PORTB = 0xFF;
				break;
			case PORTC_ID:
				DDRC = DIRECTION;
				if(DIRECTION == INPUT_PORT_PULLUP)
					PORTC = 0xFF;
				break;
			case PORTD_ID:
				DDRD = DIRECTION;
				if(DIRECTION == INPUT_PORT_PULLUP)
					PORTD = 0xFF;
				break;
				
			
		}
	}
}

void DIO_writePort(uint8_t PORT_X, uint8_t value)
{
	if(  (PORT_X >= NUM_OF_PORT) )
	{
		//Error handling ,Nothing to do
	}
	else
	{
		switch(PORT_X)
		{
			case PORTA_ID:
				//if(DDRA == 0xFF)//check that all port is output port to put value in PORT register
					PORTA = value;
				break;
			case PORTB_ID:
				//if(DDRB == 0xFF)//check that all port is output port to put value in PORT register
					PORTB = value;
				break;
			case PORTC_ID:
				//if(DDRC == 0xFF)//check that all port is output port to put value in PORT register
					PORTC = value;
				break;
			case PORTD_ID:
				//if(DDRD == 0xFF)//check that all port is output port to put value in PORT register
					PORTD = value;
				break;
		}
	}
}

uint8_t DIO_readPort(uint8_t PORT_X)
{
	uint8_t return_value = LOGIC_LOW;
	if(  (PORT_X >= NUM_OF_PORT) )
	{
		//Error handling ,Nothing to do
	}
	else
	{
		switch(PORT_X)
		{
			case PORTA_ID:
				return_value = PINA;
				break;
			case PORTB_ID:
				return_value = PINB;
				break;
			case PORTC_ID:
				return_value = PINC;
				break;
			case PORTD_ID:
				return_value = PIND;
				break;
				
		}
	}
	return return_value;
}