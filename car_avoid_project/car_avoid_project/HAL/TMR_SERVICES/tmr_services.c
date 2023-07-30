/*
 * tmr_services.c
 *
 * Created: 2023-07-30 2:01:24 AM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "tmr_services.h"

/*============= TYPE DEFINITION =============*/

/*===============MACROS DEFINTION ================*/

/*===============GLOBAL VARIBALS ================*/

/*============= FUNCTION PROTOTYPE =============*/
enu_time_error_t delay_us	(uint8 u8_timer_id,uint32 u32_time_delay)
{
	enu_time_error_t enu_time_error = ENU_TIMER_VALID;
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}
enu_time_error_t delay_ms	(uint8 u8_timer_id,uint32 u32_time_delay);
enu_time_error_t delay_sec	(uint8 u8_timer_id,uint32 u32_time_delay);
enu_time_error_t timeOut_us	(uint8 u8_timer_id,uint32 u32_time_delay);
enu_time_error_t timeOut_ms	(uint8 u8_timer_id,uint32 u32_time_delay);
enu_time_error_t timeOut_sec(uint8 u8_timer_id,uint32 u32_time_delay);
enu_time_error_t timer_callEvent_us (uint8 u8_timer_id,uint32 u32_time_delay,void(*f_ptr)(void));
enu_time_error_t timer_callEvent_ms (uint8 u8_timer_id,uint32 u32_time_delay,void(*f_ptr)(void));
enu_time_error_t timer_callEvent_sec(uint8 u8_timer_id,uint32 u32_time_delay,void(*f_ptr)(void));