/*
 * dc_motor.h
 *
 * Created: 2023-07-26 9:30:34 PM
 *  Author: HAZEM-PC
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*=========FILE INCLUSION=========*/
#include "..\..\MCAL\DIO\gpio.h"
#include "..\PWM\pwm.h"

/*=========MACRO DEFINITIONS=========*/
#define PWM_ID				0	//configuration parameter for the timer id used with PWM module, it should be [0-1-2]
#define PWM_PERIODIC_TIME	4	//configuration parameter to determine the periodic time of the generated PWM signal- defined in millisecond
/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	ENU_DCMOTOR_CW		= 0	,
	ENU_DCMOTOR_ACW			,
	ENU_DCMOTOR_MAX_STATE
	}enu_dcMotor_state_t;

typedef enum{
	ENU_DCMOTOR_INVALID_OPERA	= 0 ,
	ENU_DCMOTOR_VALID_OPERA
	}enu_dcMotor_error_t;

typedef struct{
	uint8 port_id;
	uint8 pin_id;
}str_dcMotor_terminal_t;

typedef struct{
	str_dcMotor_terminal_t positive_terminal;
	str_dcMotor_terminal_t negative_terminal;
	str_dcMotor_terminal_t enable_terminal;
	}str_dcMotor_config_t;
	
/*=========APIs DECLERATIONS=========*/

/**
 * @brief       dcMotor_init        		: Function used to initialize the motor pin connections 
 * 
 * @param[in]   str_dcMotor_config			: the motor configuration type, act as motor id
 *
 * @return      ENU_DCMOTOR_VALID_OPERA		: in case of successful operation     
 *				ENU_DCMOTOR_INVALID_OPERA	: in case of wrong value       
 */
enu_dcMotor_error_t dcMotor_init (str_dcMotor_config_t* str_dcMotor_config);

/**
 * @brief       dcMotor_rotate        		: Function used to control motor rotation direction and the rotation speed 
 * 
 * @param[in]   str_dcMotor_config			: the motor configuration type, act as motor id
 * @param[in]   enu_dcMotor_state			: the motor rotate direction [CW-Anti_CW]
 * @param[in]	u8_dcMotor_speed			: the motor speed percentage [0---100 %]
 *
 * @return      ENU_DCMOTOR_VALID_OPERA		: in case of successful operation     
 *				ENU_DCMOTOR_INVALID_OPERA	: in case of wrong value       
 */
enu_dcMotor_error_t dcMotor_rotate (str_dcMotor_config_t* str_dcMotor_config,enu_dcMotor_state_t enu_dcMotor_state,uint8 u8_dcMotor_speed);


/**
 * @brief       dcMotor_stop        		: Function used to stop the motor 
 * 
 * @param[in]   str_dcMotor_config			: the motor configuration type, act as motor id
 *
 * @return      ENU_DCMOTOR_VALID_OPERA		: in case of successful operation     
 *				ENU_DCMOTOR_INVALID_OPERA	: in case of wrong value       
 */
enu_dcMotor_error_t dcMotor_stop (str_dcMotor_config_t* str_dcMotor_config);


#endif /* DC_MOTOR_H_ */