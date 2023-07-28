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
#define INTERRUPT_CHANNEL_0			0
#define INTERRUPT_CHANNEL_1			1
#define INTERRUPT_CHANNEL_2			2
#define MAX_INTERRUPT_CHANNEL		3
#define  TIMER_CHANNEL_0	0
#define  TIMER_CHANNEL_1	1
#define  TIMER_CHANNEL_2	2
#define  MAX_TIMER_CHANNEL	3
/*===============TYBS DEFINTION ================*/

/*===============GLOBAL VARIBALS ================*/
uint8 gl_interrupt_id	= MAX_INTERRUPT_CHANNEL ;
uint8 gl_timer_id		= MAX_TIMER_CHANNEL;
/*=========================APIS=========================*/
/**
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_init(const enu_icu_configtype_t * Config_Ptr)
{	
	enu_intrrupt_id_t enu_intrrupt_id = ENU_MAX_INT_ID;
	enu_trigger_mode_t enu_trigger_mode = ENU_MAX_TRIGGER_MODE;
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if((Config_Ptr->enu_icu_clock >= ENU_ICU_NO_CLOCK) && ( Config_Ptr->enu_icu_clock < ENU_ICU_MAX_CLOCK))
	{
		if((Config_Ptr->enu_icu_edgetype >= ENU_ICU_RISING) && (Config_Ptr->enu_icu_edgetype < ENU_ICU_MAX_EDGETYP))
		{
			if ((Config_Ptr->enu_icu_channel_id >= ENU_ICU_CHANNEL_ID0) && (Config_Ptr->enu_icu_channel_id < ENU_ICU_MAX_CHANNEL))
			{
				if ((Config_Ptr->enu_timer_channel_id >= ENU_TIMER_CHANNEL_ID0) && (Config_Ptr->enu_timer_channel_id < ENU_TIMER_MAX_CHANNEL))
				{
					if (Config_Ptr->enu_icu_channel_id == ENU_ICU_CHANNEL_ID0)
					{
						enu_intrrupt_id = ENU_INT0_ID;
						gl_interrupt_id =INTERRUPT_CHANNEL_0;
					}
					else if (Config_Ptr->enu_icu_channel_id == ENU_ICU_CHANNEL_ID1)
					{
						enu_intrrupt_id = ENU_INT1_ID;
						gl_interrupt_id =INTERRUPT_CHANNEL_1 ;
					} 
					else
					{
						enu_intrrupt_id = ENU_INT2_ID;
						gl_interrupt_id =INTERRUPT_CHANNEL_2 ;
					}
					if(Config_Ptr->enu_icu_edgetype == ENU_ICU_FALLING )
					{
						enu_trigger_mode = ENU_FALLING;
					}
					else
					{
						enu_trigger_mode = ENU_RISING;
					}
					//to do initialize timer and set global timer channel id
					
					Init_external_interrupt (enu_intrrupt_id,enu_trigger_mode);
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

enu_icu_error_t Icu_setCallBack(void(*a_ptr)(void))
{ 
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if (gl_interrupt_id == INTERRUPT_CHANNEL_0)
	{
		interrupt0_set_callback (a_ptr);
	}
	else if (gl_interrupt_id == INTERRUPT_CHANNEL_1)
	{
		interrupt1_set_callback (a_ptr);
	}
	else if (gl_interrupt_id == INTERRUPT_CHANNEL_2)
	{
		interrupt2_set_callback (a_ptr);
	}
	else
	{
		enu_icu_error = ENU_ICU_INVALID_CHANNEL;
	}
	return enu_icu_error;
	
}

enu_icu_error_t Icu_setEdgeDetectionType(const enu_icu_edgetype_t enu_icu_edgetype)
{
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if ((enu_icu_edgetype >= ENU_ICU_FALLING) &&(enu_icu_edgetype < ENU_ICU_MAX_EDGETYP))
	{
		if((gl_interrupt_id < MAX_INTERRUPT_CHANNEL))
		{
			if (enu_icu_edgetype == ENU_ICU_FALLING)
			{
				Init_external_interrupt(gl_interrupt_id,ENU_FALLING);
			}
			else
			{
				Init_external_interrupt(gl_interrupt_id,ENU_RISING);
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
 * @brief       Icu_getInputCaptureValue    :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_getTimerValue(uint16* u16_timer_value)
{
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if(u16_timer_value != NULL_PTR)
	{
		if(gl_timer_id < MAX_TIMER_CHANNEL)
		{
			if(gl_timer_id == TIMER_CHANNEL_0)
			{
				//to do read timer0 value 
			}
			else if(gl_timer_id == TIMER_CHANNEL_1)
			{
				//to do read timer1 value
			}
			else
			{
				//to do read timer2 value				
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
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_clearTimerValue(void)
{
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	if(gl_timer_id < MAX_TIMER_CHANNEL)
	{
		if(gl_timer_id == TIMER_CHANNEL_0)
		{
			//to do clear timer0 value
		}
		else if(gl_timer_id == TIMER_CHANNEL_1)
		{
			//to do clear timer1 value
		}
		else
		{
			//to do clear timer2 value
		}
	}
	else
	{
		enu_icu_error = ENU_ICU_INVALID_CHANNEL;
	}
	return enu_icu_error;
}
/**
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
void Icu_DeInit(void)
{
	disable_external_interrupt(gl_interrupt_id);
	// to do disable timer and back to free state	
}