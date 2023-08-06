/*
 * app.c
 *
 * Created: 2023-07-26 9:27:03 PM
 *  Author: HAZEM-PC
 */ 

/*=========FILE INCLUSION=========*/
#include "app.h"
/*=========MACRO DEFINITIONS=========*/
#define BTN_DEBOUNCE_MS	100
/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/
enu_car_direction_t enu_car_direction			= ENU_RHT_DIR;
enu_car_direction_t enu_car_rotation_direction	= ENU_LFT_DIR;
uint8  gl_u8_carSpeed		= ZERO_VALUE;
uint16 gl_u16_obsDistance	= ZERO_VALUE;

uint8 gl_u8_start_btn	= LOGIC_LOW;
uint8 gl_u8_stop_btn	= LOGIC_LOW;

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
	Ultrasonic_init(ULTRASONIC_PORT,ULTRASONIC_TRIGGER_PIN,ULTRASONIC_ECHO_PIN);
	dcMotor_init(&str_dcMotor_RUP_motor);
	dcMotor_init(&str_dcMotor_RDW_motor);
	dcMotor_init(&str_dcMotor_LUP_motor);
	dcMotor_init(&str_dcMotor_LDW_motor);
}

void update_screen(enu_car_direction_t direction,uint8 distance, uint8 speed)
{
	LCD_displayStringRowColumn(0,0,"Dis= ");
	LCD_moveCursor(0,4);
	LCD_intgerToString(distance);
	LCD_displayString("CM");
	LCD_displayStringRowColumn(0,11,"S:");
	LCD_intgerToString(speed);
	LCD_displayStringRowColumn(1,0,"dir:");
	LCD_moveCursor(1,4);
	switch(direction)
	{
		case ENU_FWD_DIR:
		{
			LCD_displayString("FWD");
		}
		break;
		case ENU_BWD_DIR:
		{
			LCD_displayString("BWD");
		}
		break;
		case ENU_RHT_DIR:
		{
			LCD_displayString("RHT");
		}
		break;
		case ENU_LFT_DIR:
		{
			LCD_displayString("LFT");
		}
		break;
		case ENU_STOP:
		{
			LCD_displayString("STOP");
		}
		break;
		default:
		{
			//do nothing
		}
		break;
	}
}

void car_directionInit(void)
{
	uint8 value				= ZERO_VALUE;
	uint8 u8_direction		= ZERO_VALUE;
	uint8 u8_l_timeout_flag = ZERO_VALUE;

	
	update_screen(enu_car_direction,gl_u16_obsDistance,gl_u8_carSpeed);
	timeOut_sec(TIMEOUT_TIMER_ID,WAIT_TIME_SEC);
	timer_check_time_out_flag(TIMEOUT_TIMER_ID,&u8_l_timeout_flag);
	while(u8_l_timeout_flag != TRUE )
	{
		timer_check_time_out_flag(TIMEOUT_TIMER_ID,&u8_l_timeout_flag);
		button_read(DIRECTION_BUTTON_PORT,DIRECTION_BUTTON_PIN,&value);
		if(value == TRUE)
		{
			u8_direction ^= 1;
		}
		
		if(u8_direction == TRUE)
		{
			enu_car_rotation_direction = ENU_RHT_DIR;
		}
		else
		{
			enu_car_rotation_direction = ENU_LFT_DIR;
		}
		update_screen(enu_car_rotation_direction,gl_u16_obsDistance,gl_u8_carSpeed);
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

enu_carEvents_t read_event (uint16* value)
{
	enu_carEvents_t enu_carEvents				= ENU_MAX_EV;
	static BOOLEAN st_bo_l_event_flag			= FALSE;
	static BOOLEAN st_bo_l_timeout_active_flag	= FALSE;			//to control timeout function calling
	static uint8   st_u8_l_roatation_counter	= 0;				//to count number of car rotations
	uint8 u8_l_timeout_state					= 0;	
	Ultrasonic_readDistance(&gl_u16_obsDistance);	
	*value = gl_u16_obsDistance;						
	//button_read(START_BUTTON_PORT,START_BUTTON_PIN,&gl_u8_start_btn);
	//button_read(STOP_BUTTON_PORT,STOP_BUTTON_PIN,&gl_u8_stop_btn);

		if((gl_u16_obsDistance >= 70) && (st_bo_l_event_flag == FALSE))
		{
			enu_carEvents				= ENU_EV1;
			st_u8_l_roatation_counter	= 0;
			
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
		else if((gl_u16_obsDistance >= _70_CM) && (st_bo_l_event_flag == TRUE))
		{
			enu_carEvents				= ENU_EV6;
			st_u8_l_roatation_counter	= 0;
			st_bo_l_timeout_active_flag	= FALSE;
		}
		else if((gl_u16_obsDistance >= _30_CM) && (gl_u16_obsDistance < _70_CM))
		{
			enu_carEvents				= ENU_EV2;
			st_bo_l_timeout_active_flag	= FALSE;
			st_u8_l_roatation_counter	= 0;
			st_bo_l_event_flag			= FALSE;
		}
		else if((gl_u16_obsDistance >= _20_CM) && (gl_u16_obsDistance < _30_CM))
		{
			enu_carEvents				= ENU_EV3;
			st_bo_l_timeout_active_flag	= FALSE;
			st_bo_l_event_flag			= FALSE;
			st_u8_l_roatation_counter++;
			if(st_u8_l_roatation_counter == 4)		//car rotate 360 degree sequentially
			{
			 enu_carEvents = ENU_EV5;
			 st_u8_l_roatation_counter = 0;	
			}
		}
		else if(gl_u16_obsDistance < _20_CM)
		{
			enu_carEvents				= ENU_EV4;
			st_bo_l_event_flag			= FALSE;
			st_u8_l_roatation_counter	= 0;
			st_bo_l_timeout_active_flag	= FALSE;
		}
		else
		{
			enu_carEvents				= ENU_MAX_EV;
			st_bo_l_event_flag			= FALSE;
			st_u8_l_roatation_counter	= 0;
			st_bo_l_timeout_active_flag	= FALSE;
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
			LCD_displayString("distance>70");
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
			LCD_displayString("distance>>>70");
			//LCD_displayStringRowColumn(1,0,"with timeout");
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