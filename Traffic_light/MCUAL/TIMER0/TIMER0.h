 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: timer0.h
 *
 * Description: Header file for the AVR timer0 driver
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef TIMER_H_
#define TIMER_H_

#include "../../utilities/std_types.h"
#include "../../utilities/MCU_register.h"
#include "../../utilities/common_macros.h"
 /*******************************************************************************
 *                         Configuration                                        *
 *******************************************************************************/
#define  F_CPU_MCU  1 * 1000000

 /*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
  typedef enum
 {
	 NORMAL_MODE,PHASE_CORRECT_MODE,CTC_MODE,FAST_PWM_MODE
 }TIMER0_mode;
 
 typedef enum
 {
	 NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
 }TIMER0_clock;
  typedef struct
 {
	 TIMER0_mode mode;
	 TIMER0_clock clock;
 }Timer0_ConfigType;


	
	
 /*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
 
  /*
 * Description : 
 * 	1. Set the required mode.
 * 	2. Set the required prescaler.
 * @argument 
 * config_Ptr : is pointer to variable contain wanted MODE & PRESCALLER
 */
 void TIMER0_init(const Timer0_ConfigType * config_Ptr);
 
/*
* Description : 
* 	make delay 
* as it take number of count and initial value and this value provided in this case
* if T_delay < T_max_delay then number of count =1 and Timer_initail_value = (T_max_delay - T_delay)/T_tick
* if T_delay = T_max_delay then number of count =1 and Timer_initail_value = 0
* T_delay > T_max_delay then number of count(num_overflow) =(ceil) (T_delay / T_max_delay) and Timer_initail_value = 256 - ( (T_delay / T_tick) / number of count)
*/
/*
 void TIMER0_delay(uint16_t num_count , uint8_t initial_value);
*/
 
 /*
 * Note
 * 100     ->this is 100 Us delay  num < 10^3 delay in Msec ( micro second)  -->micro not work(not supported)
 * 1000    ->this is 1 ms delay  num * 10^3  delay im msec (milli second) 
 * 1000000 ->this is 1 sec delay   num * 10^6  delay in sec
 * @argument :
 * T_delay :wanted delay
 */
 /////Note for some round in calculation minimum delay can ably is 3 msec and function take 2000  and more increase delay accuracy increase
 void TIMER0_Delay_ms(uint32_t T_delay);
 
/*
* Description : 
* stop timer0 as make no clock source for Timer 0 peripheral
*/
 void TIMER0_stop(void);
 
 /*
 * Description :
 * stop loop make for delay because when there is ISR during delay ,delay will cut but will continue delay so this function end delay
 */
 void TIMER0_endDelay(void);
 
 
#endif /* TIMER_H_ */