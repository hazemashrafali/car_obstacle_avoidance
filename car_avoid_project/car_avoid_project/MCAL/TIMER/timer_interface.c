/*
 * timer_interface.c
 *
 * Created: 2023-07-26 9:32:42 PM
 *  Author: HAZEM-PC
 */ 

/*===============FILE ENCLUTION ================*/
#include "timer_interface.h"

/*===============GLOBAL PRIVATE VARIBALS ================*/
static BOOLEAN gl_bo_timer_init_flag [MAX_ENU_TMR_CHANNEL] = {FALSE,FALSE,FALSE};  // used to keep the timer state [initialized - uninitialized]
static enu_tmr_clk_t gl_enu_tmr_clk [MAX_ENU_TMR_CHANNEL] = {ENU_TMR_MAX_CLK,ENU_TMR_MAX_CLK,ENU_TMR_MAX_CLK};  //used to keep timer clock setting
static volatile void (*gl_callBackPtr_timer0_OVF)(void) = NULL_PTR;
static volatile void (*gl_callBackPtr_timer1_OVF)(void) = NULL_PTR;
static volatile void (*gl_callBackPtr_timer2_OVF)(void) = NULL_PTR;
static volatile void (*gl_callBackPtr_timer0_COMP)(void) = NULL_PTR;
static volatile void (*gl_callBackPtr_timer1_COMP)(void) = NULL_PTR;
static volatile void (*gl_callBackPtr_timer2_COMP)(void) = NULL_PTR;
/*============= PRIVATE FUNCTIONS =============*/

/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/
#define CLK_MASK_BIT 0xF8
/*===============TYBS DEFINTION ================*/	

/*===============FUNCTION DEFINITIONS ================*/

/**
 * @brief		timer_init		: function used to initialize specific timer channel
 */

enu_tmr_error_t timer_init	(str_tmr_config_t* ptr_str_tmr_config)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;

	if (ptr_str_tmr_config != NULL_PTR)
	{
		if ((ptr_str_tmr_config->enu_tmr_channel_id) < MAX_ENU_TMR_CHANNEL)
		{
			if ((ptr_str_tmr_config->enu_tmr_mode) < ENU_MAX_TMR_MODE )
			{
				if ((ptr_str_tmr_config->enu_tmr_interrupt_state) < ENU_MAX_TMR_STATE )
				{
					if((ptr_str_tmr_config->enu_tmr_cmp_mode) < ENU_MAX_TMR_CMP_MODE)
					{
						if ((ptr_str_tmr_config->enu_tmr_clk) < ENU_TMR_MAX_CLK)
						{
							if ((ptr_str_tmr_config->enu_tmr_channel_id) == ENU_TMR_CHANNEL_0) // timer_0 setup
							{
								//Set FOC PIN as NON PWM MODE
								SET_BIT(TCCR0,FOC0);
								//Configure timer mode
								switch (ptr_str_tmr_config->enu_tmr_mode)
								{
									case ENU_TMR_NORMAL_MODE:
									{
										CLEAR_BIT(TCCR0,WGM00);
										CLEAR_BIT(TCCR0,WGM01);	
									}
									break;
									case ENU_TMR_CMP_MODE:
									{
										CLEAR_BIT(TCCR0,WGM00);
										SET_BIT(TCCR0,WGM01);
									}
									break;
									default:
									{
										// do nothing
									}
								} /*end Configure timer mode*/
								//Configure Output Compare PIN Mode
								switch (ptr_str_tmr_config->enu_tmr_cmp_mode)
								{
									case ENU_TMR_CMP_DISCONNECT:
									{
										CLEAR_BIT(TCCR0,COM00);
										CLEAR_BIT(TCCR0,COM01);
									}
									break;
									case ENU_TMR_CMP_TOGGLE:
									{
										SET_BIT(DDRB,PIN3);
										SET_BIT(TCCR0,COM00);
										CLEAR_BIT(TCCR0,COM01);
									}
									break;
									case ENU_TMR_CMP_CLEAR:
									{
										SET_BIT(DDRB,PIN3);
										CLEAR_BIT(TCCR0,COM00);
										SET_BIT(TCCR0,COM01);
									}
									break;
									case ENU_TMR_CMP_SET:
									{
										SET_BIT(DDRB,PIN3);
										SET_BIT(TCCR0,COM00);
										SET_BIT(TCCR0,COM01);
									}
									break;
									default:
									{
										//do nothing
									}
								}/*end Configure OC PIN Mode*/
								//Clock Select
								if ((ptr_str_tmr_config->enu_tmr_clk != ENU_TMR_CLK_32) && (ptr_str_tmr_config->enu_tmr_clk != ENU_TMR_CLK_128))
								{
									//save clock setting to global variable
									gl_enu_tmr_clk[ptr_str_tmr_config->enu_tmr_channel_id] = ptr_str_tmr_config->enu_tmr_clk;

									//Set the interrupt configuration
									if ((ptr_str_tmr_config->enu_tmr_interrupt_state) == ENU_TMR_INT_ENABLE)
									{
										if(ptr_str_tmr_config->enu_tmr_mode == ENU_TMR_NORMAL_MODE)
										{
											SET_BIT(TIMSK,TOIE0); // normal mode
										}
										else
										{
											SET_BIT(TIMSK,OCIE0); // compare mode
										}
									}
									else
									{
										// disable timer interrupt mode
										CLEAR_BIT(TIMSK,TOIE0);
										CLEAR_BIT(TIMSK,OCIE0);
									}/*end Set the interrupt configuration*/
								
									//Set The initial value,compare value
									if ((ptr_str_tmr_config->u16_tmr_initial_value < MAX_8_BIT_COUNT) && (ptr_str_tmr_config->u16_tmr_compare_value < MAX_8_BIT_COUNT))
									{
										if(ptr_str_tmr_config->enu_tmr_mode == ENU_TMR_NORMAL_MODE)
										{
											TCNT0 = ptr_str_tmr_config->u16_tmr_initial_value;
											OCR0 = ZERO_VALUE;	
										}
										else
										{
											TCNT0 = ZERO_VALUE;
											OCR0 = ptr_str_tmr_config->u16_tmr_compare_value;
										}
									}
									else
									{
										enu_tmr_error = ENU_TMR_INVALID_INPUT;
									}/*end Set The initial value,compare value*/
								}
								else
								{
									enu_tmr_error = ENU_TMR_INVALID_CLK;
								} /*end Clock Select*/

							} //end timer_0 setup
							else if ((ptr_str_tmr_config->enu_tmr_channel_id) == ENU_TMR_CHANNEL_1) // timer_1 setup
							{
								/* Set FOC PIN as NON PWM MODE */
								SET_BIT(TCCR1A,FOC1A);
								SET_BIT(TCCR1A,FOC1B);
								/* Configure timer mode*/
								switch (ptr_str_tmr_config->enu_tmr_mode)
								{
									case ENU_TMR_NORMAL_MODE:
									{
										CLEAR_BIT(TCCR1A,WGM10);
										CLEAR_BIT(TCCR1A,WGM11);
										CLEAR_BIT(TCCR1B,WGM12);
										CLEAR_BIT(TCCR1B,WGM13);
									}
									break;
									case ENU_TMR_CMP_MODE:
									{
										CLEAR_BIT(TCCR1A,WGM10);
										CLEAR_BIT(TCCR1A,WGM11);
										SET_BIT(TCCR1B,WGM12);
										CLEAR_BIT(TCCR1B,WGM13);
									}
									break;
									default:
									{
										// to do other modes in TIMER_1
									}
								} /*end Configure timer mode*/
								
								//Configure OCA PIN Mode [to do handle OCB]
								switch (ptr_str_tmr_config->enu_tmr_cmp_mode)
								{
									case ENU_TMR_CMP_DISCONNECT:
									{
										CLEAR_BIT(TCCR1A,COM1A0);
										CLEAR_BIT(TCCR1A,COM1A1);
									}
									break;
									case ENU_TMR_CMP_TOGGLE:
									{
										SET_BIT(DDRD,PIN5);
										SET_BIT(TCCR1A,COM1A0);
										CLEAR_BIT(TCCR1A,COM1A1);
									}
									break;
									case ENU_TMR_CMP_CLEAR:
									{
										SET_BIT(DDRD,PIN5);
										CLEAR_BIT(TCCR1A,COM1A0);
										SET_BIT(TCCR1A,COM1A1);
									}
									break;
									case ENU_TMR_CMP_SET:
									{
										SET_BIT(DDRD,PIN5);
										SET_BIT(TCCR1A,COM1A0);
										SET_BIT(TCCR1A,COM1A1);
									}
									break;
									default:
									{
										//do nothing
									}
								}/*end Configure OCA PIN Mode*/
	
								/* Clock Select */
								if ((ptr_str_tmr_config->enu_tmr_clk != ENU_TMR_CLK_32) && (ptr_str_tmr_config->enu_tmr_clk != ENU_TMR_CLK_128))
								{
									//save clock setting to global variable
									gl_enu_tmr_clk[ptr_str_tmr_config->enu_tmr_channel_id] = ptr_str_tmr_config->enu_tmr_clk;
									//Set the interrupt configuration
									if ((ptr_str_tmr_config->enu_tmr_interrupt_state) == ENU_TMR_INT_ENABLE)
									{
										if(ptr_str_tmr_config->enu_tmr_mode == ENU_TMR_NORMAL_MODE)
										{
											SET_BIT(TIMSK,TOIE1);
										}
										else
										{
											SET_BIT(TIMSK,OCIE1A);
										}
									}
									else
									{
										CLEAR_BIT(TIMSK,TOIE1);
										CLEAR_BIT(TIMSK,OCIE1A); //to do handle OCB interrupt
									}/*end Set the interrupt configuration*/
										
									//Set The initial value,compare value
									if ((ptr_str_tmr_config->u16_tmr_initial_value < MAX_16_BIT_COUNT) && (ptr_str_tmr_config->u16_tmr_compare_value < MAX_16_BIT_COUNT))
									{
										if(ptr_str_tmr_config->enu_tmr_mode == ENU_TMR_NORMAL_MODE)
										{
											TCNT1 = ptr_str_tmr_config->u16_tmr_initial_value;
											OCR1A = ZERO_VALUE;	
										}
										else
										{
											TCNT1 = ZERO_VALUE;
											OCR1A = ptr_str_tmr_config->u16_tmr_compare_value;
										}
									}
									else
									{
										enu_tmr_error = ENU_TMR_INVALID_INPUT;
									}/*end Set The initial value,compare value*/			
								}
								else
								{
									enu_tmr_error = ENU_TMR_INVALID_CLK;
								} /*end Clock Select*/	
								
							}/*end timer_1 setup*/		
							else // timer_2 setup
							{
								//Set FOC PIN as NON PWM MODE
								SET_BIT(TCCR2,FOC2);
								//Configure timer mode
								switch (ptr_str_tmr_config->enu_tmr_mode)
								{
									case ENU_TMR_NORMAL_MODE:
									{
										CLEAR_BIT(TCCR2,WGM20);
										CLEAR_BIT(TCCR2,WGM21);
									}
									break;
									case ENU_TMR_CMP_MODE:
									{
										CLEAR_BIT(TCCR2,WGM20);
										SET_BIT(TCCR2,WGM21);
									}
									break;
									default:	
									{
										// do nothing
									}
								} /*end Configure timer mode*/
								//Configure OC PIN Mode
								switch (ptr_str_tmr_config->enu_tmr_cmp_mode)
								{
									case ENU_TMR_CMP_DISCONNECT:
									{
										CLEAR_BIT(TCCR2,COM20);
										CLEAR_BIT(TCCR2,COM21);
									}
									break;
									case ENU_TMR_CMP_TOGGLE:
									{
										SET_BIT(DDRD,PIN7);
										SET_BIT(TCCR2,COM20);
										CLEAR_BIT(TCCR2,COM21);
									}
									break;
									case ENU_TMR_CMP_CLEAR:
									{
										SET_BIT(DDRD,PIN7);
										CLEAR_BIT(TCCR2,COM20);
										SET_BIT(TCCR2,COM21);
									}
									break;
									case ENU_TMR_CMP_SET:
									{
										SET_BIT(DDRD,PIN7);
										SET_BIT(TCCR2,COM20);
										SET_BIT(TCCR2,COM21);
									}
									break;
									default:
									{
										//do nothing
									}
								}/*end Configure OC PIN Mode*/
								//Clock Select
								if ((ptr_str_tmr_config->enu_tmr_clk != ENU_TMR_CLK_EXT_FALLING) && (ptr_str_tmr_config->enu_tmr_clk != ENU_TMR_CLK_EXT_RISING))
								{
									//save clock setting to global variable
									gl_enu_tmr_clk[ptr_str_tmr_config->enu_tmr_channel_id] = ptr_str_tmr_config->enu_tmr_clk;
									//Set the interrupt configuration
									if ((ptr_str_tmr_config->enu_tmr_interrupt_state) == ENU_TMR_INT_ENABLE)
									{
										if(ptr_str_tmr_config->enu_tmr_mode == ENU_TMR_NORMAL_MODE)
										{
											SET_BIT(TIMSK,TOIE2);
										}
										else
										{
											SET_BIT(TIMSK,OCIE2);
										}
									}
									else
									{
										CLEAR_BIT(TIMSK,TOIE2);
										CLEAR_BIT(TIMSK,OCIE2);
									}/*end Set the interrupt configuration*/
													
									//Set The initial value,compare value
									if ((ptr_str_tmr_config->u16_tmr_initial_value < MAX_8_BIT_COUNT) && (ptr_str_tmr_config->u16_tmr_compare_value < MAX_8_BIT_COUNT))
									{
										if(ptr_str_tmr_config->enu_tmr_mode == ENU_TMR_NORMAL_MODE)
										{
											TCNT2 = ptr_str_tmr_config->u16_tmr_initial_value;
											OCR2 = ZERO_VALUE;	
										}
										else
										{
											TCNT2 = ZERO_VALUE;
											OCR2 = ptr_str_tmr_config->u16_tmr_compare_value;
										}								
									}
									else
									{
										enu_tmr_error = ENU_TMR_INVALID_INPUT;
									}/*end Set The initial value,compare value*/									
								}
								else
								{
								enu_tmr_error = ENU_TMR_INVALID_CLK;
								} /*end Clock Select*/
								
							} //end timer_2 setup
						
						}
						else
						{
							enu_tmr_error = ENU_TMR_INVALID_CLK;
						}
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_CMP_MODE;
					}
				}
				else
				{
					enu_tmr_error = ENU_TMR_INVALID_INT_STATE;
				}
			}
			else
			{
				enu_tmr_error = ENU_TMR_INVALID_MODE;
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_INVALID_ID;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_INPUT;
	}
	
	if(enu_tmr_error == ENU_TMR_VALID)
	{
		// set initialization flag for timer id, TRUE mean it is in use
		gl_bo_timer_init_flag[ptr_str_tmr_config->enu_tmr_channel_id] = TRUE;	
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_setInitialValue		: function used to set timer initial value
 */
enu_tmr_error_t timer_setInitialValue	(enu_tmr_channel_id_t enu_tmr_channel_id, uint16 u16_tmr_initial_value)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if(gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{
			switch (enu_tmr_channel_id)
			{
				case ENU_TMR_CHANNEL_0:
				{
					if (u16_tmr_initial_value < MAX_8_BIT_COUNT)
					{
						TCNT0 = u16_tmr_initial_value;
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_INPUT;
					}
				}
				break;
				case ENU_TMR_CHANNEL_1:
				{
					if (u16_tmr_initial_value < MAX_16_BIT_COUNT)
					{
						TCNT1 = u16_tmr_initial_value;
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_INPUT;
					}					
				}
				break;
				case ENU_TMR_CHANNEL_2:
				{
					if (u16_tmr_initial_value < MAX_8_BIT_COUNT)
					{
						TCNT2 = u16_tmr_initial_value;
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_INPUT;
					}
				}
				break;
				default:
				{
					// do nothing
				}
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_setCompareValue		: function used to set timer compare value
 */
enu_tmr_error_t timer_setCompareValue	(enu_tmr_channel_id_t enu_tmr_channel_id, uint16 u16_tmr_compare_value)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if(gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{
			switch (enu_tmr_channel_id)
			{
				case ENU_TMR_CHANNEL_0:
				{
					if (u16_tmr_compare_value < MAX_8_BIT_COUNT)
					{
						OCR0 = u16_tmr_compare_value;
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_INPUT;
					}
				}
				break;
				case ENU_TMR_CHANNEL_1:
				{
					if (u16_tmr_compare_value < MAX_16_BIT_COUNT)
					{
						OCR1A = u16_tmr_compare_value;
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_INPUT;
					}
				}
				break;
				case ENU_TMR_CHANNEL_2:
				{
					if (u16_tmr_compare_value < MAX_8_BIT_COUNT)
					{
						OCR2 = u16_tmr_compare_value;
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_INPUT;
					}
				}
				break;
				default:
				{
					// do nothing
				}
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_setClock				: function used to set timer clock source
 */
enu_tmr_error_t timer_setClock	(enu_tmr_channel_id_t enu_tmr_channel_id, enu_tmr_clk_t enu_tmr_clk)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if(gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{
			if(enu_tmr_clk < ENU_TMR_MAX_CLK)
			{
				switch(enu_tmr_channel_id)
				{
					case  ENU_TMR_CHANNEL_0:
					{
						if((enu_tmr_clk != ENU_TMR_CLK_32) && (enu_tmr_clk != ENU_TMR_CLK_128))
						{
							gl_enu_tmr_clk[enu_tmr_channel_id] = enu_tmr_clk;
						}
						else
						{
							enu_tmr_error = ENU_TMR_INVALID_CLK;
						}
					}
					break;
					case ENU_TMR_CHANNEL_1:
					{
						if((enu_tmr_clk != ENU_TMR_CLK_32) && (enu_tmr_clk != ENU_TMR_CLK_128))
						{
							gl_enu_tmr_clk[enu_tmr_channel_id] = enu_tmr_clk;
						}
						else
						{
							enu_tmr_error = ENU_TMR_INVALID_CLK;
						}
					}
					break;
					case ENU_TMR_CHANNEL_2:
					{
						if((enu_tmr_clk != ENU_TMR_CLK_EXT_FALLING) && (enu_tmr_clk != ENU_TMR_CLK_EXT_RISING))
						{
							gl_enu_tmr_clk[enu_tmr_channel_id] = enu_tmr_clk;
						}
						else
						{
							enu_tmr_error = ENU_TMR_INVALID_CLK;
						}
					}
					break;
					default:
					{
						// do nothing
					}
				}
			}
			else
			{
				enu_tmr_error = ENU_TMR_INVALID_CLK;
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_setCallBack			: function used to set timer callback function 
 */
enu_tmr_error_t timer_setCallBack	(enu_tmr_channel_id_t enu_tmr_channel_id , volatile void (*f_ptr) (void) , enu_tmr_mode_t enu_tmr_mode)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if(enu_tmr_mode < ENU_MAX_TMR_MODE)
		{
			if(f_ptr != NULL_PTR)
			{
				switch(enu_tmr_channel_id)
				{
					case ENU_TMR_CHANNEL_0:
					{
						if (enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							gl_callBackPtr_timer0_OVF = f_ptr;
						}
						else if(enu_tmr_mode == ENU_TMR_CMP_MODE)
						{
							gl_callBackPtr_timer0_COMP = f_ptr;
						}
						else
						{
							// do nothing
						}
					}
					break;
					case ENU_TMR_CHANNEL_1:
					{
						if (enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							gl_callBackPtr_timer1_OVF = f_ptr;
						}
						else if(enu_tmr_mode == ENU_TMR_CMP_MODE)
						{
							gl_callBackPtr_timer1_COMP = f_ptr;
						}
						else
						{
							// do nothing
						}
					}
					break;
					case ENU_TMR_CHANNEL_2:
					{
						if (enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							gl_callBackPtr_timer2_OVF = f_ptr;
						}
						else if(enu_tmr_mode == ENU_TMR_CMP_MODE)
						{
							gl_callBackPtr_timer2_COMP = f_ptr;
						}
						else
						{
							// do nothing
						}
					}
					break;
					default: 
					{
						// do nothing
					}
				}
			}
			else
			{
				enu_tmr_error = ENU_TMR_INVALID_INPUT;
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_INVALID_MODE;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_start					: function used to start the timer to count
 */
enu_tmr_error_t timer_start	(enu_tmr_channel_id_t enu_tmr_channel_id)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if (enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if(gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{		
			switch (enu_tmr_channel_id)
			{
				case ENU_TMR_CHANNEL_0:
				{
					if( (gl_enu_tmr_clk[ENU_TMR_CHANNEL_0] < ENU_TMR_MAX_CLK) && (gl_enu_tmr_clk[ENU_TMR_CHANNEL_0] != ENU_TMR_CLK_32) && (gl_enu_tmr_clk[ENU_TMR_CHANNEL_0] != ENU_TMR_CLK_128) )
					{
						switch (gl_enu_tmr_clk[ENU_TMR_CHANNEL_0])
						{
							case ENU_TMR_NO_CLK:			TCCR0 = (TCCR0 & CLK_MASK_BIT) | (ZERO_VALUE);							break;
							case ENU_TMR_CLK_1:				TCCR0 = (TCCR0 & CLK_MASK_BIT) | (1<<CS00);								break;
							case ENU_TMR_CLK_8:				TCCR0 = (TCCR0 & CLK_MASK_BIT) | (1<<CS01);								break;
							case ENU_TMR_CLK_64:			TCCR0 = (TCCR0 & CLK_MASK_BIT) | (1<<CS01)| (1<<CS00);					break;
							case ENU_TMR_CLK_256:			TCCR0 = (TCCR0 & CLK_MASK_BIT) | (1<<CS02);								break;
							case ENU_TMR_CLK_1024:			TCCR0 = (TCCR0 & CLK_MASK_BIT) | (1<<CS02)| (1<<CS00);					break;
							case ENU_TMR_CLK_EXT_FALLING:	TCCR0 = (TCCR0 & CLK_MASK_BIT) | (1<<CS02)| (1<<CS01);					break;
							case ENU_TMR_CLK_EXT_RISING:	TCCR0 = (TCCR0 & CLK_MASK_BIT) | (1<<CS02)| (1<<CS01)| (1<<CS00);		break;
							default: 
							{
								// do nothing
							}
						}
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_CLK;
					}
				}
				break;
				case ENU_TMR_CHANNEL_1:
				{
					if( (gl_enu_tmr_clk[ENU_TMR_CHANNEL_1] < ENU_TMR_MAX_CLK) && (gl_enu_tmr_clk[ENU_TMR_CHANNEL_1] != ENU_TMR_CLK_32) && (gl_enu_tmr_clk[ENU_TMR_CHANNEL_1] != ENU_TMR_CLK_128) )
					{
						switch (gl_enu_tmr_clk[ENU_TMR_CHANNEL_1])
						{
							case ENU_TMR_NO_CLK:			TCCR1B = (TCCR1B & CLK_MASK_BIT) | ZERO_VALUE;						break;
							case ENU_TMR_CLK_1:				TCCR1B = (TCCR1B & CLK_MASK_BIT) |(1<<CS10);						break;
							case ENU_TMR_CLK_8:				TCCR1B = (TCCR1B & CLK_MASK_BIT) |(1<<CS11);						break;
							case ENU_TMR_CLK_64:			TCCR1B = (TCCR1B & CLK_MASK_BIT) |(1<<CS11)| (1<<CS10);				break;
							case ENU_TMR_CLK_256:			TCCR1B = (TCCR1B & CLK_MASK_BIT) |(1<<CS12);						break;
							case ENU_TMR_CLK_1024:			TCCR1B = (TCCR1B & CLK_MASK_BIT) |(1<<CS12)| (1<<CS10);				break;
							case ENU_TMR_CLK_EXT_FALLING:	TCCR1B = (TCCR1B & CLK_MASK_BIT) |(1<<CS12)| (1<<CS11);				break;
							case ENU_TMR_CLK_EXT_RISING:	TCCR1B = (TCCR1B & CLK_MASK_BIT) |(1<<CS12)| (1<<CS11)| (1<<CS10);	break;
							default: 
							{
								// do nothing
							}
						}
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_CLK;
					}
				}
				break;
				case ENU_TMR_CHANNEL_2:
				{
					if( (gl_enu_tmr_clk[ENU_TMR_CHANNEL_2] < ENU_TMR_MAX_CLK) && (gl_enu_tmr_clk[ENU_TMR_CHANNEL_2] != ENU_TMR_CLK_EXT_RISING) && (gl_enu_tmr_clk[ENU_TMR_CHANNEL_2] != ENU_TMR_CLK_EXT_FALLING) )
					{
						switch (gl_enu_tmr_clk[ENU_TMR_CHANNEL_2])
						{
							case ENU_TMR_NO_CLK:			TCCR2 = (TCCR2 & CLK_MASK_BIT) |ZERO_VALUE;							break;
							case ENU_TMR_CLK_1:				TCCR2 = (TCCR2 & CLK_MASK_BIT) |(1<<CS20);							break;
							case ENU_TMR_CLK_8:				TCCR2 = (TCCR2 & CLK_MASK_BIT) |(1<<CS21);							break;
							case ENU_TMR_CLK_32:			TCCR2 = (TCCR2 & CLK_MASK_BIT) |(1<<CS21)| (1<<CS20);				break;
							case ENU_TMR_CLK_64:			TCCR2 = (TCCR2 & CLK_MASK_BIT) |(1<<CS22);							break;
							case ENU_TMR_CLK_128:			TCCR2 = (TCCR2 & CLK_MASK_BIT) |(1<<CS22)| (1<<CS20);				break;
							case ENU_TMR_CLK_256:			TCCR2 = (TCCR2 & CLK_MASK_BIT) |(1<<CS22)| (1<<CS21);				break;
							case ENU_TMR_CLK_1024:			TCCR2 = (TCCR2 & CLK_MASK_BIT) |(1<<CS22) | (1<<CS21)| (1<<CS20);	break;
							default:
							{
								//do nothing
							}
						}
					}
					else
					{
						enu_tmr_error = ENU_TMR_INVALID_CLK;
					}
				}
				break;
				default: 
				{
					// do nothing
				}
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;	
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_stop					: function used to stop the timer 
 */
enu_tmr_error_t timer_stop	(enu_tmr_channel_id_t enu_tmr_channel_id)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if (gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{
			switch(enu_tmr_channel_id)
			{
				case ENU_TMR_CHANNEL_0:		TCCR0  = (TCCR0 & CLK_MASK_BIT) | ZERO_VALUE;		break;
				case ENU_TMR_CHANNEL_1:		TCCR1B = (TCCR1B & CLK_MASK_BIT)| ZERO_VALUE;		break;
				case ENU_TMR_CHANNEL_2:		TCCR2  = (TCCR2 & CLK_MASK_BIT) | ZERO_VALUE;		break;
				default: 
				{
					// do nothing
				}
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_getValue				: function used to read timer value
 */
enu_tmr_error_t timer_getValue	(enu_tmr_channel_id_t enu_tmr_channel_id , uint16* ptr_u16_tmr_value)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if (gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{
			switch(enu_tmr_channel_id)
			{
				case ENU_TMR_CHANNEL_0:		*ptr_u16_tmr_value = TCNT0;		break;
				case ENU_TMR_CHANNEL_1:		*ptr_u16_tmr_value = TCNT1;		break;
				case ENU_TMR_CHANNEL_2:		*ptr_u16_tmr_value = TCNT2;		break;
				default:
				{ 
					//do nothing
				}
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_enableNotification	: function used to enable timer interrupt source
 */
enu_tmr_error_t timer_enableInterrupt	(enu_tmr_channel_id_t enu_tmr_channel_id,enu_tmr_mode_t enu_tmr_mode)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if (gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{
			if (enu_tmr_mode < ENU_MAX_TMR_MODE)
			{
				switch(enu_tmr_channel_id)
				{
					case ENU_TMR_CHANNEL_0:
					{
						if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							SET_BIT(TIMSK,TOIE0);
						}
						else
						{
							SET_BIT(TIMSK,OCIE0);
						}
					}
					break;
					case ENU_TMR_CHANNEL_1:
					{
						if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							SET_BIT(TIMSK,TOIE1);
						}
						else
						{
							SET_BIT(TIMSK,OCIE1A);
						}
					}
					break;
					case ENU_TMR_CHANNEL_2:
					{
						if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							SET_BIT(TIMSK,TOIE2);
						}
						else
						{
							SET_BIT(TIMSK,OCIE2);
						}	
					}
					break;
					default: 
					{
						// do nothing
					}
				}
			}
			else
			{
				enu_tmr_error = ENU_TMR_INVALID_MODE;
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_disableNotification	: function used to disable timer interrupt source
 */
enu_tmr_error_t timer_disableInterrupt	(enu_tmr_channel_id_t enu_tmr_channel_id,enu_tmr_mode_t enu_tmr_mode)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if (gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
		{
			if (enu_tmr_mode < ENU_MAX_TMR_MODE)
			{
				switch(enu_tmr_channel_id)
				{
					case ENU_TMR_CHANNEL_0:
					{
						if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							CLEAR_BIT(TIMSK,TOIE0);
						}
						else
						{
							CLEAR_BIT(TIMSK,OCIE0);
						}
					}
					break;
					case ENU_TMR_CHANNEL_1:
					{
						if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							CLEAR_BIT(TIMSK,TOIE1);
						}
						else
						{
							CLEAR_BIT(TIMSK,OCIE1A);
						}
					}
					break;
					case ENU_TMR_CHANNEL_2:
					{
						if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
						{
							CLEAR_BIT(TIMSK,TOIE2);
						}
						else
						{
							CLEAR_BIT(TIMSK,OCIE2);
						}	
					}
					break;
					default:
					{
						// do nothing
					}
				}
			}
			else
			{
				enu_tmr_error = ENU_TMR_INVALID_MODE;
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_getStatus				: function used to get timer state if it is [ready - busy]
 */
enu_tmr_error_t timer_getStatus	(enu_tmr_channel_id_t enu_tmr_channel_id,uint8* ptr_u8_tmr_state)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if (enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if(ptr_u8_tmr_state != NULL_PTR)
		{
			*ptr_u8_tmr_state = (uint8) gl_bo_timer_init_flag[enu_tmr_channel_id];
		}
		else
		{
			enu_tmr_error = ENU_TMR_INVALID_INPUT;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/**
 * @brief       timer_deInit				: function used to clear timer initialization
 */
enu_tmr_error_t timer_deInit	(enu_tmr_channel_id_t enu_tmr_channel_id)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		switch (enu_tmr_channel_id)
		{
			case ENU_TMR_CHANNEL_0:
			{
				TCCR0=ZERO_VALUE;
				TCNT0=ZERO_VALUE;
				OCR0 =ZERO_VALUE;
				CLEAR_BIT(TIMSK,TOIE0);
				CLEAR_BIT(TIMSK,OCIE0);
			}
			break;
			case ENU_TMR_CHANNEL_1:
			{
				TCCR1B=ZERO_VALUE;
				TCCR1A=ZERO_VALUE;
				TCNT1 =ZERO_VALUE;
				OCR1A =ZERO_VALUE;
				CLEAR_BIT(TIMSK,TOIE1);
				CLEAR_BIT(TIMSK,OCIE1A);	
			}
			break;
			case ENU_TMR_CHANNEL_2:
			{
				TCCR2=ZERO_VALUE;
				TCNT2=ZERO_VALUE;
				OCR2 =ZERO_VALUE;
				CLEAR_BIT(TIMSK,TOIE2);
				CLEAR_BIT(TIMSK,OCIE2);
			}
			break;
			default:
			{
				// do nothing
			}
		}
		gl_bo_timer_init_flag[enu_tmr_channel_id] = FALSE;	// the timer_id is ready for another use
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return ENU_TMR_INVALID_ID;
}


/**
 * @brief       timer_flag_notification		: function used to notify the upper layer when interrupt happen
 *											  if [*ptr_u8_flag_status] = TRUE  >>> the interrupt happen then cleared
 *											  if [*ptr_u8_flag_status] = FLASE >>> the interrupt does not happen
 */
enu_tmr_error_t timer_flag_notification	(enu_tmr_channel_id_t enu_tmr_channel_id,enu_tmr_mode_t enu_tmr_mode,uint8* ptr_u8_flag_status)
{
	enu_tmr_error_t enu_tmr_error = ENU_TMR_VALID;
	if(enu_tmr_channel_id < MAX_ENU_TMR_CHANNEL)
	{
		if(enu_tmr_mode < ENU_MAX_TMR_MODE)
		{
			if(ptr_u8_flag_status != NULL_PTR)
			{
				if(gl_bo_timer_init_flag[enu_tmr_channel_id] == TRUE)
				{
					switch (enu_tmr_channel_id)
					{
						case ENU_TMR_CHANNEL_0:
						{
							if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
							{
								if(BIT_IS_SET(TIFR,TOV0) == LOGIC_TRUE)
								{
									*ptr_u8_flag_status = LOGIC_TRUE;
									SET_BIT(TIFR,TOV0);	//TOV0 is cleared by writing a logic one to the flag
								}
								else
								{
									*ptr_u8_flag_status = LOGIC_FALSE;
								}
							}
							else
							{
								if(BIT_IS_SET(TIFR,OCF0) == LOGIC_TRUE)	// in case compare flag
								{
									*ptr_u8_flag_status = LOGIC_TRUE;
									SET_BIT(TIFR,OCF0);	//OCF0 is cleared by writing a logic one to the flag
								}
								else
								{
									*ptr_u8_flag_status = LOGIC_FALSE;
								}
							}
						}
						break;
						case ENU_TMR_CHANNEL_1:
						{
							if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
							{
								if(BIT_IS_SET(TIFR,TOV1) == LOGIC_TRUE)
								{
									*ptr_u8_flag_status = LOGIC_TRUE;
									SET_BIT(TIFR,TOV1);	//TOV1 is cleared by writing a logic one to the flag
								}
								else
								{
									*ptr_u8_flag_status = LOGIC_FALSE;
								}
							}
							else
							{
								if(BIT_IS_SET(TIFR,OCF1A) == LOGIC_TRUE)
								{
									*ptr_u8_flag_status = LOGIC_TRUE;
									SET_BIT(TIFR,OCF1A);	//OCF1A is cleared by writing a logic one to the flag
								}
								else
								{
									*ptr_u8_flag_status = LOGIC_FALSE;
								}
							}
						}
						break;
						case ENU_TMR_CHANNEL_2:
						{
							if(enu_tmr_mode == ENU_TMR_NORMAL_MODE)
							{
								if(BIT_IS_SET(TIFR,TOV2) == LOGIC_TRUE)
								{
									*ptr_u8_flag_status = LOGIC_TRUE;
									SET_BIT(TIFR,TOV2);	//TOV2 is cleared by writing a logic one to the flag
								}
								else
								{
									*ptr_u8_flag_status = LOGIC_FALSE;
								}
							}
							else
							{
								if(BIT_IS_SET(TIFR,OCF2) == LOGIC_TRUE)
								{
									*ptr_u8_flag_status = LOGIC_TRUE;
									SET_BIT(TIFR,OCF2);	//OCF2 is cleared by writing a logic one to the flag
								}
								else
								{
									*ptr_u8_flag_status = LOGIC_FALSE;
								}
							}
						}
						break;
						default:
						{
							// do nothing
						}
					}
				}
				else
				{
					enu_tmr_error = ENU_TMR_NOT_INITIALIZED;
				}
			}
			else
			{
				enu_tmr_error = ENU_TMR_INVALID_INPUT;
			}
		}
		else
		{
			enu_tmr_error = ENU_TMR_INVALID_MODE;
		}
	}
	else
	{
		enu_tmr_error = ENU_TMR_INVALID_ID;
	}
	return enu_tmr_error;
}

/*===============ISR HANDLERS================*/
/* Interrupt Service Routine for TIMER0 Overflow Mode */
ISR_HANDLER(TMR0_OVF)
{
	if(gl_callBackPtr_timer0_OVF != NULL_PTR)
	{
		gl_callBackPtr_timer0_OVF();
	}
}

/* Interrupt Service Routine for TIMER1 Overflow Mode */
ISR_HANDLER(TMR1_OVF)
{
	if(gl_callBackPtr_timer1_OVF != NULL_PTR)
	{
		gl_callBackPtr_timer1_OVF();
	}
}

/* Interrupt Service Routine for TIMER2 Overflow Mode */
ISR_HANDLER(TMR2_OVF)
{
	if(gl_callBackPtr_timer2_OVF != NULL_PTR)
	{
		gl_callBackPtr_timer2_OVF();
	}
}
/* Interrupt Service Routine for TIMER0 Overflow Mode */
ISR_HANDLER(TMR0_CMP)
{
	if(gl_callBackPtr_timer0_COMP != NULL_PTR)
	{
		gl_callBackPtr_timer0_COMP();
	}
}

/* Interrupt Service Routine for TIMER1 Overflow Mode */
ISR_HANDLER(TMR1_CMP_A)
{
	if(gl_callBackPtr_timer1_COMP != NULL_PTR)
	{
		gl_callBackPtr_timer1_COMP();
	}
}

/* Interrupt Service Routine for TIMER2 Overflow Mode */
ISR_HANDLER(TMR2_CMP)
{
	if(gl_callBackPtr_timer2_COMP != NULL_PTR)
	{
		gl_callBackPtr_timer2_COMP(); 
	}
}