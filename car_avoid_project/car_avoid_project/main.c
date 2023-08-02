/*
 * car_avoid_project.c
 *
 * Created: 2023-07-26 9:26:13 PM
 * Author : HAZEM-PC
 */ 

#include "HAL/TMR_SERVICES/tmr_services.h"
#include "MCAL/GLOBAL_INT/global_int.h"
#include "HAL/LED/led.h"
#include "HAL/BUTTON/button.h"
	
int main(void)
{
	uint8 flag = 0,count_flag=0;
	led_init(PORTD_ID,PIN7_ID);
	led_init(PORTD_ID,PIN6_ID);
	timeOut_sec(2,2.5);
	enable_global_interrupt();
    /* Replace with your application code */
    while (1) 
    {
		timer_check_time_out_flag(2,&flag);
		if(flag == 1)
		{
			led_write(PORTD_ID,PIN7_ID,PIN_HIGH);
			/*
			count_flag++;
			if(count_flag == 1)
			{
				timeOut_sec(1,3);	
			}
			if(count_flag == 2)
			{
				led_write(PORTD_ID,PIN6_ID,PIN_HIGH);
				timeOut_sec(1,10);
			}
			if(count_flag == 3)
			{
				led_write(PORTD_ID,PIN7_ID,PIN_LOW);
				led_write(PORTD_ID,PIN6_ID,PIN_LOW);
			}
			*/
		}
    }
}

