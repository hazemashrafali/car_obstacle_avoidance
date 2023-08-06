/*
 * app.h
 *
 * Created: 2023-07-26 9:27:10 PM
 *  Author: HAZEM-PC
 */ 


#ifndef APP_H_
#define APP_H_

/*=========FILE INCLUSION=========*/
#include "../MCAL/EXT_INT/ext_interrupt.h"
#include "../HAL/BUTTON/button.h"
#include "../HAL/DC_MOTOR/dc_motor.h"
#include "../HAL/ULTRSONIC/ultrasonic.h"
#include "../HAL/LCD/lcd_config.h"
#include "../HAL/TMR_SERVICES/tmr_services.h"
#include "../HAL/LED/led.h"
#include "app_config.h"
/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/
extern str_dcMotor_config_t str_dcMotor_RUP_motor;
extern str_dcMotor_config_t str_dcMotor_RDW_motor;
extern str_dcMotor_config_t str_dcMotor_LUP_motor;
extern str_dcMotor_config_t str_dcMotor_LDW_motor;

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	ENU_FWD_DIR	= 0,
	ENU_BWD_DIR,
	ENU_RHT_DIR,
	ENU_LFT_DIR,
	ENU_STOP,
	ENU_MAX_DIR
}enu_car_direction_t;

typedef enum{
	ENU_EV1	= 0,
	ENU_EV2,
	ENU_EV3,
	ENU_EV4,
	ENU_EV5,
	ENU_EV6,
	ENU_MAX_EV
}enu_carEvents_t;

typedef enum{
	ENU_ST1	= 0,
	ENU_ST2,
	ENU_ST3,
	ENU_ST4,
	ENU_ST5,
	ENU_MAX_ST
}enu_carStates_t;
/*=========APIs DECLERATIONS=========*/
void app_init(void);
void update_screen(enu_car_direction_t direction,uint8 distance, uint8 speed);
void car_directionInit(void);
void display_event (enu_carEvents_t enu_carEvents,uint16 distance);
void robot_control (str_dcMotor_config_t* str_dcMotor_1, str_dcMotor_config_t* str_dcMotor_2, str_dcMotor_config_t* str_dcMotor_3, str_dcMotor_config_t* str_dcMotor_4,enu_car_direction_t enu_car_direction ,uint8 u8_car_speed);
enu_carEvents_t read_event (uint16* value);

#endif /* APP_H_ */