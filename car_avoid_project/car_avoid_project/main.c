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

void fun (void)
{
	
}

int main(void)
{
/*
	uint16 value = 0;
	enu_icu_error_t enu_icu_error = ENU_ICU_VALID;
	str_icu_configtype_t str_icu_configtype ={0,ULTRASONIC_TIME_ID,ENU_ICU_F_CPU_8,ENU_ICU_RISING};
	enu_icu_error = Icu_init(&str_icu_configtype);
	enu_icu_error = Icu_setCallBack(fun);
	enu_icu_error = Icu_setEdgeDetectionType(ENU_ICU_FALLING);
	enu_icu_error = Icu_getTimerValue(&value);
	enu_icu_error = Icu_clearTimerValue();
	Icu_DeInit();
	while(1)
	{
		if (enu_icu_error == ENU_ICU_INVALID_INPUT)
		{
			fun();
		}
	}
*/
	
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
}

