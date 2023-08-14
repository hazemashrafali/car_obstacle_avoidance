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

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	ENU_FWD_DIR	= 0	,
	ENU_BWD_DIR		,
	ENU_RHT_DIR		,
	ENU_LFT_DIR		,
	ENU_STOP		,
	ENU_MAX_DIR
}enu_car_direction_t;

typedef enum{
	ENU_EV1	= 0,	// distance > 70
	ENU_EV2,		// 70 > distance > 30
	ENU_EV3,		// 30 > distance > 20
	ENU_EV4,		// 20 > distance
	ENU_EV5,		// stop for 3 seconds
	ENU_EV6,		// distance > 70 for 5 second
	ENU_EV7,		// button power off
	ENU_EV8,		// button power on
	ENU_MAX_EV
}enu_carEvents_t;

typedef enum{
	ENU_FWD_30	= 0	,	// move forward speed 30 %
	ENU_FWD_50		,	// move forward speed 50 %
	ENU_PWR_OFF		,	// stop car, power off
	ENU_ROT_90		,	// stop and rotate 90*
	ENU_BWD_30		,	// move backward speed 30 %
	ENU_STOP_3_SEC	,	// stop car for 3 seconds
	ENU_PWR_ON		,	// start car, power on
	ENU_MAX_ST
}enu_carStates_t;

typedef enum{
	ENU_CAR_POWER_OFF,
	ENU_CAR_POWER_ON,
	ENU_CAR_POWER_STABLE
}enu_car_power_t;

typedef enum{
	ENU_PAGE_INFO,
	ENU_PAGE_WELCOME,
	ENU_PAGE_INIT,
	ENU_PAGE_MSG_1,
	ENU_PAGE_MSG_2,
	ENU_MAX_PAGE
}enu_lcd_page_t;

/*=========GLOBAL VARIABLES=========*/

/*=========EXTERN VARIABLES=========*/
extern str_dcMotor_config_t str_dcMotor_RUP_motor;
extern str_dcMotor_config_t str_dcMotor_RDW_motor;
extern str_dcMotor_config_t str_dcMotor_LUP_motor;
extern str_dcMotor_config_t str_dcMotor_LDW_motor;
extern enu_car_direction_t  gl_enu_car_direction;
extern uint8				gl_u8_carSpeed;

/*=========APIs DECLERATIONS=========*/
void app_init(void);
void car_directionInit(void);
void robot_control (str_dcMotor_config_t* str_dcMotor_1, str_dcMotor_config_t* str_dcMotor_2, str_dcMotor_config_t* str_dcMotor_3, str_dcMotor_config_t* str_dcMotor_4,enu_car_direction_t enu_car_direction ,uint8 u8_car_speed);
enu_carEvents_t read_event (uint16* value);
enu_carStates_t car_stateMachine (enu_carEvents_t enu_carEvents);
void car_action (enu_carStates_t enu_carStates,uint8* u8_carSpeed,enu_car_direction_t* enu_car_direction);
void car_powerOn (void);
void car_powerOff (void);
void car_welcome_screen(void);
void car_initialization_screen(void);
void car_updtae_screen (enu_lcd_page_t enu_lcd_page,uint16 u16_distance,uint8 u8_car_speed,enu_car_direction_t enu_car_direction);
void display_event (enu_carEvents_t enu_carEvents,uint16 distance);

#endif /* APP_H_ */