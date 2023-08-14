/*
 * dc_motor.c
 *
 * Created: 2023-07-26 9:30:48 PM
 *  Author: HAZEM-PC
 */ 
/*=========FILE INCLUSION=========*/
#include "dc_motor.h"

/*=========MACRO DEFINITIONS=========*/
#define	VALID			1
#define	INVALID			0
#define MAX_MOTOR_SPEED	100
/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

	
/*=========APIs DECLERATIONS=========*/

/**
 * @brief       dcMotor_init        		: Function used to initialize the motor pin connections      
 */

enu_dcMotor_error_t dcMotor_init (str_dcMotor_config_t* str_dcMotor_config)
{
	enu_dcMotor_error_t enu_dcMotor_error = ENU_DCMOTOR_VALID_OPERA;
	uint8 u8_l_returnValue = ZERO_VALUE;
	if(str_dcMotor_config != NULL_PTR)
	{
		u8_l_returnValue = DIO_pinMode(str_dcMotor_config->positive_terminal.port_id, str_dcMotor_config->positive_terminal.pin_id, PIN_OUTPUT);
		if(u8_l_returnValue == VALID)
		{
			u8_l_returnValue = DIO_pinMode(str_dcMotor_config->negative_terminal.port_id, str_dcMotor_config->negative_terminal.pin_id, PIN_OUTPUT);
			if(u8_l_returnValue == VALID)
			{
				u8_l_returnValue = PWM_Init(str_dcMotor_config->enable_terminal.port_id, str_dcMotor_config->enable_terminal.pin_id,PWM_TIMER_ID);
				if(u8_l_returnValue == VALID)
				{
					DIO_writePin(str_dcMotor_config->positive_terminal.port_id, str_dcMotor_config->positive_terminal.pin_id, PIN_LOW);
					DIO_writePin(str_dcMotor_config->negative_terminal.port_id, str_dcMotor_config->negative_terminal.pin_id, PIN_LOW);
				}					
			}
			else
			{
				enu_dcMotor_error = ENU_DCMOTOR_INVALID_OPERA;
			}
		}
		else
		{
			enu_dcMotor_error = ENU_DCMOTOR_INVALID_OPERA;
		}
	}
	else
	{
		enu_dcMotor_error = ENU_DCMOTOR_INVALID_OPERA;
	}
	return enu_dcMotor_error;
}

/**
 * @brief       dcMotor_rotate        		: Function used to control motor rotation direction and the rotation speed    
 */
enu_dcMotor_error_t dcMotor_rotate (str_dcMotor_config_t* str_dcMotor_config,enu_dcMotor_state_t enu_dcMotor_state,uint8 u8_dcMotor_speed)
{
	enu_dcMotor_error_t enu_dcMotor_error = ENU_DCMOTOR_VALID_OPERA;
	if((str_dcMotor_config != NULL_PTR) && (enu_dcMotor_state < ENU_DCMOTOR_MAX_STATE) && (u8_dcMotor_speed <= MAX_MOTOR_SPEED))
	{
		PWM_start(PWM_TIMER_ID,PWM_PERIODIC_TIME,u8_dcMotor_speed);
		if(enu_dcMotor_state == ENU_DCMOTOR_CW)
		{
			DIO_writePin(str_dcMotor_config->positive_terminal.port_id, str_dcMotor_config->positive_terminal.pin_id, PIN_HIGH);
			DIO_writePin(str_dcMotor_config->negative_terminal.port_id, str_dcMotor_config->negative_terminal.pin_id, PIN_LOW);
		}
		else if(enu_dcMotor_state == ENU_DCMOTOR_ACW)
		{
			DIO_writePin(str_dcMotor_config->positive_terminal.port_id, str_dcMotor_config->positive_terminal.pin_id, PIN_LOW);
			DIO_writePin(str_dcMotor_config->negative_terminal.port_id, str_dcMotor_config->negative_terminal.pin_id, PIN_HIGH);
		}
		else if(enu_dcMotor_state == ENU_DCMOTOR_BREAK)
		{
			DIO_writePin(str_dcMotor_config->positive_terminal.port_id, str_dcMotor_config->positive_terminal.pin_id, PIN_LOW);
			DIO_writePin(str_dcMotor_config->negative_terminal.port_id, str_dcMotor_config->negative_terminal.pin_id, PIN_LOW);
		}
		else
		{
			//do nothing
		}
	}
	else
	{
		enu_dcMotor_error = ENU_DCMOTOR_INVALID_OPERA;
	}
	return enu_dcMotor_error;
}

/**
 * @brief       dcMotor_stop        		: Function used to stop the motor  
 */
enu_dcMotor_error_t dcMotor_stop (str_dcMotor_config_t* str_dcMotor_config)
{
	enu_dcMotor_error_t enu_dcMotor_error = ENU_DCMOTOR_VALID_OPERA;
	if(str_dcMotor_config != NULL_PTR)
	{
		//PWM_stop(PWM_TIMER_ID);
		DIO_writePin(str_dcMotor_config->positive_terminal.port_id, str_dcMotor_config->positive_terminal.pin_id, PIN_LOW);
		DIO_writePin(str_dcMotor_config->negative_terminal.port_id, str_dcMotor_config->negative_terminal.pin_id, PIN_LOW);
	}
	else
	{
		enu_dcMotor_error = ENU_DCMOTOR_INVALID_OPERA;
	}
	return enu_dcMotor_error;
}
