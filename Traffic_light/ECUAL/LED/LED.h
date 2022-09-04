/******************************************
* Module: LED
*
* File Name: LED.h
*
* Description: header file for AVR LED Driver
*
* Author: Hesham Shehata
*
******************************************/


#ifndef LED_H_
#define LED_H_

#include "../../MCUAL/DIO/DIO.h"
#include "../../MCUAL/TIMER0/TIMER0.h"


/*********************************************************
*               Prototypes
*********************************************************/

/*
* Description:
* set pin for specific port as output pin to be able to connect led
* if input port number and pin number are not correct ,function will not handle request
* @arguement
* PORT_X : port wanted to be set for pin direction as output pin
* PIN_NUM : pin wanted
*/
void LED_init(uint8_t PORT_X , uint8_t PIN_NUM);

/*
* Description:
* set pin high to turn led on if connected as active high or turn led off if connected as active low 
* if input port number and pin number are not correct ,function will not handle request
* if this pin not make for it "LED_init function and not output pin " ,function will not handle request
* @arguement
* PORT_X : port wanted to control pin in
* PIN_NUM : pin wanted to set as logic high pin
*/
void LED_on(uint8_t PORT_X , uint8_t PIN_NUM);

/*
* Description:
* Clear pin high to turn led off if connected as active high or turn led on if connected as active low
* if input port number and pin number are not correct ,function will not handle request
* if this pin not make for it "LED_init function and not output pin " ,function will not handle request
* @arguement
* PORT_X : port wanted to control pin in
* PIN_NUM : pin wanted to set as logic low pin
*/
void LED_off(uint8_t PORT_X , uint8_t PIN_NUM);

/*
* Description:
* Toggle pin
* if input port number and pin number are not correct ,function will not handle request
* if this pin not make for it "LED_init function and not output pin " ,function will not handle request
* @arguement
* PORT_X : port wanted to control pin in
* PIN_NUM : pin wanted to toggle its value
*/
void LED_toggle(uint8_t PORT_X , uint8_t PIN_NUM);

/*
* Description:
* set pin high to turn led on if connected as active high or turn led off if connected as active low
* if input port number and pin number are not correct ,function will not handle request
* if this pin not make for it "LED_init function and not output pin " ,function will not handle request
* the delay for specefic time
* @arguement
* PORT_X : port wanted to control pin in
* PIN_NUM : pin wanted to set as logic high pin for specific time
* T_delay: delay wanted 
*/
void LED_onWithDelay(uint8_t PORT_X , uint8_t PIN_NUM,uint32_t T_delay);

/*
* Description:
* set pin low to turn led off if connected as active high or turn led off if connected as active low
* if input port number and pin number are not correct ,function will not handle request
* if this pin not make for it "LED_init function and not output pin " ,function will not handle request
* the delay for specefic time
* @arguement
* PORT_X : port wanted to control pin in
* PIN_NUM : pin wanted to set as logic low pin for specific time
* T_delay: delay wanted
*/
void LED_offWithDelay(uint8_t PORT_X , uint8_t PIN_NUM,uint32_t T_delay);

/*
* Description:
* will set pin high for half second then low for half second and will repeat it for number of times 
* @arguement
* PORT_X : port wanted to control pin in
* PIN_NUM : pin wanted to set as logic high pin for specific time
* time_of_blinking: delay wanted in second (as one blink take one second)
*/
void LED_blink(uint8_t PORT_X , uint8_t PIN_NUM,uint32_t time_of_blinking);

/*
* Description:
* will set pin high for half second then low for half second and will repeat it for number of times
* as delay make in looping on flag so we can't blink two leds in same take by call previous function twice so this function take to pin together to make for them blink
* @arguement
* PORT_X_1 : port_1 wanted to control pin in
* PIN_NUM_1 : pin_1 wanted to set as logic high pin for specific time
* PORT_X_2 : port_2 wanted to control pin in
* PIN_NUM_2 : pin_2 wanted to set as logic high pin for specific time
* time_of_blinking: delay wanted in second (as one blink take one second)
*/
void LED_blinkForTwoPins(uint8_t PORT_X_1 , uint8_t PIN_NUM_1,uint8_t PORT_X_2 , uint8_t PIN_NUM_2,uint32_t time_of_blinking);

/*
* Description:
* this function stop blinking  as call function timer0_endDelay(as end loop doing to make specific delay wanted)
* if during blinking as during first delay(as in blinking function there are two delay)specific when interrupt happen after handling will complete delay and some application may need to go out this delay  immediately
* so this function solve problem as interrupt called at first or second delay this function will handle every thing
*/
void LED_stopBlink(void);

#endif /* LED_H_ */