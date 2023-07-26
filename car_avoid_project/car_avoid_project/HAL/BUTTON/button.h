/*
 * button.h
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

#ifndef HAL_BUTTON_BUTTON_H_
#define HAL_BUTTON_BUTTON_H_

/*============= FILE INCLUSION =============*/
#include "..\..\MCAL\DIO\gpio.h"

/*============= TYPE DEFINITION =============*/
typedef enum{
	BTN_INVALID_OPERATION	=0,
	BTN_VALID_OPERATION		=1,
	BTN_INVALID_PORT_ID		=2,
	BTN_INVALID_PIN_ID		=3,
	BTN_INVALID_DIRECTION	=4,
}enu_button_error_t;
/*============= FUNCTION PROTOTYPE =============*/

/**
 * @brief       button_init				:   Function used to Setup the direction of the button to be INPUT
 *
 * @param[in]   port					:	port name id should be [PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin						:	pin name id should be  [PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 *
 * @return      VALID_OPERATION			:   in case of successful operation
 *              INVALID_PORT_ID 		:   in case of wrong port id
 *				INVALID_PIN_ID			:	in case of wrong pin id
 */
enu_button_error_t button_init(uint8 port,uint8 pin);

/**
 * @brief       button_init				:   Function used to enable the internal pull_up resistor
 *
 * @param[in]   port					:	port name id should be [PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin						:	pin name id should be  [PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 *
 * @return      VALID_OPERATION			:   in case of successful operation
 *              INVALID_PORT_ID 		:   in case of wrong port id
 *				INVALID_PIN_ID			:	in case of wrong pin id
 */
enu_button_error_t button_enable_pullup (uint8 port,uint8 pin);

/**
 * @brief       button_read					:   Function used to Read and return the value of the button, it should be Logic High or Logic Low
 *
 * @param[in]   port						:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin							:	pin name id should be	[PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 * @param[out]	value						:	the value of the required pin
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 *				INVALID_PIN_ID				:	in case of wrong pin id
 *				INVALID_OPERATION			:	in case of passing NULL pointer
 */
enu_button_error_t button_read(uint8 port,uint8 pin,uint8* value);



#endif /* HAL_BUTTON_BUTTON_H_ */
