/*
 * tmr_services.h
 *
 * Created: 2023-07-30 2:01:16 AM
 *  Author: HAZEM-PC
 */ 


#ifndef TMR_SERVICES_H_
#define TMR_SERVICES_H_

/*============= FILE INCLUSION =============*/
#include "../../MCAL/TIMER/timer_interface.h"

/*============= TYPE DEFINITION =============*/
typedef enum{
	ENU_TIMER_INVALID_ID	= 0,
	ENU_TIMER_INVALID_DELAY	= 1,
	ENU_TIMER_INVALID_INPUT	= 2,
	ENU_TIMER_VALID			= 3,
	ENU_TIMER_MAX_ERROR		= 4
	}enu_time_error_t;
/*===============MACROS DEFINTION ================*/
#define MAX_TIMER_ID	3

/*===============GLOBAL VARIBALS ================*/

/*============= FUNCTION PROTOTYPE =============*/
enu_time_error_t delay_us	(uint8 u8_timer_id,float32 u32_time_delay);
enu_time_error_t delay_ms	(uint8 u8_timer_id,float32 f32_time_delay);
enu_time_error_t delay_sec	(uint8 u8_timer_id,float32 f32_time_delay);
enu_time_error_t timeOut_us	(uint8 u8_timer_id,float32 f32_time_delay);
enu_time_error_t timeOut_ms	(uint8 u8_timer_id,float32 f32_time_delay);
enu_time_error_t timeOut_sec(uint8 u8_timer_id,float32 f32_time_delay);
enu_time_error_t timer_callEvent_ms (uint8 u8_timer_id,float32 f32_time_delay,void(*f_ptr)(void));
enu_time_error_t timer_check_time_out_flag (uint8 u8_timer_id,uint8* ptr_u8_flag);

#endif /* TMR_SERVICES_H_ */