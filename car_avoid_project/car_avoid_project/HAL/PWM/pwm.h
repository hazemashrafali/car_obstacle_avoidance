#ifndef PWM_H_
#define PWM_H_

/*=========FILE INCLUSION=========*/
#include "..\..\MCAL\TIMER\timer_interface.h"
#include "..\..\MCAL\TIMER\timer_utilities.h"
#include "..\..\MCAL\DIO\gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	ENU_PWM_INVALID_OPERATION	= 0,
	ENU_PWM_VALID_OPERATION		  
}enu_pwm_error_t;

/*=========APIs DECLERATIONS=========*/

/**
 * @brief       PWM_Init        		: Function used to initialize PWM module  
 * 
 * @param[in]   u8_pwm_port_id			: port name ID should be 
 * @param[in]   u8_pwm_pin_id			: pin name ID should be	 
 * @param[in]	u8_pwm_timer_id			: Timer ID should be
 *
 * @return      ENU_PWM_VALID_OPERATION		: in case of successful operation     
 *				ENU_PWM_INVALID_OPERATION	:	in case of wrong value       
 */
enu_pwm_error_t PWM_Init(uint8 u8_pwm_port_id,uint8 u8_pwm_pin_id,uint8 u8_pwm_timer_id);


/**
 * @brief       PWM_start        		: Function used to start generate PWM signal  
 * 
 * @param[in]   u8_pwm_timer_id			: port name ID should be
 * @param[in]   u32_periodic_time		: PWM periodic time
 * @param[in]	u8_tick_unit			: time unit it should be [USEC,MSEC,SEC]
 * @param[in]   u8_duty_cycle			: PWM duty cycle percentage it should be [0%--100%]
 * @return      ENU_PWM_VALID_OPERATION		: in case of successful operation     
 *				ENU_PWM_INVALID_OPERATION	:in case of wrong value       
 */
enu_pwm_error_t PWM_start(uint8 u8_pwm_timer_id,uint32 u32_periodic_time,uint8 u8_duty_cycle);
/**
 * @brief       PWM_stop        			: Function used to stop generate PWM signal  
 * 
 * @param[in]	u8_pwm_timer_id				: Timer ID should be

 * @return      ENU_PWM_VALID_OPERATION		: in case of successful operation
 *				ENU_PWM_INVALID_OPERATION	: in case of wrong value      
 */
enu_pwm_error_t PWM_stop(uint8 u8_pwm_timer_id);

#endif	/* PWM_H_ */


