 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "../../MCUAL/DIO/DIO.h"
#include "../../MCUAL/TIMER0/TIMER0.h"

/*******************************************************************************
 *                               Configuration                                  *
 *******************************************************************************/
 #define LCD_RS_PORT_ID     PORTA_ID
 #define LCD_RS_PIN_ID      PIN5_ID
						    
 #define LCD_RW_PORT_ID     PORTA_ID
 #define LCD_RW_Pin_ID      PIN6_ID
						    
 #define LCD_E_PORT_ID      PORTA_ID
 #define LCD_E_PIN_ID       PIN7_ID 
						    
 #define LCD_DATA_PORT_ID   PORTC_ID
 
 /*
 *  ############################## Set BIT MODE (4 or 8) ##############################
 */
 #define LCD_DATA_BITS_MODE   8
 
#if( (LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8) )

#error "Number of Data bits should be equal to 4 or 8"

#endif
/*###########edit###########*/
#if (LCD_DATA_BITS_MODE == 4)/*@ this mode connect MCU port pins to D4 : D7 of LCD */
/*
* there will use only four bits for data and can choose using lower 4 bits or higher 4 bits
* if need use lower bits comment next macros ,if need use higher bits don't comment macro
*/

#define LCD_LAST_PORT_PINS

#ifdef LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID    PIN4_ID
#else 
#define LCD_FIRST_DATA_PIN_ID    PIN0_ID
#endif

#endif
 
 
 /*******************************************************************************
 *                               Definitions                                    *
 *******************************************************************************/
 
 /*
 * ############################## Set LCD AND THIS COMMAND USED IN INIT FUNCTION ##############################
 */
 //LCD commands
#define LCD_8_BITS_2_LINES                 0x38
#define LCD_8_BITS_1_LINES                 0x30
#define LCD_4_BITS_2_LINES                 0x28
#define LCD_4_BITS_1_LINES                 0x20
#define LCD_RETURN_HOME                    0x02
#define LCD_CLEAR_SCREEN                   0x01
#define LCD_DISPLAY_OFF_CURSOR_OFF         0x08
#define LCD_DISPLAY_ON_CURSOR_ON           0x0E
#define LCD_DISPLAY_ON_CURSOR_OFF  	  	   0x0C
#define LCD_DISPLAY_ON_CURSOR_BLINKING     0x0F
#define LCD_SHIFT_ENTIRE_DISPLAY_LEFT      0x07 /*write to specific position and when write next character will shift previous character to left and write new character in same position*/
#define LCD_SHIFT_ENTIRE_DISPLAY_RIGHT     0x04 /*write to specific position and next character will placed in next position*/
/*
has no affect or I use it incorrect
#define LCD_MOVE_CURSOR_LEFT               0x10
#define LCD_MOVE_CURSOR_RIGHT              0x14
*/
#define LCD_SET_CURSOR_LOCATION_DDRAM      0x80
#define LCD_SET_CURSOR_LOCATION_CGRAM      0x40

#define LCD_CGRAM_LOCATION_1               0
#define LCD_CGRAM_LOCATION_2               1
#define LCD_CGRAM_LOCATION_3               2
#define LCD_CGRAM_LOCATION_4               3
#define LCD_CGRAM_LOCATION_5               4
#define LCD_CGRAM_LOCATION_6               5
#define LCD_CGRAM_LOCATION_7               6
#define LCD_CGRAM_LOCATION_8               7

 /*******************************************************************************
 *                              Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * Setup the LCD pins directions by use the GPIO driver.
 * Setup the LCD Data Modes & put any config of display here.
 */
void LCD_init(void);

/*
 * Description :
 * Send the required command to the screen
 * @arguement
 * command : command line that want to send to LCD
 */
void LCD_sendCommand(uint8_t command);

/*
 * Description :
 * Display the required character on the screen
 * @argument 
 * data: variable contain character want to display in LCD
 */
void LCD_displayCharacter(uint8_t data);

/*
 * Description :
 * Display the required string on the screen
 * @argument
 * string: pointer to array of character want to display in LCD
 */
void LCD_displayString(const uint8_t * string);

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 * @argument
 * row: variable contain row number want to begin display character on
 * column: variable contain column number want to begin display character on
 */
void LCD_moveCursor(uint8_t row ,uint8_t column);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 * @argument
 * string: pointer to array of character want to display in LCD
 * row: variable contain row number want to begin display character on
 * column: variable contain column number want to begin display character on
 */
void LCD_displayStringRowColumn(const uint8_t * string ,uint8_t row ,uint8_t column);

/*
 * Description :
 * Display the required decimal value on the screen
  * @argument
  * data: variable contain value that will take digit digit to convert to character and display on LCD
 */
void LCD_intToString(uint32_t data);

/*
 * Description :
 * Send the clear screen command and return to begin of LCD
 */
void LCD_clearScreen(void);

/*
 * Description :
 * return to begin of LCD without remove display content
 */
void LCD_goBeginOfScreen(void);

/*
 * Description :
 * store custom character in CGRAM to able to display
 * and set cursor(0,0) because it avoid some error happened during debbug and try
 * @argument
 * ptr_newchar: pointer to array of character want to stored in CGRAM 
 * location: location number for CGRAM want to store customized character want
 */
void LCD_generateCustomCharacter(uint8_t *ptr_newchar,uint8_t location);

/*
 * Description :
 * store human move in CGRAM to be able to display it
 */
void LCD_humanMoveInit(void);

/*
 * Description :
 * display human move
 * @argument
 * row: variable contain row number want to begin display human move
 * column: variable contain column number want to begin display human move
 */
void LCD_humanMoveDisplay(uint8_t row ,uint8_t column);

/*
 * Description :
 * store hand in CGRAM to be able to display it
 */
void LCD_handInit(void);

/*
 * Description :
 * display hand
 * @argument
 * row: variable contain row number want to begin display human move
 * column: variable contain column number want to begin display human move
 */
void LCD_handDisplay(uint8_t row ,uint8_t column);

#endif /* LED_H_ */