/*
 * app.c
 *
 * Created: 2023-07-26 9:27:03 PM
 *  Author: HAZEM-PC
 */ 

/*=========FILE INCLUSION=========*/
#include "app.h"
#include "util/delay.h"
/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/
enu_car_direction_t gl_enu_car_direction			= ENU_FWD_DIR;
enu_car_direction_t gl_enu_car_rotation_direction	= ENU_RHT_DIR;
enu_car_power_t		gl_enu_car_power				= ENU_CAR_POWER_OFF;
uint8				gl_u8_carSpeed					= LOGIC_LOW;
uint16				gl_u16_obsDistance				= LOGIC_LOW;

str_dcMotor_config_t str_dcMotor_RUP_motor = {
	.positive_terminal.port_id	= RIGHT_UP_WHEEL_PORT,
	.positive_terminal.pin_id	= RIGHT_UP_WHEEL_POSITIVE_PIN,
	.negative_terminal.port_id	= RIGHT_UP_WHEEL_PORT,
	.negative_terminal.pin_id	= RIGHT_UP_WHEEL_NEGATIVE_PIN,
	.enable_terminal.port_id	= DC_MOTOR_ENABLE_PORT,
	.enable_terminal.pin_id		= DC_MOTOR_ENABLE_PIN	
};

str_dcMotor_config_t str_dcMotor_RDW_motor = {
	.positive_terminal.port_id	= RIGHT_DOWN_WHEEL_PORT,
	.positive_terminal.pin_id	= RIGHT_DOWN_WHEEL_POSITIVE_PIN,
	.negative_terminal.port_id	= RIGHT_DOWN_WHEEL_PORT,
	.negative_terminal.pin_id	= RIGHT_DOWN_WHEEL_NEGATIVE_PIN,
	.enable_terminal.port_id	= DC_MOTOR_ENABLE_PORT,
	.enable_terminal.pin_id		= DC_MOTOR_ENABLE_PIN
};

str_dcMotor_config_t str_dcMotor_LUP_motor = {
	.positive_terminal.port_id	= LEFT_UP_WHEEL_PORT,
	.positive_terminal.pin_id	= LEFT_UP_WHEEL_POSITIVE_PIN,
	.negative_terminal.port_id	= LEFT_UP_WHEEL_PORT,
	.negative_terminal.pin_id	= LEFT_UP_WHEEL_NEGATIVE_PIN,
	.enable_terminal.port_id	= DC_MOTOR_ENABLE_PORT,
	.enable_terminal.pin_id		= DC_MOTOR_ENABLE_PIN
};

str_dcMotor_config_t str_dcMotor_LDW_motor = {
	.positive_terminal.port_id	= LEFT_DOWN_WHEEL_PORT,
	.positive_terminal.pin_id	= LEFT_DOWN_WHEEL_POSITIVE_PIN,
	.negative_terminal.port_id	= LEFT_DOWN_WHEEL_PORT,
	.negative_terminal.pin_id	= LEFT_DOWN_WHEEL_NEGATIVE_PIN,
	.enable_terminal.port_id	= DC_MOTOR_ENABLE_PORT,
	.enable_terminal.pin_id		= DC_MOTOR_ENABLE_PIN
};


/*=========TYPE DEFINITIONS=========*/

/*=========APIs DECLERATIONS=========*/
void app_init(void)
{
	enable_global_interrupt();
	LCD_init();
	button_init(DIRECTION_BUTTON_PORT,DIRECTION_BUTTON_PIN);
	Init_external_interrupt(START_BUTTON_ID,ENU_RISING);
	Init_external_interrupt(STOP_BUTTON_ID,ENU_RISING);
	interrupt0_set_callback(car_powerOff);
	interrupt1_set_callback(car_powerOn);
	Ultrasonic_init(ULTRASONIC_PORT,ULTRASONIC_TRIGGER_PIN,ULTRASONIC_ECHO_PIN);
	dcMotor_init(&str_dcMotor_RUP_motor);
	dcMotor_init(&str_dcMotor_RDW_motor);
	dcMotor_init(&str_dcMotor_LUP_motor);
	dcMotor_init(&str_dcMotor_LDW_motor);
	car_welcome_screen();
	enable_external_interrupt(START_BUTTON_ID);
	enable_external_interrupt(STOP_BUTTON_ID);
}

void car_directionInit()
{
	uint8 value				= LOGIC_LOW;
	uint8 u8_direction		= LOGIC_LOW;
	uint8 u8_l_timeout_flag = LOGIC_LOW;

	//update_screen(gl_u16_obsDistance);
	car_updtae_screen(ENU_PAGE_INIT,LOGIC_LOW,LOGIC_LOW,LOGIC_LOW);
	//car_initialization_screen();
	timeOut_sec(TIMEOUT_TIMER_ID,DIRECTION_TIMEOUT_SEC);
	timer_check_time_out_flag(TIMEOUT_TIMER_ID,&u8_l_timeout_flag);
	while(u8_l_timeout_flag != TRUE )
	{
		timer_check_time_out_flag(TIMEOUT_TIMER_ID,&u8_l_timeout_flag);
		button_read(DIRECTION_BUTTON_PORT,DIRECTION_BUTTON_PIN,&value);
		if(value == TRUE)
		{
			u8_direction ^= LOGIC_ONE;
		}
		
		if(u8_direction == TRUE)
		{
			gl_enu_car_rotation_direction = ENU_LFT_DIR;
		}
		else
		{
			gl_enu_car_rotation_direction = ENU_RHT_DIR;
		}
		gl_enu_car_direction = gl_enu_car_rotation_direction;
		car_updtae_screen(ENU_PAGE_INIT,LOGIC_LOW,LOGIC_LOW,gl_enu_car_direction);
	}
}

void robot_control (str_dcMotor_config_t* str_dcMotor_1, str_dcMotor_config_t* str_dcMotor_2, str_dcMotor_config_t* str_dcMotor_3, str_dcMotor_config_t* str_dcMotor_4,enu_car_direction_t enu_car_direction ,uint8 u8_car_speed)
{
	if (enu_car_direction == ENU_FWD_DIR)
	{
		dcMotor_rotate(str_dcMotor_1,ENU_DCMOTOR_CW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_2,ENU_DCMOTOR_CW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_3,ENU_DCMOTOR_CW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_4,ENU_DCMOTOR_CW,u8_car_speed);
	}
	else if(enu_car_direction == ENU_BWD_DIR)
	{
		dcMotor_rotate(str_dcMotor_1,ENU_DCMOTOR_ACW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_2,ENU_DCMOTOR_ACW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_3,ENU_DCMOTOR_ACW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_4,ENU_DCMOTOR_ACW,u8_car_speed);
	}
	else if(enu_car_direction == ENU_LFT_DIR)
	{
		dcMotor_rotate(str_dcMotor_1,ENU_DCMOTOR_ACW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_2,ENU_DCMOTOR_CW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_3,ENU_DCMOTOR_CW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_4,ENU_DCMOTOR_ACW,u8_car_speed);
	}
	else if(enu_car_direction == ENU_RHT_DIR)
	{
		dcMotor_rotate(str_dcMotor_1,ENU_DCMOTOR_CW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_2,ENU_DCMOTOR_ACW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_3,ENU_DCMOTOR_ACW,u8_car_speed);
		dcMotor_rotate(str_dcMotor_4,ENU_DCMOTOR_CW,u8_car_speed);
	}
	else if(enu_car_direction == ENU_STOP)
	{
		dcMotor_stop(str_dcMotor_1);
		dcMotor_stop(str_dcMotor_2);
		dcMotor_stop(str_dcMotor_3);
		dcMotor_stop(str_dcMotor_4);
	}
	else
	{
		//do nothing
	}
}

enu_carEvents_t read_event (uint16* ptr_u16_distance)
{
	enu_carEvents_t enu_carEvents				= ENU_MAX_EV;
	static BOOLEAN st_bo_l_event_flag			= FALSE;
	static BOOLEAN st_bo_l_timeout_active_flag	= FALSE;				//to control timeout function calling
	static uint8   st_u8_l_roatation_counter	= LOGIC_LOW;			//to count number of car rotations
	uint8 u8_l_timeout_state					= LOGIC_LOW;	
	Ultrasonic_readDistance(ptr_u16_distance);
	
		if(gl_enu_car_power == ENU_CAR_POWER_ON)
		{
			enu_carEvents				= ENU_EV8;
			st_bo_l_event_flag			= FALSE;
			st_bo_l_timeout_active_flag	= FALSE;
			gl_enu_car_power			= ENU_CAR_POWER_STABLE;
		}
		else if(gl_enu_car_power == ENU_CAR_POWER_OFF)
		{
			enu_carEvents				= ENU_EV7;		//hard stop
			st_bo_l_event_flag			= FALSE;
			st_bo_l_timeout_active_flag	= FALSE;
		}
		else if((*ptr_u16_distance >= _70_CM) && (st_bo_l_event_flag == FALSE))
		{
			enu_carEvents				= ENU_EV1;
			st_u8_l_roatation_counter	= LOGIC_LOW;
			
			if(st_bo_l_timeout_active_flag == FALSE)
			{
				timeOut_sec(TIMEOUT_TIMER_ID,DISTANCE_TIMEOUT_SEC);
				st_bo_l_timeout_active_flag = TRUE;
			}
			timer_check_time_out_flag(TIMEOUT_TIMER_ID,&u8_l_timeout_state);
			if(u8_l_timeout_state == TRUE)
			{
				enu_carEvents		= ENU_EV6;
				st_bo_l_event_flag	= TRUE;
			}
		}
		else if((*ptr_u16_distance >= _70_CM) && (st_bo_l_event_flag == TRUE))
		{
			enu_carEvents				= ENU_EV6;
			st_u8_l_roatation_counter	= LOGIC_LOW;
			st_bo_l_timeout_active_flag	= FALSE;
		}
		else if((*ptr_u16_distance >= _30_CM) && (*ptr_u16_distance < _70_CM))
		{
			enu_carEvents				= ENU_EV2;
			st_bo_l_timeout_active_flag	= FALSE;
			st_u8_l_roatation_counter	= LOGIC_LOW;
			st_bo_l_event_flag			= FALSE;
		}
		else if((*ptr_u16_distance >= _20_CM) && (*ptr_u16_distance < _30_CM))
		{
			enu_carEvents				= ENU_EV3;
			st_bo_l_timeout_active_flag	= FALSE;
			st_bo_l_event_flag			= FALSE;
			st_u8_l_roatation_counter++;
			if(st_u8_l_roatation_counter == NUMBER_OF_ROTATIONS)		//car rotate 360 degree sequentially
			{
				enu_carEvents = ENU_EV5;
				st_u8_l_roatation_counter = LOGIC_LOW;	
			}
		}
		else if(*ptr_u16_distance < _20_CM)
		{
			enu_carEvents				= ENU_EV4;
			st_bo_l_event_flag			= FALSE;
			st_u8_l_roatation_counter	= LOGIC_LOW;
			st_bo_l_timeout_active_flag	= FALSE;
		}
		else
		{
			enu_carEvents				= ENU_MAX_EV;
			st_bo_l_event_flag			= FALSE;
			st_u8_l_roatation_counter	= LOGIC_LOW;
			st_bo_l_timeout_active_flag	= FALSE;
		}
	
	if(gl_enu_car_power == ENU_CAR_POWER_OFF)
	{
		enu_carEvents = ENU_EV7;		//hard stop 
	}
	return enu_carEvents;
}

void display_event (enu_carEvents_t enu_carEvents,uint16 distance)
{
	LCD_clearScreen();
	switch(enu_carEvents)
	{
		case ENU_EV1:
		{
			LCD_displayString("dist>70,sp=30%");
		}
		break;
		case ENU_EV2:
		{
			LCD_displayString("70>distance>30");
		}
		break;
		case ENU_EV3:
		{
			LCD_displayString("30>distance>20");
		}
		break;
		case ENU_EV4:
		{
			LCD_displayString("distance<20");
		}
		break;
		case ENU_EV5:
		{
			LCD_displayString("STOP");
		}
		break;
		case ENU_EV6:
		{
			LCD_displayString("dist>70,sp=50%");
		}
		break;
		case ENU_EV7:
		{
			LCD_displayString("HARD STOP");
		}
		break;
		case ENU_EV8:
		{
			LCD_displayString("START EVENT");
		}
		break;
		default:
		{
			//do nothing
		}
		break;
	}
	LCD_displayStringRowColumn(1,0,"Dis= ");
	LCD_moveCursor(1,4);
	LCD_intgerToString(distance);
}

void car_powerOn (void)
{
	if(gl_enu_car_power != ENU_CAR_POWER_STABLE)
		gl_enu_car_power = ENU_CAR_POWER_ON;
}

void car_powerOff (void)
{
	gl_enu_car_power = ENU_CAR_POWER_OFF;
}

void car_action (enu_carStates_t enu_carStates,uint8* u8_carSpeed,enu_car_direction_t* enu_car_direction)
{
	if(enu_carStates == ENU_FWD_30)
	{
		robot_control ( &str_dcMotor_RUP_motor,
						&str_dcMotor_RDW_motor,
						&str_dcMotor_LUP_motor,
						&str_dcMotor_LDW_motor,
						ENU_FWD_DIR,
						SPEED_30_PERCENT);
		*u8_carSpeed		= SPEED_30_PERCENT;
		*enu_car_direction	= ENU_FWD_DIR;
	}
	else if(enu_carStates == ENU_FWD_50)
	{
			robot_control ( &str_dcMotor_RUP_motor,
							&str_dcMotor_RDW_motor,
							&str_dcMotor_LUP_motor,
							&str_dcMotor_LDW_motor,
							ENU_FWD_DIR,
							SPEED_50_PERCENT);
		*u8_carSpeed		= SPEED_50_PERCENT;
		*enu_car_direction	= ENU_FWD_DIR;
	}
	else if(enu_carStates == ENU_BWD_30)
	{
			robot_control ( &str_dcMotor_RUP_motor,
							&str_dcMotor_RDW_motor,
							&str_dcMotor_LUP_motor,
							&str_dcMotor_LDW_motor,
							ENU_BWD_DIR,
							SPEED_30_PERCENT);	
		*u8_carSpeed		= SPEED_30_PERCENT;
		*enu_car_direction	= ENU_BWD_DIR;
	}
	else if(enu_carStates == ENU_ROT_90)
	{
			robot_control ( &str_dcMotor_RUP_motor,
							&str_dcMotor_RDW_motor,
							&str_dcMotor_LUP_motor,
							&str_dcMotor_LDW_motor,
							gl_enu_car_rotation_direction,
							SPEED_10_PERCENT);
			delay_ms(DELAY_TIMER_ID,1500);
			robot_control ( &str_dcMotor_RUP_motor,
							&str_dcMotor_RDW_motor,
							&str_dcMotor_LUP_motor,
							&str_dcMotor_LDW_motor,
							ENU_STOP,
							SPEED_0_PERCENT);
			delay_ms(DELAY_TIMER_ID,1500);
		*u8_carSpeed			= SPEED_10_PERCENT;
		*enu_car_direction		= gl_enu_car_rotation_direction;				
	}
	else if(enu_carStates == ENU_STOP_3_SEC)
	{
		*u8_carSpeed			= SPEED_0_PERCENT;
		*enu_car_direction		= ENU_STOP;
		car_updtae_screen(ENU_PAGE_MSG_2,LOGIC_LOW,*u8_carSpeed,*enu_car_direction);
		delay_sec(DELAY_TIMER_ID,3);
	}
	else if(enu_carStates == ENU_PWR_OFF)
	{
		robot_control ( &str_dcMotor_RUP_motor,
						&str_dcMotor_RDW_motor,
						&str_dcMotor_LUP_motor,
						&str_dcMotor_LDW_motor,
						ENU_STOP,
						SPEED_0_PERCENT);
		*u8_carSpeed		= SPEED_0_PERCENT;
		*enu_car_direction	= ENU_STOP;
		car_updtae_screen(ENU_PAGE_MSG_1,LOGIC_LOW,*u8_carSpeed,*enu_car_direction);
	}
	else if(enu_carStates == ENU_PWR_ON)
	{
		car_directionInit();
		delay_sec(DELAY_TIMER_ID,WAIT_TIME_SEC);
		*u8_carSpeed		= SPEED_0_PERCENT;
		*enu_car_direction	= ENU_FWD_DIR;
	}
	else
	{
		//do nothing
	}
	
}

enu_carStates_t car_stateMachine (enu_carEvents_t enu_carEvents)
{
	static enu_carStates_t	st_enu_carStates	= ENU_PWR_OFF;
	static enu_carEvents_t	st_enu_carEvents	= ENU_MAX_EV;		//used to check whether the event change or not
	if(enu_carEvents != st_enu_carEvents)
	{
		st_enu_carEvents = enu_carEvents;
		switch(st_enu_carStates)
		{
			case ENU_FWD_30:
			{
				switch(enu_carEvents)
				{
					case ENU_EV1:		// distance > 70
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV2:		// 70 > distance > 30
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV3:		// 30 > distance > 20
					{
						st_enu_carStates = ENU_ROT_90;
					}
					break;
					case ENU_EV4:		// 20 > distance
					{
						st_enu_carStates = ENU_BWD_30;
					}
					break;
					case ENU_EV6:		// distance > 70 for 5 second
					{
						st_enu_carStates = ENU_FWD_50;
					}
					break;
					case ENU_EV7:
					{
						st_enu_carStates = ENU_PWR_OFF;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			break;
			case ENU_FWD_50:
			{
				switch(enu_carEvents)
				{
					case ENU_EV1:		// distance > 70
					{
						st_enu_carStates = ENU_FWD_50;
					}
					break;
					case ENU_EV2:		// 70 > distance > 30
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV3:		// 30 > distance > 20
					{
						st_enu_carStates = ENU_ROT_90;
					}
					break;
					case ENU_EV4:		// 20 > distance
					{
						st_enu_carStates = ENU_BWD_30;
					}
					break;
					case ENU_EV7:
					{
						st_enu_carStates = ENU_PWR_OFF;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			break;
			case ENU_ROT_90:
			{
				switch(enu_carEvents)
				{
					case ENU_EV1:		// distance > 70
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV2:		// 70 > distance > 30
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV3:		// 30 > distance > 20
					{
						st_enu_carStates = ENU_ROT_90;
					}
					break;
					case ENU_EV4:		// 20 > distance
					{
						st_enu_carStates = ENU_BWD_30;
					}
					break;
					case ENU_EV5:		// stop for 3 seconds
					{
						st_enu_carStates = ENU_STOP_3_SEC;
					}
					break;
					case ENU_EV7:
					{
						st_enu_carStates = ENU_PWR_OFF;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			break;
			case ENU_BWD_30:
			{
				switch(enu_carEvents)
				{
					case ENU_EV1:		// distance > 70
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV2:		// 70 > distance > 30
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV3:		// 30 > distance > 20
					{
						st_enu_carStates = ENU_ROT_90;
					}
					break;
					case ENU_EV4:		// 20 > distance
					{
						st_enu_carStates = ENU_BWD_30;
					}
					break;
					case ENU_EV7:
					{
						st_enu_carStates = ENU_PWR_OFF;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			break;
			case ENU_STOP_3_SEC:
			{
				switch(enu_carEvents)
				{
					case ENU_EV1:		// distance > 70
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV2:		// 70 > distance > 30
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV3:		// 30 > distance > 20
					{
						st_enu_carStates = ENU_ROT_90;
					}
					break;
					case ENU_EV4:		// 20 > distance
					{
						st_enu_carStates = ENU_BWD_30;
					}
					break;
					case ENU_EV7:
					{
						st_enu_carStates = ENU_PWR_OFF;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			break;
			case ENU_PWR_ON:
			{
				switch(enu_carEvents)
				{
					case ENU_EV1:		// distance > 70
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV2:		// 70 > distance > 30
					{
						st_enu_carStates = ENU_FWD_30;
					}
					break;
					case ENU_EV3:		// 30 > distance > 20
					{
						st_enu_carStates = ENU_ROT_90;
					}
					break;
					case ENU_EV4:		// 20 > distance
					{
						st_enu_carStates = ENU_BWD_30;
					}
					break;
					case ENU_EV7:
					{
						st_enu_carStates = ENU_PWR_OFF;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			break;
			case ENU_PWR_OFF:
			{
				switch(enu_carEvents)
				{
					case ENU_EV8:
					{
						st_enu_carStates = ENU_PWR_ON;
					}
					break;
					default:
					{
						//do nothing
					}
					break;
				}
			}
			break;
			default:
			{
				//do nothing
			}
			break;
		}
	}
	return st_enu_carStates;
}

void car_welcome_screen(void)
{
	LCD_displayStringRowColumn(0,2,"CAR OBSTACLE");
	LCD_displayStringRowColumn(1,3,"AVOIDANCE");
	delay_ms(DELAY_TIMER_ID,3000);
	LCD_clearScreen();
}

void car_initialization_screen(void)
{
	LCD_clearScreen();
	_delay_ms(50);
	LCD_displayString("set Def. Rot");
	if (gl_enu_car_rotation_direction == ENU_LFT_DIR)
	{
		LCD_displayString("     ");
		LCD_displayStringRowColumn(1,0,"LEFT");	
	}
	else
	{
		LCD_displayString("     ");
		LCD_displayStringRowColumn(1,0,"RIGHT");
	}
}

void car_updtae_screen (enu_lcd_page_t enu_lcd_page,uint16 u16_distance,uint8 u8_car_speed,enu_car_direction_t enu_car_direction)
{
	static enu_lcd_page_t st_enu_lcd_page = ENU_MAX_PAGE;
	if((st_enu_lcd_page != enu_lcd_page))
	{
		LCD_clearScreen();
	}
	if(enu_lcd_page == ENU_PAGE_WELCOME)
	{
		LCD_displayStringRowColumn(0,2,"CAR OBSTACLE");
		LCD_displayStringRowColumn(1,3,"AVOIDANCE");
	}
	else if(enu_lcd_page == ENU_PAGE_MSG_1)
	{
		LCD_displayString("press start");
		LCD_displayStringRowColumn(1,0,"to start the car");
	}
	else if(enu_lcd_page == ENU_PAGE_MSG_2)
	{
		LCD_displayString("car stopped");
		LCD_displayStringRowColumn(1,0,"for 3 seconds");
	}
	else if(enu_lcd_page == ENU_PAGE_INIT)
	{
		LCD_displayStringRowColumn(0,0,"set Def. Rot");
		if (enu_car_direction == ENU_LFT_DIR)
		{
			LCD_displayStringRowColumn(1,0,"      ");
			LCD_displayStringRowColumn(1,0,"LEFT");
		}
		else
		{
			LCD_displayStringRowColumn(1,0,"      ");
			LCD_displayStringRowColumn(1,0,"RIGHT");
		}
	}
	else if(enu_lcd_page == ENU_PAGE_INFO)
	{
		LCD_displayStringRowColumn(0,0,"Dis= ");
		LCD_moveCursor(0,4);
		LCD_intgerToString(u16_distance);
		LCD_displayString("CM");
		LCD_displayStringRowColumn(0,11,"S:");
		LCD_intgerToString(u8_car_speed);
		LCD_displayStringRowColumn(1,0,"dir:");
		LCD_moveCursor(1,4);
		switch(enu_car_direction)
		{
			case ENU_FWD_DIR:
			{
				LCD_displayString("     ");
				LCD_displayStringRowColumn(1,4,"FWD");
			}
			break;
			case ENU_BWD_DIR:
			{
				LCD_displayString("     ");
				LCD_displayStringRowColumn(1,4,"BWD");
			}
			break;
			case ENU_RHT_DIR:
			{
				LCD_displayString("     ");
				LCD_displayStringRowColumn(1,4,"RHT");

			}
			break;
			case ENU_LFT_DIR:
			{
				LCD_displayString("     ");
				LCD_displayStringRowColumn(1,4,"LFT");
				
			}
			break;
			case ENU_STOP:
			{
				LCD_displayString("     ");
				LCD_displayStringRowColumn(1,4,"STOP");
				
			}
			break;
			default:
			{
				//do nothing
			}
			break;
		}
	}
	else
	{
		//do nothing
	}
	st_enu_lcd_page	= enu_lcd_page;
}
