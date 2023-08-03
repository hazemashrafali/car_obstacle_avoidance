/*
 * ultrasonic.h
 *
 * Created: 2023-07-26 9:31:42 PM
 *  Author: HAZEM-PC
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


/*============= FILE INCLUSION =============*/
#include "..\ICU\icu.h"
#include "..\..\MCAL\DIO\gpio.h"

/*===============EXTERNAL VARIBALS ================*/

/*============= MACRO DEFINITION =============*/
#define ULTRASONIC_TIMER_ID		1	//select the timer_id, it should be [0,1,2]

/*===============GLOBAL VARIBALS ================*/


/*===============TYBS DEFINTION ================*/
typedef enum{
	ENU_ECHO_ID_0	= 0	,
	ENU_ECHO_ID_1		,
	ENU_ECHO_ID_2		,
	ENU_MAX_ECHO
}enu_echo_pin_id_t;

typedef enum{
	ENU_USONIC_STATE_VALID	= 0	,
	ENU_USONIC_STATE_INVALID	,
	ENU_MAX_USONIC_STATE
}enu_usonic_state_t;

/*============= FUNCTION PROTOTYPE =============*/

/**
 * @brief       Ultrasonic_init				: Function to initialize the ultrasonic driver
 *											  initialize ICU driver,set callback function,setup trigger pin direction as output
 *											  setup External interrupt source
 *
 * @param[in]   u8_triggerPort				: the port id of trigger terminal 
 * @param[in]   u8_triggerPin				: the pin id of trigger terminal
 * @param[in]   enu_echo_pin_id				: the pin of echo terminal, it should be connected to external interrupt hardware pin
 *
 * @return      ENU_USONIC_STATE_INVALID	: in case of invalid operation
 *				ENU_USONIC_STATE_VALID		: in case of valid operation
 */
enu_usonic_state_t Ultrasonic_init(uint8 u8_triggerPort,uint8 u8_triggerPin,enu_echo_pin_id_t enu_echo_pin_id);

/**
 * @brief       Ultrasonic_readDistance		: function to read distance of from the sensor

 *
 * @param[out]   ptr_u16_distanceValue		: reference to the value of the sensor distance reading
 *
 * @return      ENU_USONIC_STATE_INVALID	: in case of invalid operation
 *				ENU_USONIC_STATE_VALID		: in case of valid operation
 */
enu_usonic_state_t Ultrasonic_readDistance(uint16* ptr_u16_distanceValue);



#endif /* ULTRASONIC_H_ */