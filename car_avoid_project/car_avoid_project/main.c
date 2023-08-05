/*
 * car_avoid_project.c
 *
 * Created: 2023-07-26 9:26:13 PM
 * Author : HAZEM-PC
 */ 

#include "HAL/TMR_SERVICES/tmr_services.h"
#include "HAL/LCD/lcd.h"
#include "HAL/ULTRSONIC/ultrasonic.h"
#include "MCAL/EXT_INT/ext_interrupt.h"
#include "util/delay.h"
#include "HAL/PWM/pwm.h"
#include "HAL/DC_MOTOR/dc_motor.h"

void fun (void)
{
	
}

int main(void)
{
	str_dcMotor_config_t str_dcMotor_config;
	str_dcMotor_config.positive_terminal.port_id = PORTA_ID;
	str_dcMotor_config.positive_terminal.pin_id	 = PIN1_ID;
	str_dcMotor_config.negative_terminal.port_id = PORTA_ID;
	str_dcMotor_config.negative_terminal.pin_id  = PIN2_ID;
	str_dcMotor_config.enable_terminal.port_id	 = PORTA_ID;
	str_dcMotor_config.enable_terminal.pin_id	 = PIN0_ID; 
	dcMotor_init(&str_dcMotor_config);
	enable_global_interrupt();
	dcMotor_rotate(&str_dcMotor_config,ENU_DCMOTOR_ACW,10);
	while(1)
	{
		fun();
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
	
}

