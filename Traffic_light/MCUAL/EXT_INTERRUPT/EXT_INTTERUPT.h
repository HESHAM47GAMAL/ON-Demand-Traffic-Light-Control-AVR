/******************************************
* Module: EXT_INTERRUPT
*
* File Name: EXT_INTERRUPT.h
*
* Description: header file for AVR external interrupt
*
* Author: Hesham Shehata
*
******************************************/



#ifndef EXT_INTTERUPT_H_
#define EXT_INTTERUPT_H_

#include "../../utilities/common_macros.h"
#include "../../utilities/MCU_register.h"
#include "../../utilities/std_types.h"
#include "../../utilities/IVT.h"

#include "../DIO/DIO.h"

 /*******************************************************************************
 *                              Types Definition                            *
 *******************************************************************************/
 typedef enum
 {
	 LOW_LEVEL_TRIGGER,
	 ANY_LOGIC_CHANGE_TRIGGER,
	 FALLING_EDGE_TRIGGER,
	 RISING_EDGE_TRIGGER
 }EXT_triggerType;

 /*******************************************************************************
 *                              Functions Prototypes                            *
 *******************************************************************************/
 
/*
* Description:
* call assembly function to enable global interrupt
*/
void GLOBAL_INTERRUPT_ENABLE(void);

/*
* Description:
* call assembly function to disable global interrupt
*/
void GLOBAL_INTERRUPT_DISABLE(void);
 
/*
* Description:
* set type of trigger first then enable EXT interrupt 0
* set pin as input or input pulled up
* @arguement  
* triggerType : conatain type of trigger will make interrupt
* direction : use to make this pin input pin or input pin with internal pull up register
*/
void INT0_init( EXT_triggerType triggerType,GPIO_PinDirectionTypes direction);

/*
* Description:
* set type of trigger first then enable EXT interrupt 1
* set pin as input or input pulled up
* @arguement
* triggerType : conatain type of trigger will make interrupt
* direction : use to make this pin input pin or input pin with internal pull up register
*/
void INT1_init( EXT_triggerType triggerType ,GPIO_PinDirectionTypes direction);

/*
* Description:
* set type of trigger first then enable EXT interrupt 2
* set pin as input or input pulled up
* @arguement
* triggerType : conatain type of trigger will make interrupt
* direction : use to make this pin input pin or input pin with internal pull up register
*/
void INT2_init( EXT_triggerType triggerType ,GPIO_PinDirectionTypes direction);

/*
* Description:
* disable EXT interrupt 0
*/
void INT0_deInit(void);

/*
* Description:
* disable EXT interrupt 1
*/
void INT1_deInit(void);

/*
* Description:
* disable EXT interrupt 2
*/
void INT2_deInit(void);

#endif /* EXT_INTTERUPT_H_ */