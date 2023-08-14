/*
 * car_avoid_project.c
 *
 * Created: 2023-07-26 9:26:13 PM
 * Author : HAZEM-PC
 */ 

#include "APP/app.h"

int main(void)
{
	uint16 u16_obstacle_distance			= LOGIC_ZERO;
	enu_carEvents_t enu_carEvents			= ENU_MAX_EV;
	enu_carStates_t	enu_carStates			= ENU_MAX_ST;
	enu_car_direction_t enu_car_direction	= ENU_STOP;
	uint8 u8_car_speed						= SPEED_0_PERCENT;
	
	app_init();
	
	while(1)
	{
		enu_carEvents = read_event(&u16_obstacle_distance);
		enu_carStates = car_stateMachine(enu_carEvents);
		car_action(enu_carStates,&u8_car_speed,&enu_car_direction);
		if(enu_carStates != ENU_PWR_OFF)
			car_updtae_screen(ENU_PAGE_INFO,u16_obstacle_distance,u8_car_speed,enu_car_direction);
	}

}








	/*
	uint16 value=0;
	uint8 x = 0;
	LCD_init();
	Ultrasonic_init(PORTB_ID,5,ENU_ECHO_ID_0);
	LCD_displayString("Distance = ");
	PWM_Init(3,6,0);
	enable_global_interrupt();
	
	while(1)
	{
		for(x = 0;x<100;x++)
		{
			PWM_start(0,20,x);
			delay_ms(2,5);	
		}
		Ultrasonic_readDistance(&value);
		LCD_moveCursor(0,10);
		LCD_intgerToString(value);
		LCD_displayString(" CM ");
		delay_ms(2,50);
	}
	*/
	/*
	//ULTRASONIC CODE
	uint16 value=0;
	LCD_init();
	Ultrasonic_init(PORTB_ID,5,ENU_ECHO_ID_0);
	LCD_displayString("Distance = ");
	enable_global_interrupt();
	while(1)
	{
		Ultrasonic_readDistance(&value);
		LCD_moveCursor(0,10);
		LCD_intgerToString(value);
		LCD_displayString(" CM");
		//_delay_ms(200);
		delay_ms(2,50);
	}
	*/