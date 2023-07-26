/*
 * led.c
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

/*============= FILE INCLUSION =============*/
#include "led.h"

/*============= FUNCTION DEFINITIONS =============*/

enu_led_error_t led_init(uint8 u8_port,uint8 u8_pin)
{
	enu_led_error_t enu_led_error = LED_VALID_OPERATION;
	enu_led_error = (enu_led_error_t) DIO_pinMode(u8_port,u8_pin,PIN_OUTPUT);
	if(enu_led_error == LED_VALID_OPERATION)
	{
		enu_led_error = DIO_writePin(u8_port,u8_pin,PIN_LOW);
	}
	return enu_led_error;
}

/*===========================================================================*/

enu_led_error_t led_write(uint8 u8_port,uint8 u8_pin,enu_pin_value_t enu_led_state)
{
	enu_led_error_t enu_led_error = LED_VALID_OPERATION;

	enu_led_error = (enu_led_error_t) DIO_writePin(u8_port,u8_pin,enu_led_state);

	return enu_led_error;
}

/*===========================================================================*/

enu_led_error_t led_toggle(uint8 u8_port,uint8 u8_pin)
{
	enu_led_error_t enu_led_error = LED_VALID_OPERATION;

	enu_led_error = (enu_led_error_t) DIO_togglePin(u8_port,u8_pin);

	return enu_led_error;
}
