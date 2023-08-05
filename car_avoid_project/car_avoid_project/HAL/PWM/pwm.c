/*
 * 	File:						pwm.c
 *	Module:					PWM
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "pwm.h"

/*=========MACRO DEFINITIONS=========*/
#define MAX_DUTY_CYCLE 100.0F

/*=========EXTERN VARIABLES=========*/

/*=========STATIC GLOBAL VARIABLES=========*/
static uint8	gs_u8_gpio_port_id		= ZERO_VALUE;	
static uint8	gs_u8_gpio_pin_id 		= ZERO_VALUE;
static uint8	gs_u8_timer_id 			= ZERO_VALUE;
static BOOLEAN	gs_bo_pwm_flag			= FALSE;
static uint8 	gs_u8_duty_cycle		= ZERO_VALUE;

static uint8	gs_u8_periodic_prescale	 = ZERO_VALUE;
static uint8	gs_u8_offTime_prescale	 = ZERO_VALUE;
static uint8	gs_u8_onTime_prescale	 = ZERO_VALUE;
static uint16	gs_u16_periodic_initValue= ZERO_VALUE;
static uint16	gs_u16_offTime_initValue = ZERO_VALUE;
static uint16	gs_u16_onTime_initValue	 = ZERO_VALUE;


/*=========TYPE DEFINITIONS=========*/


/*=========PRIVATE FUNCTIONS=========*/
static void PWM_callback	(void);

/*=========APIs DEFINITIONS=========*/

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
enu_pwm_error_t PWM_Init(uint8 u8_pwm_port_id,uint8 u8_pwm_pin_id,uint8 u8_pwm_timer_id)
{
	enu_pwm_error_t enu_pwm_error = ENU_PWM_VALID_OPERATION;
	str_tmr_config_t str_tmr_config;
	//check the passing parameters
	if((u8_pwm_port_id < MAX_PORT_ID) && (u8_pwm_pin_id < MAX_PIN_ID) && (u8_pwm_timer_id < MAX_ENU_TMR_CHANNEL))
	{
		//set global variables
		gs_u8_gpio_port_id	= u8_pwm_port_id;
		gs_u8_gpio_pin_id	= u8_pwm_pin_id;
		gs_u8_timer_id		= u8_pwm_timer_id;
		//initialize TIMER
		str_tmr_config.enu_tmr_channel_id		= u8_pwm_timer_id;
		str_tmr_config.enu_tmr_clk				= ENU_TMR_NO_CLK;
		str_tmr_config.enu_tmr_mode				= ENU_TMR_NORMAL_MODE;
		str_tmr_config.enu_tmr_cmp_mode			= ENU_TMR_CMP_DISCONNECT;
		str_tmr_config.enu_tmr_interrupt_state	= ENU_TMR_INT_ENABLE;
		str_tmr_config.u16_tmr_initial_value	= ZERO_VALUE;
		str_tmr_config.u16_tmr_compare_value	= ZERO_VALUE;
		timer_init(&str_tmr_config);
		timer_setCallBack(u8_pwm_timer_id,PWM_callback,ENU_TMR_NORMAL_MODE);
		//initialize GPIO
		DIO_pinMode(u8_pwm_port_id,u8_pwm_pin_id,PIN_OUTPUT);
		DIO_writePin(u8_pwm_port_id,u8_pwm_pin_id,PIN_LOW);
	}
	else
	{
		enu_pwm_error = ENU_PWM_INVALID_OPERATION;
	}
	return enu_pwm_error;
}


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
enu_pwm_error_t PWM_start(uint8 u8_pwm_timer_id,uint32 u32_periodic_time,uint8 u8_duty_cycle)
{
	enu_pwm_error_t enu_pwm_error	= ENU_PWM_VALID_OPERATION;
	float32 f32_on_time				= ZERO_VALUE;
	float32 f32_off_time			= ZERO_VALUE;
	uint16  u16_periodic_prescale	= ZERO_VALUE;
	uint16	u16_offTime_prescale	= ZERO_VALUE;
	uint16	u16_onTime_prescale		= ZERO_VALUE;
	gs_u8_duty_cycle				= u8_duty_cycle;
	
	if((u8_pwm_timer_id < MAX_ENU_TMR_CHANNEL) && (u32_periodic_time > ZERO_VALUE))
	{
		if((u8_duty_cycle < MAX_DUTY_CYCLE) && (u8_duty_cycle > ZERO_VALUE))
		{
			f32_off_time	= ((float32)u32_periodic_time*u8_duty_cycle)/MAX_DUTY_CYCLE;	//calculate on time delay
			f32_on_time		= u32_periodic_time - f32_off_time;
			calc_prescaler(f32_off_time,u8_pwm_timer_id,ENU_MILLI_SECOND,&u16_offTime_prescale);
			calc_prescaler(f32_on_time,u8_pwm_timer_id,ENU_MILLI_SECOND,&u16_onTime_prescale);
			calc_initialValue(u8_pwm_timer_id,ENU_MILLI_SECOND,u16_offTime_prescale,f32_off_time,&gs_u16_offTime_initValue);
			calc_initialValue(u8_pwm_timer_id,ENU_MILLI_SECOND,u16_onTime_prescale,f32_on_time,&gs_u16_onTime_initValue);
			gs_u8_onTime_prescale	= (uint8) timer_clk_map(u16_onTime_prescale);
			gs_u8_offTime_prescale	= (uint8) timer_clk_map(u16_offTime_prescale);
			timer_setInitialValue(u8_pwm_timer_id,gs_u16_onTime_initValue);
			timer_setClock(u8_pwm_timer_id,gs_u8_onTime_prescale);
		}
		else 
		{
			calc_prescaler(u32_periodic_time,u8_pwm_timer_id,ENU_MILLI_SECOND,&u16_periodic_prescale);
			calc_initialValue(u8_pwm_timer_id,ENU_MILLI_SECOND,u16_periodic_prescale,u32_periodic_time,&gs_u16_periodic_initValue);
			gs_u8_periodic_prescale	= (uint8) timer_clk_map(u16_periodic_prescale);
			timer_setInitialValue(u8_pwm_timer_id,gs_u16_periodic_initValue);
			timer_setClock(u8_pwm_timer_id,gs_u8_periodic_prescale);
		}
		timer_start(u8_pwm_timer_id);
	}
	else
	{
		enu_pwm_error = ENU_PWM_INVALID_OPERATION;
	}
	return enu_pwm_error;
}

/**
 * @brief       PWM_stop        			: Function used to stop generate PWM signal  
 * 
 * @param[in]	u8_pwm_timer_id				: Timer ID should be

 * @return      ENU_PWM_VALID_OPERATION		: in case of successful operation
 *				ENU_PWM_INVALID_OPERATION	: in case of wrong value      
 */
enu_pwm_error_t PWM_stop(uint8 u8_pwm_timer_id)
{	
	enu_pwm_error_t enu_pwm_error = ENU_PWM_VALID_OPERATION;
	if(u8_pwm_timer_id < MAX_ENU_TMR_CHANNEL)
	{
		timer_stop(u8_pwm_timer_id);
	}
	else
	{
		enu_pwm_error = ENU_PWM_INVALID_OPERATION;
	}
	return enu_pwm_error;
}


/* ============= PWM CALLBACK FUNCTION =============*/
void PWM_callback (void)
{
	if((gs_u8_duty_cycle < MAX_DUTY_CYCLE) && ((gs_u8_duty_cycle > ZERO_VALUE)))
	{
		DIO_togglePin(gs_u8_gpio_port_id,gs_u8_gpio_pin_id);
		timer_stop(gs_u8_timer_id);
		if(gs_bo_pwm_flag == FALSE)		
		{
			timer_setClock(gs_u8_timer_id,gs_u8_offTime_prescale);
			timer_setInitialValue(gs_u8_timer_id,gs_u16_offTime_initValue);
			gs_bo_pwm_flag = TRUE;
		}
		else
		{
			timer_setClock(gs_u8_timer_id,gs_u8_onTime_prescale);
			timer_setInitialValue(gs_u8_timer_id,gs_u16_onTime_initValue);
			gs_bo_pwm_flag = FALSE;
		}
		timer_start(gs_u8_timer_id);
	}
	else if (gs_u8_duty_cycle == MAX_DUTY_CYCLE)
	{
		DIO_writePin(gs_u8_gpio_port_id,gs_u8_gpio_pin_id,PIN_HIGH);
	}
	else
	{
		DIO_writePin(gs_u8_gpio_port_id,gs_u8_gpio_pin_id,PIN_LOW);
	}
}



