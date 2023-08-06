/*
 * button.c
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

/*============= FILE INCLUSION =============*/
#include "button.h"
#include "util/delay.h"

/*============= FUNCTION DEFINITIONS =============*/

enu_button_error_t button_init(uint8 port,uint8 pin)
{
	enu_button_error_t enu_button_error = BTN_VALID_OPERATION;
	enu_button_error = (enu_button_error_t) DIO_pinMode(port,pin,PIN_INPUT);
	return enu_button_error;
}


enu_button_error_t button_enable_pullup (uint8 port,uint8 pin)
{
	enu_button_error_t enu_button_error = BTN_VALID_OPERATION;
	enu_button_error = (enu_button_error_t) DIO_writePin(port,pin,PIN_HIGH);
	return enu_button_error;
}


enu_button_error_t button_read(uint8 port,uint8 pin,uint8* value)
{
	enu_button_error_t enu_button_error = BTN_VALID_OPERATION;
	uint8 u8_l_value = LOGIC_LOW;
	if(value != NULL_PTR)
	{
		enu_button_error = (enu_button_error_t) DIO_readPin(port,pin,&u8_l_value);
		if(u8_l_value == LOGIC_HIGH)
		{
			*value = LOGIC_HIGH;
		}
		else
		{
			*value = LOGIC_LOW;
		}
	}
	else
	{
		enu_button_error = BTN_INVALID_OPERATION;
	}
	return enu_button_error;
}
