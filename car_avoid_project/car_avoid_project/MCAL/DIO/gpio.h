/*
 * gpio.h
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

/*============= FILE INCLUSION =============*/
#include "..\..\Utilities\Common_Macros.h"
#include "..\..\Utilities\Std_Types.h"
#include "..\..\Utilities\registers.h"

/*============= TYPE DEFINITION =============*/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}enu_pin_direction_t;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}enu_port_direction_t;

typedef enum{
	PIN_LOW,PIN_HIGH
}enu_pin_value_t;

typedef enum{
	PORT_LOW,PORT_HIGH=0xFF
}enu_port_value_t;

typedef enum{
	DIO_INVALID_OPERATION	=0,
	DIO_VALID_OPERATION		=1,
	DIO_INVALID_PORT_ID		=2,
	DIO_INVALID_PIN_ID		=3,
	DIO_INVALID_DIRECTION	=4,
}enu_dio_error_t;

#define PORTA_ID		0
#define PORTB_ID		1
#define PORTC_ID		2
#define PORTD_ID		3
#define MAX_PORT_ID		4

#define PIN0_ID			0
#define PIN1_ID			1
#define PIN2_ID			2
#define PIN3_ID			3
#define PIN4_ID			4
#define PIN5_ID			5
#define PIN6_ID			6
#define PIN7_ID			7
#define MAX_PIN_ID		8

/*============= FUNCTION PROTOTYPE =============*/

/**
 * @brief       DIO_pinMode                 :   Function used to Setup the direction of the required pin input/output
 *
 * @param[in]   port						:	port name id should be [PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin							:	pin name id should be  [PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 * @param[in]   direction					:	pin direction should be [PIN_INPUT,PIN_OUTPUT]
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 *				INVALID_PIN_ID				:	in case of wrong pin id
 *				INVALID_DIRECTION			:	in case of wrong direction
 */
enu_dio_error_t DIO_pinMode	(uint8 port,uint8 pin,enu_pin_direction_t direction);

/**
 * @brief       DIO_writePin                :   Function used to Write the value Logic High or Logic Low on the required pin
 *
 * @param[in]   port						:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin							:	pin name id should be	[PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 * @param[in]	value						:	pin value should be		[PIN_LOW,PIN_HIGH]
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 *				INVALID_PIN_ID				:	in case of wrong pin id
 *				INVALID_OPERATION			:	in case of wrong value
 */
enu_dio_error_t DIO_writePin		(uint8 port,uint8 pin,enu_pin_value_t value);

/**
 * @brief       DIO_readPin					:   Function used to Read and return the value for the required pin, it should be Logic High or Logic Low
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
enu_dio_error_t DIO_readPin		(uint8 port,uint8 pin,uint8* value);

/**
 * @brief       DIO_togglePin               :   Function used to toggle the logic of the required pin
 *
 * @param[in]   port						:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   pin							:	pin name id should be	[PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,PIN4_ID,PIN5_ID,PIN6_ID,PIN7_ID]
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 *				INVALID_PIN_ID				:	in case of wrong pin id
 */
enu_dio_error_t DIO_togglePin	(uint8 port,uint8 pin);

/**
 * @brief       DIO_portMode                :   Function used to Setup the direction of the required port input/output
 *
 * @param[in]   port						:	port name id should be		[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]   direction					:	port direction should be	[PORT_INPUT,PORT_OUTPUT]
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 *				INVALID_DIRECTION			:	in case of wrong direction
 */
enu_dio_error_t DIO_portMode		(uint8 port,enu_port_direction_t direction);

/**
 * @brief       DIO_writePort               :   Function used to Write the value Logic High or Logic Low on the required port
 *
 * @param[in]   port						:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[in]	value						:	pin value should be		[PORT_INPUT,PORT_OUTPUT]
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 *				INVALID_OPERATION			:	in case of wrong value
 */
enu_dio_error_t DIO_writePort	(uint8 port,enu_port_value_t enu_port_value);

/**
 * @brief       DIO_readPort				:   Function used to Read and return the value for the required port
 *
 * @param[in]   port						:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 * @param[out]	value						:	the value of the required pin
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 *				INVALID_OPERATION			:	in case of passing NULL pointer
 */
enu_dio_error_t DIO_readPort		(uint8 port,uint8* value);

/**
 * @brief       DIO_togglePort              :   Function used to toggle the logic of the required port
 *
 * @param[in]   port						:	port name id should be	[PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID]
 *
 * @return      VALID_OPERATION				:   in case of successful operation
 *              INVALID_PORT_ID 			:   in case of wrong port id
 */
enu_dio_error_t DIO_togglePort	(uint8 port);


#endif /* MCAL_GPIO_GPIO_H_ */
