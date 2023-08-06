/*
 * tmr_services.c
 *
 * Created: 2023-07-30 2:01:24 AM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "tmr_services.h"
#include "..\..\MCAL\TIMER\timer_utilities.h"
/*============= TYPE DEFINITION =============*/

/*===============MACROS DEFINTION ================*/

/*============= PRIVATE FUNCTION PROTOTYPE =============*/
static volatile void timeOut_callBack (void);

/*===============GLOBAL VARIBALS ================*/
static uint16 gl_u16_realPart[MAX_TIMER_ID]			= {ZERO_VALUE};
static float32 gl_f32_reminderPart[MAX_TIMER_ID]	= {ZERO_VALUE};
static BOOLEAN gl_bo_timeOut_flag [MAX_TIMER_ID]	= {FALSE};
static uint8	gl_u8_timer_id						= MAX_TIMER_ID;
static uint16	gl_u16_prescale[MAX_TIMER_ID]		= {ZERO_VALUE};
static uint16	gl_u16_initialValue[MAX_TIMER_ID]	= {ZERO_VALUE};
static BOOLEAN gl_bo_overFlow_flag[MAX_TIMER_ID]	= {FALSE};

void (*gl_fun_ptr_arr[MAX_TIMER_ID]) (void)			= {NULL_PTR};	

/*============= FUNCTION PROTOTYPE =============*/

enu_time_error_t delay_us	(uint8 u8_timer_id,float32 f32_time_delay)
{
	enu_time_error_t enu_time_error = ENU_TIMER_VALID;
	BOOLEAN bo_l_return_state		= FALSE ;
	uint16 u16_l_prescale			= ZERO_VALUE;
	uint16 u16_l_initialValue		= ZERO_VALUE;
	float32 f32_l_overFlows			= ZERO_VALUE;
	uint8 u8_l_flag_status			= ZERO_VALUE;
	uint16 u16_l_realPart			= ZERO_VALUE;
	float32 f32_l_reminderPart		= ZERO_VALUE;
	str_tmr_config_t str_tmr_config ;
	str_tmr_config.enu_tmr_channel_id		= u8_timer_id;
	str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
	str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
	str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_DISABLE;
	str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
	
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		//compare delay with max timer value and if delay < max timer value, find the best prescaler value
		bo_l_return_state = calc_prescaler(f32_time_delay,u8_timer_id,ENU_MICRO_SECOND,&u16_l_prescale);
		if(bo_l_return_state == TRUE)
		{
			if (u16_l_prescale != NO_FIT_PRESCALER)
			{
				//use timer without overflows
				calc_initialValue(u8_timer_id,ENU_MICRO_SECOND,u16_l_prescale,f32_time_delay,&u16_l_initialValue);
				str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
				str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
				timer_init(&str_tmr_config);
				timer_start(u8_timer_id);
				//wait for timer_flag_notification
				do 
				{
					timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
				} while (u8_l_flag_status == LOGIC_FALSE);
				
			}
			else
			{
				str_tmr_config.enu_tmr_clk				= timer_clk_map(P_1024);
				str_tmr_config.u16_tmr_initial_value	= ZERO_VALUE;
				//calculate number of overflows
				if(u8_timer_id == ENU_TMR_CHANNEL_0 || u8_timer_id == ENU_TMR_CHANNEL_2)
				{
					f32_l_overFlows = f32_time_delay / MAX_8_BIT_DELAY_US(P_1024);
					u16_l_realPart = (uint16)f32_l_overFlows;
					f32_l_reminderPart = (f32_l_overFlows - u16_l_realPart) * MAX_8_BIT_DELAY_US(P_1024);
				}
				else
				{
					f32_l_overFlows = f32_time_delay / MAX_16_BIT_DELAY_US(P_1024);
					u16_l_realPart = (uint16)f32_l_overFlows;
					f32_l_reminderPart =((f32_l_overFlows - u16_l_realPart) * MAX_16_BIT_DELAY_US(P_1024));
				}
				while (u16_l_realPart != ZERO_VALUE)
				{
					timer_init(&str_tmr_config);
					timer_start(u8_timer_id);
					do 
					{
						timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
					}while (u8_l_flag_status == LOGIC_FALSE);
					u16_l_realPart--;
				}
				if(f32_l_reminderPart > ZERO_VALUE)
				{
					calc_prescaler(f32_l_reminderPart,u8_timer_id,ENU_MICRO_SECOND,&u16_l_prescale);
					calc_initialValue(u8_timer_id,ENU_MICRO_SECOND,u16_l_prescale,f32_l_reminderPart,&u16_l_initialValue);
					str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
					str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
					timer_init(&str_tmr_config);
					timer_start(u8_timer_id);
					//wait for timer_flag_notification
					do 
					{
						timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
					} while (u8_l_flag_status == LOGIC_FALSE);
				}
			}
		}
		else
		{
			enu_time_error = ENU_TIMER_INVALID_ID;
		}		
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}

enu_time_error_t delay_ms	(uint8 u8_timer_id,float32 f32_time_delay)
{
	enu_time_error_t enu_time_error = ENU_TIMER_VALID;
	BOOLEAN bo_l_return_state		= FALSE ;
	uint16 u16_l_prescale			= ZERO_VALUE;
	uint16 u16_l_initialValue		= ZERO_VALUE;
	float32 f32_l_overFlows			= ZERO_VALUE;
	uint8 u8_l_flag_status			= ZERO_VALUE;
	uint16 u16_l_realPart			= ZERO_VALUE;
	float32 f32_l_reminderPart		= ZERO_VALUE;
	str_tmr_config_t str_tmr_config ;
	str_tmr_config.enu_tmr_channel_id		= u8_timer_id;
	str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
	str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
	str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_DISABLE;
	str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
	
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		//compare delay with max timer value and if delay < max timer value, find the best prescaler value
		bo_l_return_state = calc_prescaler(f32_time_delay,u8_timer_id,ENU_MILLI_SECOND,&u16_l_prescale);
		if(bo_l_return_state == TRUE)
		{
			if (u16_l_prescale != NO_FIT_PRESCALER)
			{
				//use timer without overflows
				calc_initialValue(u8_timer_id,ENU_MILLI_SECOND,u16_l_prescale,f32_time_delay,&u16_l_initialValue);
				str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
				str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
				timer_init(&str_tmr_config);
				timer_start(u8_timer_id);
				//wait for timer_flag_notification
				do 
				{
					timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
				} while (u8_l_flag_status == LOGIC_FALSE);
				
			}
			else
			{
				str_tmr_config.enu_tmr_clk				= timer_clk_map(P_1024);
				str_tmr_config.u16_tmr_initial_value	= ZERO_VALUE;
				//calculate number of overflows
				if(u8_timer_id == ENU_TMR_CHANNEL_0 || u8_timer_id == ENU_TMR_CHANNEL_2)
				{
					f32_l_overFlows = f32_time_delay / MAX_8_BIT_DELAY_MS(P_1024);
					u16_l_realPart = (uint16)f32_l_overFlows;
					f32_l_reminderPart = (f32_l_overFlows - u16_l_realPart) * MAX_8_BIT_DELAY_MS(P_1024);
				}
				else
				{
					f32_l_overFlows = f32_time_delay / MAX_16_BIT_DELAY_MS(P_1024);
					u16_l_realPart = (uint16)f32_l_overFlows;
					f32_l_reminderPart =((f32_l_overFlows - u16_l_realPart) * MAX_16_BIT_DELAY_MS(P_1024));
				}
				while (u16_l_realPart != ZERO_VALUE)
				{
					timer_init(&str_tmr_config);
					timer_start(u8_timer_id);
					do 
					{
						timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
					}while (u8_l_flag_status == LOGIC_FALSE);
					u16_l_realPart--;
				}
				if(f32_l_reminderPart > ZERO_VALUE)
				{
					calc_prescaler(f32_l_reminderPart,u8_timer_id,ENU_MILLI_SECOND,&u16_l_prescale);
					calc_initialValue(u8_timer_id,ENU_MILLI_SECOND,u16_l_prescale,f32_l_reminderPart,&u16_l_initialValue);
					str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
					str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
					timer_init(&str_tmr_config);
					timer_start(u8_timer_id);
					//wait for timer_flag_notification
					do 
					{
						timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
					} while (u8_l_flag_status == LOGIC_FALSE);
				}
			}
		}
		else
		{
			enu_time_error = ENU_TIMER_INVALID_ID;
		}		
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}

enu_time_error_t delay_sec	(uint8 u8_timer_id,float32 f32_time_delay)
{

	enu_time_error_t enu_time_error = ENU_TIMER_VALID;
	BOOLEAN bo_l_return_state		= FALSE ;
	uint16 u16_l_prescale			= ZERO_VALUE;
	uint16 u16_l_initialValue		= ZERO_VALUE;
	float32 f32_l_overFlows			= ZERO_VALUE;
	uint8 u8_l_flag_status			= ZERO_VALUE;
	uint16 u16_l_realPart			= ZERO_VALUE;
	float32 f32_l_reminderPart		= ZERO_VALUE;
	str_tmr_config_t str_tmr_config ;	
	str_tmr_config.enu_tmr_channel_id		= u8_timer_id;
	str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
	str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
	str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_DISABLE;
	str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
	
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		//compare delay with max timer value and if delay < max timer value, find the best prescaler value
		bo_l_return_state = calc_prescaler(f32_time_delay,u8_timer_id,ENU_SECOND,&u16_l_prescale);
		if(bo_l_return_state == TRUE)
		{
			if (u16_l_prescale != NO_FIT_PRESCALER)
			{
				//use timer without overflows
				calc_initialValue(u8_timer_id,ENU_SECOND,u16_l_prescale,f32_time_delay,&u16_l_initialValue);
				str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
				str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
				timer_init(&str_tmr_config);
				timer_start(u8_timer_id);
				//wait for timer_flag_notification
				do 
				{
					timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
				} while (u8_l_flag_status == LOGIC_FALSE);
				
			}
			else
			{
				str_tmr_config.enu_tmr_clk				= timer_clk_map(P_1024);
				str_tmr_config.u16_tmr_initial_value	= ZERO_VALUE;
				//calculate number of overflows
				if(u8_timer_id == ENU_TMR_CHANNEL_0 || u8_timer_id == ENU_TMR_CHANNEL_2)
				{
					f32_l_overFlows = f32_time_delay / MAX_8_BIT_DELAY_SEC(P_1024);
					u16_l_realPart = (uint16)f32_l_overFlows;
					f32_l_reminderPart = (f32_l_overFlows - u16_l_realPart) * MAX_8_BIT_DELAY_SEC(P_1024);
				}
				else
				{
					f32_l_overFlows = f32_time_delay / MAX_16_BIT_DELAY_SEC(P_1024);
					u16_l_realPart = (uint16)f32_l_overFlows;
					f32_l_reminderPart =((f32_l_overFlows - u16_l_realPart) * MAX_16_BIT_DELAY_SEC(P_1024));
				}
				while (u16_l_realPart != ZERO_VALUE)
				{
					timer_init(&str_tmr_config);
					timer_start(u8_timer_id);
					do 
					{
						timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
					}while (u8_l_flag_status == LOGIC_FALSE);
					u16_l_realPart--;
				}
				if(f32_l_reminderPart > ZERO_VALUE)
				{
					calc_prescaler(f32_l_reminderPart,u8_timer_id,ENU_SECOND,&u16_l_prescale);
					calc_initialValue(u8_timer_id,ENU_SECOND,u16_l_prescale,f32_l_reminderPart,&u16_l_initialValue);
					str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
					str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
					timer_init(&str_tmr_config);
					timer_start(u8_timer_id);
					//wait for timer_flag_notification
					do 
					{
						timer_flag_notification(u8_timer_id,ENU_TMR_NORMAL_MODE,&u8_l_flag_status);
					} while (u8_l_flag_status == LOGIC_FALSE);
				}
			}
		}
		else
		{
			enu_time_error = ENU_TIMER_INVALID_ID;
		}		
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}

enu_time_error_t timeOut_us	(uint8 u8_timer_id,float32 f32_time_delay)
{
	enu_time_error_t enu_time_error		= ENU_TIMER_VALID;
	uint16 u16_l_prescale				= ZERO_VALUE;
	uint16 u16_l_initialValue			= ZERO_VALUE;
	BOOLEAN bo_l_return_state			= FALSE ;
	float32 f32_l_overFlows				= ZERO_VALUE;
	gl_bo_timeOut_flag [gl_u8_timer_id] = FALSE;
	str_tmr_config_t str_tmr_config ;
	str_tmr_config.enu_tmr_channel_id		= u8_timer_id;
	str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
	str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
	str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_ENABLE;
	str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
	gl_u8_timer_id							= u8_timer_id;
	
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		bo_l_return_state = calc_prescaler(f32_time_delay,u8_timer_id,ENU_MICRO_SECOND,&u16_l_prescale);
		if(bo_l_return_state == TRUE)
		{
			if (u16_l_prescale != NO_FIT_PRESCALER)
			{
				//use timer without overflows
				gl_bo_overFlow_flag[u8_timer_id] = FALSE; 
				calc_initialValue(u8_timer_id,ENU_MICRO_SECOND,u16_l_prescale,f32_time_delay,&u16_l_initialValue);
				str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
				str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
			}
			else
			{
				//use timer with overflows
				gl_bo_overFlow_flag[u8_timer_id]	= TRUE; 
				str_tmr_config.enu_tmr_clk			= timer_clk_map(P_1024);
				str_tmr_config.u16_tmr_initial_value= ZERO_VALUE;
				//calculate number of overflows
				if(u8_timer_id == ENU_TMR_CHANNEL_0 || u8_timer_id == ENU_TMR_CHANNEL_2)
				{
					f32_l_overFlows = f32_time_delay / MAX_8_BIT_DELAY_US(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] = ((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_8_BIT_DELAY_US(P_1024));
				}
				else
				{
					f32_l_overFlows = f32_time_delay / MAX_16_BIT_DELAY_US(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] =((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_16_BIT_DELAY_US(P_1024));
				}
				calc_prescaler(gl_f32_reminderPart[u8_timer_id],u8_timer_id,ENU_MICRO_SECOND,&gl_u16_prescale[u8_timer_id]);
				calc_initialValue(u8_timer_id,ENU_MICRO_SECOND,gl_u16_prescale[u8_timer_id],gl_f32_reminderPart[u8_timer_id],&gl_u16_initialValue[u8_timer_id]);
			}
			timer_init(&str_tmr_config);
			timer_setCallBack(u8_timer_id,timeOut_callBack,ENU_TMR_NORMAL_MODE);
			timer_start(u8_timer_id);
		}
		else
		{
			
		}
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}

enu_time_error_t timeOut_ms	(uint8 u8_timer_id,float32 f32_time_delay)
{
	enu_time_error_t enu_time_error		= ENU_TIMER_VALID;
	uint16 u16_l_prescale				= ZERO_VALUE;
	uint16 u16_l_initialValue			= ZERO_VALUE;
	BOOLEAN bo_l_return_state			= FALSE ;
	float32 f32_l_overFlows				= ZERO_VALUE;
	gl_bo_timeOut_flag [gl_u8_timer_id] = FALSE;
	str_tmr_config_t str_tmr_config ;
	str_tmr_config.enu_tmr_channel_id		= u8_timer_id;
	str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
	str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
	str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_ENABLE;
	str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
	gl_u8_timer_id							= u8_timer_id;
	
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		bo_l_return_state = calc_prescaler(f32_time_delay,u8_timer_id,ENU_MILLI_SECOND,&u16_l_prescale);
		if(bo_l_return_state == TRUE)
		{
			if (u16_l_prescale != NO_FIT_PRESCALER)
			{
				//use timer without overflows
				gl_bo_overFlow_flag[u8_timer_id] = FALSE; 
				calc_initialValue(u8_timer_id,ENU_MILLI_SECOND,u16_l_prescale,f32_time_delay,&u16_l_initialValue);
				str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
				str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
			}
			else
			{
				gl_bo_overFlow_flag[u8_timer_id]	= TRUE; 
				str_tmr_config.enu_tmr_clk			= timer_clk_map(P_1024);
				str_tmr_config.u16_tmr_initial_value= ZERO_VALUE;
				//calculate number of overflows
				if(u8_timer_id == ENU_TMR_CHANNEL_0 || u8_timer_id == ENU_TMR_CHANNEL_2)
				{
					f32_l_overFlows = f32_time_delay / MAX_8_BIT_DELAY_MS(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] = ((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_8_BIT_DELAY_MS(P_1024));
				}
				else
				{
					f32_l_overFlows = f32_time_delay / MAX_16_BIT_DELAY_MS(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] =((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_16_BIT_DELAY_MS(P_1024));
				}
				calc_prescaler(gl_f32_reminderPart[u8_timer_id],u8_timer_id,ENU_MILLI_SECOND,&gl_u16_prescale[u8_timer_id]);
				calc_initialValue(u8_timer_id,ENU_MILLI_SECOND,gl_u16_prescale[u8_timer_id],gl_f32_reminderPart[u8_timer_id],&gl_u16_initialValue[u8_timer_id]);
			}
			timer_init(&str_tmr_config);
			timer_setCallBack(u8_timer_id,timeOut_callBack,ENU_TMR_NORMAL_MODE);
			timer_start(u8_timer_id);
		}
		else
		{
			
		}
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}

enu_time_error_t timeOut_sec(uint8 u8_timer_id,float32 f32_time_delay)
{
	enu_time_error_t enu_time_error		= ENU_TIMER_VALID;
	uint16 u16_l_prescale				= ZERO_VALUE;
	uint16 u16_l_initialValue			= ZERO_VALUE;
	BOOLEAN bo_l_return_state			= FALSE ;
	float32 f32_l_overFlows				= ZERO_VALUE;
	gl_bo_timeOut_flag [gl_u8_timer_id] = FALSE;
	str_tmr_config_t str_tmr_config ;
	str_tmr_config.enu_tmr_channel_id		= u8_timer_id;
	str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
	str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
	str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_ENABLE;
	str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
	gl_u8_timer_id							= u8_timer_id;
	
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		bo_l_return_state = calc_prescaler(f32_time_delay,u8_timer_id,ENU_SECOND,&u16_l_prescale);
		if(bo_l_return_state == TRUE)
		{
			if (u16_l_prescale != NO_FIT_PRESCALER)
			{
				//use timer without overflows
				gl_bo_overFlow_flag[u8_timer_id] = FALSE; 
				//calculate initial value
				calc_initialValue(u8_timer_id,ENU_SECOND,u16_l_prescale,f32_time_delay,&u16_l_initialValue);
				str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
				str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
			}
			else
			{
				gl_bo_overFlow_flag[u8_timer_id]	= TRUE; 
				str_tmr_config.enu_tmr_clk			= timer_clk_map(P_1024);
				str_tmr_config.u16_tmr_initial_value= ZERO_VALUE;
				//calculate number of overflows
				if(u8_timer_id == ENU_TMR_CHANNEL_0 || u8_timer_id == ENU_TMR_CHANNEL_2)
				{
					f32_l_overFlows = f32_time_delay / MAX_8_BIT_DELAY_SEC(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] = ((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_8_BIT_DELAY_SEC(P_1024));
				}
				else
				{
					f32_l_overFlows = f32_time_delay / MAX_16_BIT_DELAY_SEC(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] =((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_16_BIT_DELAY_SEC(P_1024));
				}
				calc_prescaler(gl_f32_reminderPart[u8_timer_id],u8_timer_id,ENU_SECOND,&gl_u16_prescale[u8_timer_id]);
				calc_initialValue(u8_timer_id,ENU_SECOND,gl_u16_prescale[u8_timer_id],gl_f32_reminderPart[u8_timer_id],&gl_u16_initialValue[u8_timer_id]);
			}
			timer_init(&str_tmr_config);
			timer_setCallBack(u8_timer_id,timeOut_callBack,ENU_TMR_NORMAL_MODE);
			timer_start(u8_timer_id);
		}
		else
		{
			
		}
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}

enu_time_error_t timer_callEvent_ms (uint8 u8_timer_id,float32 f32_time_delay,void(*f_ptr)(void))
{
	enu_time_error_t enu_time_error		= ENU_TIMER_VALID;
	uint16 u16_l_prescale				= ZERO_VALUE;
	uint16 u16_l_initialValue			= ZERO_VALUE;
	BOOLEAN bo_l_return_state			= FALSE ;
	float32 f32_l_overFlows				= ZERO_VALUE;
	str_tmr_config_t str_tmr_config ;
	str_tmr_config.enu_tmr_channel_id		= u8_timer_id;
	str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
	str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
	str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_ENABLE;
	str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
	gl_u8_timer_id							= u8_timer_id;
	gl_fun_ptr_arr[u8_timer_id]				= f_ptr;
	
	
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		bo_l_return_state = calc_prescaler(f32_time_delay,u8_timer_id,ENU_MILLI_SECOND,&u16_l_prescale);
		if(bo_l_return_state == TRUE)
		{
			if (u16_l_prescale != NO_FIT_PRESCALER)
			{
				//use timer without overflows
				gl_bo_overFlow_flag[u8_timer_id] = FALSE;
				calc_initialValue(u8_timer_id,ENU_MILLI_SECOND,u16_l_prescale,f32_time_delay,&u16_l_initialValue);
				str_tmr_config.enu_tmr_clk				= timer_clk_map(u16_l_prescale);
				str_tmr_config.u16_tmr_initial_value	= u16_l_initialValue;
			}
			else
			{
				gl_bo_overFlow_flag[u8_timer_id]	= TRUE;
				str_tmr_config.enu_tmr_clk			= timer_clk_map(P_1024);
				str_tmr_config.u16_tmr_initial_value= ZERO_VALUE;
				//calculate number of overflows
				if(u8_timer_id == ENU_TMR_CHANNEL_0 || u8_timer_id == ENU_TMR_CHANNEL_2)
				{
					f32_l_overFlows = f32_time_delay / MAX_8_BIT_DELAY_MS(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] = ((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_8_BIT_DELAY_MS(P_1024));
				}
				else
				{
					f32_l_overFlows = f32_time_delay / MAX_16_BIT_DELAY_MS(P_1024);
					gl_u16_realPart[u8_timer_id] = (uint16)f32_l_overFlows;
					gl_f32_reminderPart[u8_timer_id] =((f32_l_overFlows - gl_u16_realPart[u8_timer_id]) * MAX_16_BIT_DELAY_MS(P_1024));
				}
				calc_prescaler(gl_f32_reminderPart[u8_timer_id],u8_timer_id,ENU_MILLI_SECOND,&gl_u16_prescale[u8_timer_id]);
				calc_initialValue(u8_timer_id,ENU_MILLI_SECOND,gl_u16_prescale[u8_timer_id],gl_f32_reminderPart[u8_timer_id],&gl_u16_initialValue[u8_timer_id]);
			}
			timer_init(&str_tmr_config);
			timer_setCallBack(u8_timer_id,timeOut_callBack,ENU_TMR_NORMAL_MODE);
			timer_start(u8_timer_id);
		}
		else
		{
			//wrong input...do nothing
		}
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;	
}

enu_time_error_t timer_check_time_out_flag (uint8 u8_timer_id,uint8* ptr_u8_flag)
{
	enu_time_error_t enu_time_error = ENU_TIMER_VALID;
	if(u8_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		if(ptr_u8_flag != NULL_PTR)
		{	
			//if(gl_bo_timeOut_flag[u8_timer_id] == TRUE)
			{
				*ptr_u8_flag = gl_bo_timeOut_flag[u8_timer_id];
				gl_bo_timeOut_flag[u8_timer_id] = FALSE;	
			}
		}
		else
		{
			enu_time_error = ENU_TIMER_INVALID_INPUT;
		}	
	}
	else
	{
		enu_time_error = ENU_TIMER_INVALID_ID;
	}
	return enu_time_error;
}

/*============= PRIVATE FUNCTION DEFINITIONS =============*/

volatile void timeOut_callBack (void)
{
	static uint16 gl_u16_tick_count			= ZERO_VALUE;
	enu_tmr_clk_t enu_tmr_clk = ENU_TMR_MAX_CLK;
	if(gl_bo_overFlow_flag[gl_u8_timer_id] == FALSE) // no overflows needed
	{
		timer_stop(gl_u8_timer_id);
		if(gl_fun_ptr_arr[gl_u8_timer_id] != NULL_PTR)
		{
			(*gl_fun_ptr_arr[gl_u8_timer_id])();
		}
		gl_bo_timeOut_flag[gl_u8_timer_id] = TRUE ;
	}
	else // overflows needed
	{
		gl_u16_tick_count++;
		if(gl_u16_tick_count == gl_u16_realPart[gl_u8_timer_id])
		{
			timer_stop(gl_u8_timer_id);
			gl_u16_tick_count = ZERO_VALUE;
			if(gl_f32_reminderPart[gl_u8_timer_id] > ZERO_VALUE)
			{
				timer_setInitialValue(gl_u8_timer_id,gl_u16_initialValue[gl_u8_timer_id]);
				enu_tmr_clk = timer_clk_map(gl_u16_prescale[gl_u8_timer_id]);
				timer_setClock (gl_u8_timer_id,enu_tmr_clk);
				timer_start(gl_u8_timer_id);
				gl_bo_overFlow_flag[gl_u8_timer_id] = FALSE;
			}
		}
	}
}

enu_tmr_clk_t timer_clk_map(uint16 u16_l_prescale)
{
	enu_tmr_clk_t enu_tmr_clk = ENU_TMR_MAX_CLK;
	switch(u16_l_prescale)
	{
		case 0:		enu_tmr_clk = ENU_TMR_NO_CLK;	break;
		case 1:		enu_tmr_clk = ENU_TMR_CLK_1;	break;
		case 8:		enu_tmr_clk = ENU_TMR_CLK_8;	break;
		case 32:	enu_tmr_clk = ENU_TMR_CLK_32;	break;
		case 64:	enu_tmr_clk = ENU_TMR_CLK_64;	break;
		case 128:	enu_tmr_clk = ENU_TMR_CLK_128;	break;
		case 256:	enu_tmr_clk = ENU_TMR_CLK_256;	break;
		case 1024:	enu_tmr_clk = ENU_TMR_CLK_1024; break;
		default:	enu_tmr_clk = ENU_TMR_MAX_CLK;	break;
	}
	return enu_tmr_clk;
}