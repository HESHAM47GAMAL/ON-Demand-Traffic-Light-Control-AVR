/*
 * APP.h
 *
 * Created: 8/16/2022 7:55:19 PM
 *  Author: 20112
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/LED/LED.h"
#include "../ECUAL/LCD/LCD.h"
#include "../MCUAL/EXT_INTERRUPT/EXT_INTTERUPT.h"
#include "../MCUAL/TIMER0/TIMER0.h"

/********************************************************************
*                              Types Decleration
********************************************************************/

typedef enum
{
	NORMAL_STATE,
	RED_LED_CAR_STATE ,
	YELLOW_GREEN_CAR_STATE	
}car_lightState;

typedef enum 
{
	NO_INTERRUPT_HAPPEN,
	DOING_INTERRUPT_HAPPEN	
}ISR_state;

/*********************************************************
*               Prototypes
*********************************************************/

/*
* Description:
* contain all function initialization
*/
void APP_init(void);

/*
* Description:
* contain flow of program
*/
void APP_start(void);

/*
* Description:
* implement for normal car traffic light
*/
void CAR_trafficLight(void);

/*
* Description:
* implement for traffic light when pedestrian press on button when car traffic light is red on
*/
void CAR_redLedState(void);

/*
* Description:
* implement for traffic light when pedestrian press on button when car traffic light is green or yellow on
*/
void CAR_yellowGreenLedState(void);

/*
* Description:
* function called in "CAR_yellowGreenLedState()" and "CAR_redLedState" as commen steps for two function
*/
void CAR_endOfTwoStates(void);

#endif /* APP_H_ */