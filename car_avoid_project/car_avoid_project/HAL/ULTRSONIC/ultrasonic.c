/*
 * ultrasonic.c
 *
 * Created: 2023-07-26 9:31:32 PM
 *  Author: HAZEM-PC
 */ 
/*============= FILE INCLUSION =============*/
#include "ultrasonic.h"
#include "..\TMR_SERVICES\tmr_services.h"

/*============= MACRO DEFINITION =============*/
#define NUM_OF_EDGES		2
#define DELAY_ID			2
#define TRIGGER_TIME		10
#define FIREST_EDGE			1
#define SECOND_EDGE			2
#define ZERO				0
#define CALC_DISTANCE(x)	(((uint16)x/58)+1)
/*============= GLOBAL STATIC VARIABLES =============*/
static uint8	gl_u8_edgeCount	= ZERO;		//to count number of edges
static uint16	gl_u16_timeHigh	= ZERO;		//to hold time of generated pulse
static uint8	gl_u8_triggerPort;			//to hold trigger port id
static uint8	gl_u8_triggerPin;			//to hold trigger pin id

/*============= FUNCTION DEFINITION =============*/

/**
 * @brief       Ultrasonic_edgeProcessing		: callback function used to process the detection of echo signal 
 */
void Ultrasonic_edgeProcessing(void)
{
	gl_u8_edgeCount++;
	if(gl_u8_edgeCount == FIREST_EDGE)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(ENU_ICU_FALLING);
	}
	else if(gl_u8_edgeCount == SECOND_EDGE)
	{
		Icu_getTimerValue(&gl_u16_timeHigh);
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(ENU_ICU_RISING);
	}
}

/**
 * @brief       Ultrasonic_init				: Function to initialize the ultrasonic driver
 *											  initialize ICU driver,set callback function,setup trigger pin direction as output
 *											  setup External interrupt source
 */
enu_usonic_state_t Ultrasonic_init(uint8 u8_triggerPort,uint8 u8_triggerPin,enu_echo_pin_id_t enu_echo_pin_id)
{
	enu_usonic_state_t enu_usonic_state = ENU_USONIC_STATE_VALID;
	str_icu_configtype_t str_icu_configtype;
	if((u8_triggerPort < MAX_PORT_ID) && (u8_triggerPin < MAX_PIN_ID) && (enu_echo_pin_id < ENU_MAX_ECHO))
	{
		str_icu_configtype.enu_icu_channel_id	= enu_echo_pin_id;
		str_icu_configtype.enu_timer_channel_id = ULTRASONIC_TIMER_ID;
		str_icu_configtype.enu_icu_clock		= ENU_ICU_F_CPU_8;
		str_icu_configtype.enu_icu_edgetype		= ENU_ICU_RISING;
		gl_u8_triggerPort						= u8_triggerPort;
		gl_u8_triggerPin						= u8_triggerPin;
		Icu_init(&str_icu_configtype);
		Icu_setCallBack(Ultrasonic_edgeProcessing);
		DIO_pinMode(u8_triggerPort,u8_triggerPin,PIN_OUTPUT);		 //setup trigger pin direction as output
		DIO_writePin(u8_triggerPort,u8_triggerPin,PIN_LOW);
	}
	else
	{
		enu_usonic_state = ENU_USONIC_STATE_INVALID;
	}
	return enu_usonic_state;
}

/**
 * @brief       Ultrasonic_Trigger		: function used to send trigger pulse 10 microSEC
 */
void Ultrasonic_Trigger(void)
{
	DIO_writePin(gl_u8_triggerPort, gl_u8_triggerPin,PIN_HIGH);
	delay_us(DELAY_ID,TRIGGER_TIME);
	DIO_writePin(gl_u8_triggerPort, gl_u8_triggerPin,PIN_LOW);
}

/**
 * @brief       Ultrasonic_readDistance		: function to read distance of from the sensor
 */
enu_usonic_state_t Ultrasonic_readDistance(uint16* ptr_u16_distanceValue)
{
	enu_usonic_state_t enu_usonic_state = ENU_USONIC_STATE_VALID;
	if(ptr_u16_distanceValue != NULL_PTR)
	{
		Ultrasonic_Trigger();
		while(gl_u8_edgeCount != NUM_OF_EDGES);			//wait until ultrasonic sound to travel towards the object and return.
		*ptr_u16_distanceValue = CALC_DISTANCE(gl_u16_timeHigh);
		gl_u8_edgeCount=ZERO;							//clear edge count to be ready for new read
	}
	else
	{
		enu_usonic_state = ENU_USONIC_STATE_INVALID;
	}
	return enu_usonic_state;
}
