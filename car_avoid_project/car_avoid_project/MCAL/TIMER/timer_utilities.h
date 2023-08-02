/*
 * timer_utilities.h
 *
 * Created: 2023-07-29 3:09:21 AM
 *  Author: HAZEM-PC
 */ 


#ifndef TIMER_UTILITIES_H_
#define TIMER_UTILITIES_H_

/*============= FILE INCLUSION =============*/
#include "timer_interface.h"

/*============= MACRO DEFINITION =============*/
#define P_0					0
#define P_1					1
#define P_8					8
#define P_32				32
#define P_64				64
#define P_128				128
#define P_256				256
#define P_1024				1024
#define NO_FIT_PRESCALER	2


#define MAX_TMR_8_BIT_COUNT		256
#define MAX_TMR_16_BIT_COUNT	65536
#define MIN_TMR_COUNT			1
#define INIT_VALUE(T_max,T_delay,tick)  (((float32)T_max-T_delay)/tick)
#define F_CPU 8000000UL

#define MAX_8_BIT_DELAY_SEC(prescaler)	((((float32)prescaler/F_CPU)*MAX_TMR_8_BIT_COUNT))
#define MAX_16_BIT_DELAY_SEC(prescaler) ((((float32)prescaler/F_CPU)*MAX_TMR_16_BIT_COUNT))
#define MAX_8_BIT_DELAY_MS(prescaler)	((((float32)prescaler/F_CPU)*MAX_TMR_8_BIT_COUNT)*1000UL)
#define MAX_16_BIT_DELAY_MS(prescaler)	((((float32)prescaler/F_CPU)*MAX_TMR_16_BIT_COUNT)*1000UL)
#define MAX_8_BIT_DELAY_US(prescaler)	((((float32)prescaler/F_CPU)*MAX_TMR_8_BIT_COUNT)*1000000UL)
#define MAX_16_BIT_DELAY_US(prescaler)	((((float32)prescaler/F_CPU)*MAX_TMR_16_BIT_COUNT)*1000000UL)
#define MIN_DELAY_SEC(prescaler)		((((float32)prescaler/F_CPU)*MIN_TMR_COUNT))
#define MIN_DELAY_MS(prescaler)			((((float32)prescaler/F_CPU)*MIN_TMR_COUNT)*1000UL)
#define MIN_DELAY_US(prescaler)			((((float32)prescaler/F_CPU)*MIN_TMR_COUNT)*1000000UL)

/*============= TYPE DEFINITION =============*/
typedef enum{
	ENU_MICRO_SECOND	= 0,
	ENU_MILLI_SECOND	= 1,
	ENU_SECOND			= 2,
	MAX_TIME_TAG		= 3
	}enu_time_unit_t;

/*============= FUNCTION DEFINITION =============*/

/**
 * @brief       calc_prescaler				: function used to notify the upper layer when interrupt happen
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   enu_time_unit				: the delay unit it should be [ENU_MICRO_SECOND,ENU_MILLI_SECOND,ENU_SECOND]
 * @param[in]   f32_delay					: the required delay
 * @param[out]  ptr_u8_prescale				: timer prescaler it should be [P_0 , P_1 , P_8 , P_16 , P_32 , P_64 , P_128 , P_256 , P_1024]
 *
 * @return      TRUE						: in case of invalid interrupt edge type
 *              FALSE 						: in case of invalid timer mode 
 */
BOOLEAN calc_prescaler(float32 f32_delay,enu_tmr_channel_id_t enu_tmr_channel_id,enu_time_unit_t enu_time_unit,uint16* ptr_u16_prescale);


/**
 * @brief       calc_initialValue			: function used to calculate the timer initial value
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   prescaler					: timer prescaler it should be [P_0 , P_1 , P_8 , P_16 , P_32 , P_64 , P_128 , P_256 , P_1024]
 * @param[in]   delay						: the required delay
 * @param[out]  init_value					: pointer to variable contain the value of initial value
 *
 * @return      TRUE						: in case of invalid interrupt edge type
 *              FALSE 						: in case of invalid timer mode 
 */
BOOLEAN calc_initialValue(enu_tmr_channel_id_t enu_tmr_channel_id,enu_time_unit_t enu_time_unit,uint16 prescaler,float32 delay,uint16* init_value);


#endif /* TIMER_UTILITIES_H_ */