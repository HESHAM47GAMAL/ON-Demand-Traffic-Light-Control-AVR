 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/
 
 #include "LCD.h"
 #include <stdlib.h>
 #include <string.h>
 
 uint8_t human_1_Move[] ={0x0E,0x04,0x0E,0x16,0x04,0x0A,0x12,0x00};
 uint8_t human_2_Move[]={0x0E,0x04,0x0E,0x0D,0x04,0x0A,0x09,0x00};
	 
 uint8_t hand_sign[] = {0x06,0x0F,0x0F,0x1F,0x1F,0x1F,0x0E,0x00};
	 
 void LCD_init(void)
 {
	 //set direction for pin RS, R/W & E
	 DIO_setupPinDirection(LCD_RS_PORT_ID , LCD_RS_PIN_ID ,OUTPUT_PIN);
	 DIO_setupPinDirection(LCD_RW_PORT_ID , LCD_RW_Pin_ID ,OUTPUT_PIN);
	 DIO_setupPinDirection(LCD_E_PORT_ID , LCD_E_PIN_ID ,OUTPUT_PIN);
	 /*set direction for pins that send data to lCD*/
	 #if (LCD_DATA_BITS_MODE == 4)
		
		DIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_FIRST_DATA_PIN_ID ,OUTPUT_PIN);
		DIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_FIRST_DATA_PIN_ID +1 ,OUTPUT_PIN);
		DIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_FIRST_DATA_PIN_ID +2 ,OUTPUT_PIN);
		DIO_setupPinDirection(LCD_DATA_PORT_ID , LCD_FIRST_DATA_PIN_ID +3,OUTPUT_PIN);
		LCD_sendCommand(LCD_RETURN_HOME);/*this line important in 4 bit mode will not work without this line and I don't know reason*/
	 #else
		DIO_setupPortDirection(LCD_DATA_PORT_ID , OUTPUT_PORT);
	 #endif
	 
	 /*
	 * ##################### put any setting for lcd like: cursor on or off and shift screen right or left #####################
	 */
	 /* choose 8bit or 4bit depend on macros in configuration */
	 #if (LCD_DATA_BITS_MODE == 4 )
		 LCD_sendCommand(LCD_4_BITS_2_LINES);
	 #else
		 LCD_sendCommand(LCD_8_BITS_2_LINES);
	 #endif
	 LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_OFF);/*should call to make display on*/
	 LCD_sendCommand(LCD_SHIFT_ENTIRE_DISPLAY_RIGHT);
	 LCD_sendCommand(LCD_CLEAR_SCREEN);
	 
	 
	 
 }
 
 void LCD_sendCommand(uint8_t command)
 {
	 DIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID ,LOGIC_LOW); /*clear RS to use command register*/
	 DIO_writePin(LCD_RW_PORT_ID , LCD_RW_Pin_ID ,LOGIC_LOW); /*clear R/W to write data to LCD*/
	 TIMER0_Delay_ms(1300); /* delay for processing Tas = 50ns */
	 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_HIGH);  /* Enable LCD E=1 */
	 TIMER0_Delay_ms(1300); /* delay for processing Tpw - Tdws = 190ns */	
	 #if( LCD_DATA_BITS_MODE == 4)
		 uint8_t PORT_value;
		 PORT_value = DIO_readPort(LCD_DATA_PORT_ID);/*read content of port to save value for pins not connected to LCD*/
	 /*bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0*/
		 #ifdef LCD_LAST_PORT_PINS  
			 /*use last 4 pins */
			 PORT_value = (PORT_value & 0x0F) | (command & 0xF0); /*send last 4 bits of command*/
		 #else 
			 /*use first 4 pins */
			 PORT_value = (PORT_value & 0xF0) | ((command & 0xF0) >> 4); /*send last 4 bits of command*/
		 #endif
		 DIO_writePort(LCD_DATA_PORT_ID,PORT_value);
		 TIMER0_Delay_ms(1300); /* delay for processing Tdsw = 100ns */
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_LOW);  /* Disable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Th = 13ns */
		 
		 
		 /*send second part of command*/
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_HIGH);  /* Enable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Tpw - Tdws = 190ns */	
		 PORT_value = DIO_readPort(LCD_DATA_PORT_ID);
		 #ifdef LCD_LAST_PORT_PINS  
			 /*use last 4 pins */
			 PORT_value = (PORT_value & 0x0F) | ((command & 0x0F) << 4); /*send last 4 bits of command*/
		 #else 
			 /*use first 4 pins */
			 PORT_value = (PORT_value & 0xF0) | ((command & 0x0F) ); /*send last 4 bits of command*/
		 #endif
		 DIO_writePort(LCD_DATA_PORT_ID,PORT_value);
		 TIMER0_Delay_ms(1300); /* delay for processing Tdsw = 100ns */
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_LOW);  /* Disable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Th = 13ns */
	 
	 #elif( LCD_DATA_BITS_MODE == 8)
		 DIO_writePort( LCD_DATA_PORT_ID ,command);
		 TIMER0_Delay_ms(1300); /* delay for processing Tdsw = 100ns */
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_LOW);  /* Disable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Th = 13ns */
		 
	 #endif
 }
 
 void LCD_displayCharacter(uint8_t data)
 {
	 DIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID ,LOGIC_HIGH); /*set RS to use data register*/
	 DIO_writePin(LCD_RW_PORT_ID , LCD_RW_Pin_ID ,LOGIC_LOW); /*clear R/W to write data to LCD*/
	 TIMER0_Delay_ms(1300); /* delay for processing Tas = 50ns */
	 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_HIGH);  /* Enable LCD E=1 */
	 TIMER0_Delay_ms(1300); /* delay for processing Tpw - Tdws = 190ns */
	 #if( LCD_DATA_BITS_MODE == 4)
		 uint8_t PORT_value;
		 PORT_value = DIO_readPort(LCD_DATA_PORT_ID);/*read content of port to save value for pins not connected to LCD*/
	 /*bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0*/
		 #ifdef LCD_LAST_PORT_PINS  
			 /*use last 4 pins */
			 PORT_value = (PORT_value & 0x0F) | (data & 0xF0); /*send last 4 bits of command*/
		 #else 
			 /*use first 4 pins */
			 PORT_value = (PORT_value & 0xF0) | ((data & 0xF0) >> 4); /*send last 4 bits of command*/
		 #endif
		 DIO_writePort(LCD_DATA_PORT_ID,PORT_value);
		 TIMER0_Delay_ms(1300); /* delay for processing Tdsw = 100ns */
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_LOW);  /* Disable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Th = 13ns */
		 
		 
		 /*send second part of command*/
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_HIGH);  /* Enable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Tpw - Tdws = 190ns */	
		 PORT_value = DIO_readPort(LCD_DATA_PORT_ID);
		 #ifdef LCD_LAST_PORT_PINS  
			 /*use last 4 pins */
			 PORT_value = (PORT_value & 0x0F) | ((data & 0x0F) << 4); /*send last 4 bits of command*/
		 #else 
			 /*use first 4 pins */
			 PORT_value = (PORT_value & 0xF0) | ((data & 0x0F) ); /*send last 4 bits of command*/
		 #endif
		 DIO_writePort(LCD_DATA_PORT_ID,PORT_value);
		 TIMER0_Delay_ms(1300); /* delay for processing Tdsw = 100ns */
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_LOW);  /* Disable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Th = 13ns */
	 
	 #elif( LCD_DATA_BITS_MODE == 8)
		 DIO_writePort( LCD_DATA_PORT_ID ,data);
		 TIMER0_Delay_ms(1300); /* delay for processing Tdsw = 100ns */
		 DIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID ,LOGIC_LOW);  /* Disable LCD E=1 */
		 TIMER0_Delay_ms(1300); /* delay for processing Th = 13ns */
		 
	 #endif
 }
 
void LCD_displayString(const uint8_t * string)
{
	 /* print string until NULL character */
	 while( (*string) != '\0')
	 {
		 LCD_displayCharacter(*string);
		 string++;
	 }
	 /***************** Another Method ***********************
	 uint8_t I = 0;
	 while (string[I] != '\0')
	 {
		 LCD_displayCharacter(*string);
		 I++;
	 }
	*********************************************************/	
}


void LCD_moveCursor(uint8_t row ,uint8_t column)
{
	 uint8_t address_DDRAM = 0 ;
	 switch( row )
	 {
		 case 0:
			address_DDRAM = column ;
			break;
		 case 1:
			address_DDRAM = 0x40 + column ;
			break;
		 case 2:
			address_DDRAM = 0x10 + column ;
			break;
		 case 3:
			address_DDRAM = 0x50 + column ;
			break;
			
	 }
	 LCD_sendCommand(address_DDRAM | LCD_SET_CURSOR_LOCATION_DDRAM);
}


void LCD_displayStringRowColumn(const uint8_t * string ,uint8_t row ,uint8_t column)
{
	 LCD_moveCursor(row,column);
	 LCD_displayString(string);
}

void LCD_intToString(uint32_t data)
{
	 char string_buff[17];// I write char not sint8_t(signed char ) to avoid warning
	 itoa(data , string_buff , 10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	 LCD_displayString( (uint8_t *)string_buff);
}

void LCD_clearScreen(void)
{
	 LCD_sendCommand(LCD_CLEAR_SCREEN); /* Send clear display command */
}

void LCD_goBeginOfScreen(void)
{
	LCD_sendCommand(LCD_RETURN_HOME);
}

void LCD_generateCustomCharacter(uint8_t *ptr_newchar,uint8_t location)
{
	LCD_sendCommand( LCD_SET_CURSOR_LOCATION_CGRAM + (location *8));
	 for(uint8_t count=0; count<8 ; count++)
	 {
		 
		 LCD_displayCharacter(ptr_newchar[count]);
	 }
	 LCD_moveCursor(0,0);
}

void LCD_humanMoveInit(void)
{
	LCD_generateCustomCharacter(human_1_Move , LCD_CGRAM_LOCATION_1);
	LCD_generateCustomCharacter(human_2_Move , LCD_CGRAM_LOCATION_2);
}

void LCD_humanMoveDisplay(uint8_t row ,uint8_t column)
{
	LCD_moveCursor(row,column);
	LCD_displayCharacter(LCD_CGRAM_LOCATION_1);
	LCD_moveCursor(row,column);
	LCD_displayCharacter(LCD_CGRAM_LOCATION_2);
	
	
}

void LCD_handInit(void)
{
	LCD_generateCustomCharacter(hand_sign,LCD_CGRAM_LOCATION_3);
}

void LCD_handDisplay(uint8_t row ,uint8_t column)
{
	LCD_moveCursor(row,column);
	LCD_displayCharacter(LCD_CGRAM_LOCATION_3);
}

