/*
 * gpio.c
 *
 *  Created on: Jul 15, 2023
 *      Author: HAZEM-PC
 */

/*============= FILE INCLUSION =============*/
#include "gpio.h"

/*============= FUNCTION DEFINITIONS =============*/

enu_dio_error_t DIO_pinMode	(uint8 port,uint8 pin,enu_pin_direction_t enu_pin_direction)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
		if((pin >= PIN0_ID) && (pin < MAX_PIN_ID))
		{
			if((enu_pin_direction == PIN_INPUT) || (enu_pin_direction == PIN_OUTPUT))
			{
				switch(port)
				{
					case PORTA_ID:
					if(enu_pin_direction == PIN_OUTPUT)
					{
						SET_BIT(DDRA,pin);
					}
					else
					{
						CLEAR_BIT(DDRA,pin);
					}
					break;
					case PORTB_ID:
					if(enu_pin_direction == PIN_OUTPUT)
					{
						SET_BIT(DDRB,pin);
					}
					else
					{
						CLEAR_BIT(DDRB,pin);
					}
					break;
					case PORTC_ID:
					if(enu_pin_direction == PIN_OUTPUT)
					{
						SET_BIT(DDRC,pin);
					}
					else
					{
						CLEAR_BIT(DDRC,pin);
					}
					break;
					case PORTD_ID:
					if(enu_pin_direction == PIN_OUTPUT)
					{
						SET_BIT(DDRD,pin);
					}
					else
					{
						CLEAR_BIT(DDRD,pin);
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			else
			{
				enu_dio_error = DIO_INVALID_DIRECTION;
			}
		}
		else
		{
			enu_dio_error = DIO_INVALID_PIN_ID;
		}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}

/*===========================================================================*/

enu_dio_error_t DIO_writePin	(uint8 port,uint8 pin,enu_pin_value_t enu_pin_value)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
		if((pin >= PIN0_ID) && (pin < MAX_PIN_ID))
		{
			if((enu_pin_value == PIN_LOW) || (enu_pin_value == PIN_HIGH))
			{
				switch(port)
				{
					case PORTA_ID:
					if(enu_pin_value == LOGIC_HIGH)
					{
						SET_BIT(PORTA,pin);
					}
					else
					{
						CLEAR_BIT(PORTA,pin);
					}
					break;
					case PORTB_ID:
					if(enu_pin_value == LOGIC_HIGH)
					{
						SET_BIT(PORTB,pin);
					}
					else
					{
						CLEAR_BIT(PORTB,pin);
					}
					break;
					case PORTC_ID:
					if(enu_pin_value == LOGIC_HIGH)
					{
						SET_BIT(PORTC,pin);
					}
					else
					{
						CLEAR_BIT(PORTC,pin);
					}
					break;
					case PORTD_ID:
					if(enu_pin_value == LOGIC_HIGH)
					{
						SET_BIT(PORTD,pin);
					}
					else
					{
						CLEAR_BIT(PORTD,pin);
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			else
			{
				enu_dio_error = DIO_INVALID_OPERATION;
			}
		}
		else
		{
			enu_dio_error = DIO_INVALID_PIN_ID;
		}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}

/*===========================================================================*/

enu_dio_error_t DIO_readPin	(uint8 port,uint8 pin,uint8* pptr_value)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
		if((pin >= PIN0_ID) && (pin < MAX_PIN_ID))
		{
			if(pptr_value != NULL_PTR)
			{
				switch(port)
				{
					case PORTA_ID:
					if(BIT_IS_SET(PINA,pin))
					{
						*pptr_value = LOGIC_HIGH;
					}
					else
					{
						*pptr_value = LOGIC_LOW;
					}
					break;
					case PORTB_ID:
					if(BIT_IS_SET(PINB,pin))
					{
						*pptr_value = LOGIC_HIGH;
					}
					else
					{
						*pptr_value = LOGIC_LOW;
					}
					break;
					case PORTC_ID:
					if(BIT_IS_SET(PINC,pin))
					{
						*pptr_value = LOGIC_HIGH;
					}
					else
					{
						*pptr_value = LOGIC_LOW;
					}
					break;
					case PORTD_ID:
					if(BIT_IS_SET(PIND,pin))
					{
						*pptr_value = LOGIC_HIGH;
					}
					else
					{
						*pptr_value = LOGIC_LOW;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			else
			{
				enu_dio_error = DIO_INVALID_OPERATION;
			}
		}
		else
		{
			enu_dio_error = DIO_INVALID_PIN_ID;
		}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}

/*===========================================================================*/

enu_dio_error_t DIO_togglePin	(uint8 port,uint8 pin)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
		if((pin >= PIN0_ID) && (pin < MAX_PIN_ID))
		{
				switch(port)
				{
					case PORTA_ID:	TOGGLE_BIT(PORTA,pin);	break;
					case PORTB_ID:	TOGGLE_BIT(PORTB,pin);	break;
					case PORTC_ID:	TOGGLE_BIT(PORTC,pin);	break;
					case PORTD_ID:	TOGGLE_BIT(PORTD,pin);	break;
					default:
					{
						//do nothing
					}
					break;
				}
		}
		else
		{
			enu_dio_error = DIO_INVALID_PIN_ID;
		}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}

/*===========================================================================*/

enu_dio_error_t DIO_portMode	(uint8 port,enu_port_direction_t enu_port_direction)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
		if((enu_port_direction == PORT_INPUT) || (enu_port_direction == PORT_OUTPUT))
		{
			switch(port)
			{
				case PORTA_ID:	DDRA = enu_port_direction;	break;
				case PORTB_ID:	DDRB = enu_port_direction;	break;
				case PORTC_ID:	DDRC = enu_port_direction;	break;
				case PORTD_ID:	DDRD = enu_port_direction;	break;
				default:
					{
						//do nothing
					}
					break;
			}
		}
		else
		{
			enu_dio_error = DIO_INVALID_PORT_ID;
		}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}

/*===========================================================================*/

enu_dio_error_t DIO_writePort	(uint8 port,enu_port_value_t enu_port_value)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
			switch(port)
			{
				case PORTA_ID:	PORTA = enu_port_value;		break;
				case PORTB_ID:	PORTB = enu_port_value;		break;
				case PORTC_ID:	PORTC = enu_port_value;		break;
				case PORTD_ID:	PORTD = enu_port_value;		break;
				default:
					{
						//do nothing
					}
					break;
			}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}

/*===========================================================================*/

enu_dio_error_t DIO_readPort	(uint8 port,uint8* pptr_value)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
		if(pptr_value != NULL_PTR)
		{
			switch(port)
			{
				case PORTA_ID:	*pptr_value = PINA;	break;
				case PORTB_ID:	*pptr_value = PINB;	break;
				case PORTC_ID:	*pptr_value = PINC;	break;
				case PORTD_ID:	*pptr_value = PIND;	break;
				default:
				{
					//do nothing
				}
				break;
			}

		}
		else
		{
			enu_dio_error = DIO_INVALID_OPERATION;
		}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}

/*===========================================================================*/

enu_dio_error_t DIO_togglePort	(uint8 port)
{
	enu_dio_error_t enu_dio_error = DIO_VALID_OPERATION;
	if((port >= PORTA_ID) && (port < MAX_PORT_ID))
	{
		switch(port)
		{
			case PORTA_ID:	PORTA ^= PORT_HIGH;		break;
			case PORTB_ID:	PORTB ^= PORT_HIGH;		break;
			case PORTC_ID:	PORTC ^= PORT_HIGH;		break;
			case PORTD_ID:	PORTD ^= PORT_HIGH;		break;
			default:
			{
				//do nothing
			}
			break;
		}
	}
	else
	{
		enu_dio_error = DIO_INVALID_PORT_ID;
	}
	return enu_dio_error;
}
