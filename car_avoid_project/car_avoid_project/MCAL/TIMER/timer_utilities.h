/*
 * timer_utilities.h
 *
 * Created: 2023-07-29 3:09:21 AM
 *  Author: HAZEM-PC
 */ 


#ifndef TIMER_UTILITIES_H_
#define TIMER_UTILITIES_H_

/*============= FILE INCLUSION =============*/


/*============= MACRO DEFINITION =============*/

#define MAX_TMR_8_BIT_COUNT		256
#define MAX_TMR_16_BIT_COUNT	65535
#define MIN_TMR_COUNT			1
#define INIT_VALUE(T_max,T_delay,tick)  (((float32)T_max-T_delay)/tick)
#define MAX_DELAY_MS(prescaler)			((((float32)prescaler/F_CPU)*MAX_COUNT)*1000UL)
#define MIN_DELAY_MS(prescaler)			((((float32)prescaler/F_CPU)*MIN_COUNT)*1000UL)
#define MAX_DELAY_US(prescaler)			((((float32)prescaler/F_CPU)*MAX_COUNT)*1000000UL)
#define MIN_DELAY_US(prescaler)			((((float32)prescaler/F_CPU)*MIN_COUNT)*1000000UL)




#endif /* TIMER_UTILITIES_H_ */