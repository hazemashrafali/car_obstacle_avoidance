/*
 * led.h
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_


/*============= FILE INCLUSION =============*/
#include "..\..\MCAL\gpio\gpio.h"

/*============= TYPE DEFINITION =============*/

typedef enum{
	LED_INVALID_OPERATION	=0,
	LED_VALID_OPERATION		=1,
	LED_INVALID_PORT_ID		=2,
	LED_INVALID_PIN_ID		=3,
	LED_INVALID_DIRECTION	=4,
}enu_led_error_t;

/*============= FUNCTION PROTOTYPE =============*/

/**
 * @brief       led_init				:   Function used to Setup the direction of the led to be OUTPUT
 *
 * @param[in]   port					:	port name id should be [PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin						:	pin name id should be  [PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 *
 * @return      VALID_OPERATION			:   in case of successful operation
 *              INVALID_PORT_ID 		:   in case of wrong port id
 *				INVALID_PIN_ID			:	in case of wrong pin id
 */
enu_led_error_t led_init(uint8 port,uint8 pin);

/**
 * @brief       led_write				:   Function used to write the value of the led to be high or low
 *
 * @param[in]   port					:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin						:	pin name id should be	[PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 * @param[in]	led_state				:	led state should be		[PIN_LOW,PIN_HIGH]
 *
 * @return      VALID_OPERATION			:   in case of successful operation
 *              INVALID_PORT_ID 		:   in case of wrong port id
 *				INVALID_PIN_ID			:	in case of wrong pin id
 *				INVALID_OPERATION		:	in case of wrong led_state
 */
enu_led_error_t led_write(uint8 port,uint8 pin,enu_pin_value_t led_state);

/**
 * @brief       led_toggle				:   Function used to toggle the logic of the required led
 *
 * @param[in]   port					:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin						:	pin name id should be	[PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 *
 * @return      VALID_OPERATION			:   in case of successful operation
 *              INVALID_PORT_ID 		:   in case of wrong port id
 *				INVALID_PIN_ID			:	in case of wrong pin id
 */
enu_led_error_t led_toggle(uint8 port,uint8 pin);


#endif /* HAL_LED_LED_H_ */
