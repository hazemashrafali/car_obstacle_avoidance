/*
 * timer_utilities.c
 *
 * Created: 2023-07-30 3:10:41 AM
 *  Author: HAZEM-PC
 */ 

/*===============FILE ENCLUTION ================*/
#include "timer_utilities.h"

/*===============GLOBAL PRIVATE VARIBALS ================*/

/*============= PRIVATE FUNCTIONS =============*/

/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/

/*===============TYBS DEFINTION ================*/

/*===============FUNCTION DEFINITIONS ================*/

/**
 * @brief       calc_prescaler				: function used to notify the upper layer when interrupt happen
 */
BOOLEAN calc_prescaler(float32 f32_delay,enu_tmr_channel_id_t enu_tmr_channel_id,enu_time_unit_t enu_time_unit,uint16* ptr_u16_prescale)
{
	BOOLEAN bo_return_value = TRUE;
	if(enu_time_unit == ENU_MICRO_SECOND)
	{
		if(enu_tmr_channel_id == ENU_TMR_CHANNEL_0)
		{
			if(f32_delay <= MAX_8_BIT_DELAY_US(P_1024) )
			{
				if(f32_delay <= MAX_8_BIT_DELAY_US(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;	
			}
		}
		else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_1)
		{
			if(f32_delay <= MAX_16_BIT_DELAY_US(P_1024) )
			{
				if(f32_delay <= MAX_16_BIT_DELAY_US(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_16_BIT_DELAY_US(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_16_BIT_DELAY_US(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_16_BIT_DELAY_US(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <= MAX_16_BIT_DELAY_US(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_2)
		{
			if(f32_delay <= MAX_8_BIT_DELAY_US(P_1024) )
			{
				if(f32_delay <= MAX_8_BIT_DELAY_US(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_32))
				*ptr_u16_prescale=P_32;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_128))
				*ptr_u16_prescale=P_128;
				else if(f32_delay <= MAX_8_BIT_DELAY_US(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <=MAX_8_BIT_DELAY_US(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else
		{
			bo_return_value = FALSE;
		}
	}
	else if (enu_time_unit == ENU_MILLI_SECOND)
	{
		if(enu_tmr_channel_id == ENU_TMR_CHANNEL_0)
		{
			if(f32_delay <= MAX_8_BIT_DELAY_MS(P_1024) )
			{
				if(f32_delay <= MAX_8_BIT_DELAY_MS(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_1)
		{

			if(f32_delay <= MAX_16_BIT_DELAY_MS(P_1024) )
			{
				if(f32_delay <= MAX_16_BIT_DELAY_MS(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_16_BIT_DELAY_MS(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_16_BIT_DELAY_MS(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_16_BIT_DELAY_MS(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <= MAX_16_BIT_DELAY_MS(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale= P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_2)
		{
			if(f32_delay <= MAX_8_BIT_DELAY_US(P_1024) )
			{
				if(f32_delay <= MAX_8_BIT_DELAY_MS(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_32))
				*ptr_u16_prescale=P_32;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_128))
				*ptr_u16_prescale=P_128;
				else if(f32_delay <= MAX_8_BIT_DELAY_MS(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <=MAX_8_BIT_DELAY_MS(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else
		{
			bo_return_value = FALSE;
			// do nothing
		}
	}
	else if (enu_time_unit == ENU_SECOND)
	{
		if(enu_tmr_channel_id == ENU_TMR_CHANNEL_0)
		{
			if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_1024) )
			{
				if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_1)
		{
			if(f32_delay <= MAX_16_BIT_DELAY_SEC(P_1024) )
			{
				if(f32_delay <= MAX_16_BIT_DELAY_SEC(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_16_BIT_DELAY_SEC(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_16_BIT_DELAY_SEC(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_16_BIT_DELAY_SEC(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <= MAX_16_BIT_DELAY_SEC(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_2)
		{
			if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_1024) )
			{
				if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_1))
				*ptr_u16_prescale=P_1;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_8))
				*ptr_u16_prescale=P_8;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_32))
				*ptr_u16_prescale=P_32;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_64))
				*ptr_u16_prescale=P_64;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_128))
				*ptr_u16_prescale=P_128;
				else if(f32_delay <= MAX_8_BIT_DELAY_SEC(P_256))
				*ptr_u16_prescale=P_256;
				else if(f32_delay <=MAX_8_BIT_DELAY_SEC(P_1024))
				*ptr_u16_prescale=P_1024;
				else
				*ptr_u16_prescale = P_0;
			}
			else
			{
				*ptr_u16_prescale = NO_FIT_PRESCALER;
				bo_return_value = TRUE;
			}
		}
		else
		{
			bo_return_value = FALSE;
			// do nothing
		}
	}
	else
	{
		bo_return_value = FALSE;
	}
	return bo_return_value;
}

/**
 * @brief       calc_initialValue			: function used to calculate the timer initial value
 */
BOOLEAN calc_initialValue(enu_tmr_channel_id_t enu_tmr_channel_id,enu_time_unit_t enu_time_unit,uint16 prescaler,float32 delay,uint16* init_value)
{	
	BOOLEAN bo_return_value = TRUE;
	if(enu_tmr_channel_id == ENU_TMR_CHANNEL_0)
	{
		if(enu_time_unit == ENU_MICRO_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_1),delay,MIN_DELAY_US(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_8),delay,MIN_DELAY_US(P_8));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_64),delay,MIN_DELAY_US(P_64));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_256),delay,MIN_DELAY_US(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_1024),delay,MIN_DELAY_US(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else if(enu_time_unit == ENU_MILLI_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_1),delay,MIN_DELAY_MS(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_8),delay,MIN_DELAY_MS(P_8));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_64),delay,MIN_DELAY_MS(P_64));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_256),delay,MIN_DELAY_MS(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_1024),delay,MIN_DELAY_MS(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else if(enu_time_unit == ENU_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_1),delay,MIN_DELAY_SEC(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_8),delay,MIN_DELAY_SEC(P_8));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_64),delay,MIN_DELAY_SEC(P_64));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_256),delay,MIN_DELAY_SEC(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_1024),delay,MIN_DELAY_SEC(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else
		{
			// do nothing
		}
	}
	else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_1)
	{
		if(enu_time_unit == ENU_MICRO_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_US(P_1),delay,MIN_DELAY_US(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_US(P_8),delay,MIN_DELAY_US(P_8));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_US(P_64),delay,MIN_DELAY_US(P_64));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_US(P_256),delay,MIN_DELAY_US(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_US(P_1024),delay,MIN_DELAY_US(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else if(enu_time_unit == ENU_MILLI_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_MS(P_1),delay,MIN_DELAY_MS(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_MS(P_8),delay,MIN_DELAY_MS(P_8));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_MS(P_64),delay,MIN_DELAY_MS(P_64));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_MS(P_256),delay,MIN_DELAY_MS(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_MS(P_1024),delay,MIN_DELAY_MS(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else if(enu_time_unit == ENU_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_SEC(P_1),delay,MIN_DELAY_SEC(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_SEC(P_8),delay,MIN_DELAY_SEC(P_8));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_SEC(P_64),delay,MIN_DELAY_SEC(P_64));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_SEC(P_256),delay,MIN_DELAY_SEC(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_16_BIT_DELAY_SEC(P_1024),delay,MIN_DELAY_SEC(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else
		{
			// do nothing
		}
	}
	else if(enu_tmr_channel_id == ENU_TMR_CHANNEL_2)
	{
		if(enu_time_unit == ENU_MICRO_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_1),delay,MIN_DELAY_US(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_8),delay,MIN_DELAY_US(P_8));
				break;
				case P_32:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_32),delay,MIN_DELAY_US(P_32));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_64),delay,MIN_DELAY_US(P_64));
				break;
				case P_128:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_128),delay,MIN_DELAY_US(P_128));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_256),delay,MIN_DELAY_US(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_US(P_1024),delay,MIN_DELAY_US(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else if(enu_time_unit == ENU_MILLI_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_1),delay,MIN_DELAY_MS(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_8),delay,MIN_DELAY_MS(P_8));
				break;
				case P_32:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_32),delay,MIN_DELAY_MS(P_32));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_64),delay,MIN_DELAY_MS(P_64));
				break;
				case P_128:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_128),delay,MIN_DELAY_MS(P_128));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_256),delay,MIN_DELAY_MS(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_MS(P_1024),delay,MIN_DELAY_MS(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else if(enu_time_unit == ENU_SECOND)
		{
			switch(prescaler)
			{
				case P_1:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_1),delay,MIN_DELAY_SEC(P_1));
				break;
				case P_8:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_8),delay,MIN_DELAY_SEC(P_8));
				break;
				case P_32:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_32),delay,MIN_DELAY_SEC(P_32));
				break;
				case P_64:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_64),delay,MIN_DELAY_SEC(P_64));
				break;
				case P_128:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_128),delay,MIN_DELAY_SEC(P_128));
				break;
				case P_256:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_256),delay,MIN_DELAY_SEC(P_256));
				break;
				case P_1024:
				*init_value=INIT_VALUE(MAX_8_BIT_DELAY_SEC(P_1024),delay,MIN_DELAY_SEC(P_1024));
				break;
				default:
				{
					*init_value=FALSE;
					bo_return_value = FALSE;
				}
				break;
			}
		}
		else
		{
			//do nothing
		}
		
	}
	else
	{
		bo_return_value = FALSE;
	}
	return bo_return_value;
}