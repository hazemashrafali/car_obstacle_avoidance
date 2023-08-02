/*
 * icu.c
 *
 * Created: 2023-07-26 9:31:00 PM
 *  Author: HAZEM-PC
 */ 
/*===============FILE ENCLUTION ================*/
#include "icu.h"

/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/
#define INTERRUPT_CHANNEL_0		0
#define INTERRUPT_CHANNEL_1		1
#define INTERRUPT_CHANNEL_2		2
#define MAX_INTERRUPT_CHANNEL	3
#define TIMER_CHANNEL_0			0
#define TIMER_CHANNEL_1			1
#define TIMER_CHANNEL_2			2
#define MAX_TIMER_CHANNEL		3
/*===============TYBS DEFINTION ================*/


/*===============GLOBAL VARIBALS ================*/
uint8 gl_u8_interrupt_id	= MAX_INTERRUPT_CHANNEL ;
uint8 gl_u8_timer_id		= MAX_TIMER_CHANNEL;

/*=========================APIS=========================*/

/**
 * @brief       Icu_init					: function used to initialize interrupt id , interrupt edge type , timer id and timer clock
 *
 * @param[in]   Config_Ptr					: pointer to structure of type str_icu_configtype_t	
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_init(const str_icu_configtype_t * str_icu_configtype)
{	
	enu_intrrupt_id_t	enu_intrrupt_id		= ENU_MAX_INT_ID;
	enu_trigger_mode_t	enu_trigger_mode	= ENU_MAX_TRIGGER_MODE;
	enu_icu_error_t		enu_icu_error		= ENU_ICU_VALID;
	str_tmr_config_t	str_tmr_config;
	if((str_icu_configtype->enu_icu_clock >= ENU_ICU_NO_CLOCK) && ( str_icu_configtype->enu_icu_clock < ENU_ICU_MAX_CLOCK))
	{
		if((str_icu_configtype->enu_icu_edgetype >= ENU_ICU_RISING) && (str_icu_configtype->enu_icu_edgetype < ENU_ICU_MAX_EDGETYPE))
		{
			if ((str_icu_configtype->enu_icu_channel_id >= ENU_ICU_CHANNEL_ID0) && (str_icu_configtype->enu_icu_channel_id < ENU_ICU_MAX_CHANNEL))
			{
				if ((str_icu_configtype->enu_timer_channel_id >= ENU_TIMER_CHANNEL_ID0) && (str_icu_configtype->enu_timer_channel_id < ENU_TIMER_MAX_CHANNEL))
				{
					if (str_icu_configtype->enu_icu_channel_id == ENU_ICU_CHANNEL_ID0)
					{
						enu_intrrupt_id = ENU_INT0_ID;
						gl_u8_interrupt_id =INTERRUPT_CHANNEL_0;
					}
					else if (str_icu_configtype->enu_icu_channel_id == ENU_ICU_CHANNEL_ID1)
					{
						enu_intrrupt_id = ENU_INT1_ID;
						gl_u8_interrupt_id =INTERRUPT_CHANNEL_1 ;
					} 
					else
					{
						enu_intrrupt_id = ENU_INT2_ID;
						gl_u8_interrupt_id =INTERRUPT_CHANNEL_2 ;
					}
					if(str_icu_configtype->enu_icu_edgetype == ENU_ICU_FALLING )
					{
						enu_trigger_mode = ENU_FALLING;
					}
					else
					{
						enu_trigger_mode = ENU_RISING;
					}
					//to do initialize timer and set global timer channel id
					str_tmr_config.enu_tmr_channel_id = str_icu_configtype->enu_timer_channel_id;
					str_tmr_config.enu_tmr_mode	= ENU_TMR_NORMAL_MODE;
					str_tmr_config.enu_tmr_cmp_mode = ENU_TMR_CMP_DISCONNECT;
					str_tmr_config.enu_tmr_clk = str_icu_configtype->enu_icu_clock; // review
					str_tmr_config.enu_tmr_interrupt_state = ENU_TMR_INT_DISABLE;
					str_tmr_config.u16_tmr_compare_value = ZERO_VALUE;
					str_tmr_config.u16_tmr_initial_value = ZERO_VALUE;
					gl_u8_timer_id = str_icu_configtype->enu_timer_channel_id;
					timer_init(&str_tmr_config);
					Init_external_interrupt (enu_intrrupt_id,enu_trigger_mode);
					timer_start(str_icu_configtype->enu_timer_channel_id);
					enable_external_interrupt(enu_intrrupt_id);
				}
				else
				{
					enu_icu_error = ENU_TIMER_MAX_CHANNEL;
				}
			}
			else
			{
				enu_icu_error = ENU_ICU_MAX_CHANNEL;
			}
		}
		else
		{
			enu_icu_error = ENU_ICU_INVALID_EDGETYP;
		}
	}
	else
	{
		enu_icu_error = ENU_ICU_INVALID_CLOCK;
	}
	return enu_icu_error;
}

/**
 * @brief       Icu_setCallBack				: function used to set ICU callback function
 *
 * @param[in]   a_ptr						: pointer to function take void and return void
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_setCallBack(void(*a_ptr)(void))
{ 
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if (gl_u8_interrupt_id == INTERRUPT_CHANNEL_0)
	{
		interrupt0_set_callback (a_ptr);
	}
	else if (gl_u8_interrupt_id == INTERRUPT_CHANNEL_1)
	{
		interrupt1_set_callback (a_ptr);
	}
	else if (gl_u8_interrupt_id == INTERRUPT_CHANNEL_2)
	{
		interrupt2_set_callback (a_ptr);
	}
	else
	{
		enu_icu_error = ENU_ICU_INVALID_CHANNEL;
	}
	return enu_icu_error;
	
}

/**
 * @brief       Icu_setEdgeDetectionType	: function used to set/change ICU edge detection type 
 *
 * @param[in]   enu_icu_edgetype			: `ICU edge type it should be [ENU_ICU_FALLING,ENU_ICU_RISING] 
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_setEdgeDetectionType(const enu_icu_edgetype_t enu_icu_edgetype)
{
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if ((enu_icu_edgetype >= ENU_ICU_FALLING) &&(enu_icu_edgetype < ENU_ICU_MAX_EDGETYPE))
	{
		if((gl_u8_interrupt_id < MAX_INTERRUPT_CHANNEL))
		{
			if (enu_icu_edgetype == ENU_ICU_FALLING)
			{
				Init_external_interrupt(gl_u8_interrupt_id,ENU_FALLING);
			}
			else
			{
				Init_external_interrupt(gl_u8_interrupt_id,ENU_RISING);
			}	
		}
		else
		{
			enu_icu_error = ENU_ICU_INVALID_INPUT;
		}
	}
	else
	{
		enu_icu_error = ENU_ICU_INVALID_EDGETYP ;
	}
	return enu_icu_error;
}

/**
 * @brief       Icu_getTimerValue			: function used to read timer value
 *
 * @param[in]   u16_timer_value				: pointer to uint16 used to hold timer value
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_getTimerValue(uint16* u16_timer_value)
{
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if(u16_timer_value != NULL_PTR)
	{
		if(gl_u8_interrupt_id < MAX_TIMER_CHANNEL)
		{
			if(gl_u8_interrupt_id == TIMER_CHANNEL_0)
			{
				//to do read timer0 value
				timer_getValue(ENU_TMR_CHANNEL_0,u16_timer_value);
			}
			else if(gl_u8_interrupt_id == TIMER_CHANNEL_1)
			{
				//to do read timer1 value
				timer_getValue(ENU_TMR_CHANNEL_1,u16_timer_value);
			}
			else
			{
				//to do read timer2 value
				timer_getValue(ENU_TMR_CHANNEL_2,u16_timer_value);			
			}
		}
		else
		{
			enu_icu_error = ENU_ICU_INVALID_CHANNEL;
		}
	} 
	else
	{
		enu_icu_error = ENU_ICU_INVALID_INPUT;
	}
	return enu_icu_error;
}

/**
 * @brief       Icu_clearTimerValue			: function used to clear timer value
 *
 * @param[in]   void						:
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_clearTimerValue(void)
{
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if(gl_u8_interrupt_id < MAX_TIMER_CHANNEL)
	{
		if(gl_u8_interrupt_id == TIMER_CHANNEL_0)
		{
			//to do clear timer0 value
			timer_stop(ENU_TMR_CHANNEL_0);
			timer_setInitialValue(ENU_TMR_CHANNEL_0,ZERO_VALUE);
			timer_start(ENU_TMR_CHANNEL_0);
		}
		else if(gl_u8_interrupt_id == TIMER_CHANNEL_1)
		{
			//to do clear timer1 value
			timer_stop(ENU_TMR_CHANNEL_1);
			timer_setInitialValue(ENU_TMR_CHANNEL_1,ZERO_VALUE);
			timer_start(ENU_TMR_CHANNEL_1);
		}
		else
		{
			//to do clear timer2 value
			timer_stop(ENU_TMR_CHANNEL_2);
			timer_setInitialValue(ENU_TMR_CHANNEL_2,ZERO_VALUE);
			timer_start(ENU_TMR_CHANNEL_2);
		}
	}
	else
	{
		enu_icu_error = ENU_ICU_INVALID_CHANNEL;
	}
	return enu_icu_error;
}

/**
 * @brief       Icu_DeInit					: function used to de_initialize the ICU
 *
 * @param[in]   void						:
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
void Icu_DeInit(void)
{
	disable_external_interrupt(gl_u8_interrupt_id);
	timer_deInit(gl_u8_timer_id);
	// to do disable timer and back to initial state	
}