/*
 * icu.h
 *
 * Created: 2023-07-26 9:31:08 PM
 *  Author: HAZEM-PC
 */ 


#ifndef ICU_H_
#define ICU_H_

/*===============FILE ENCLUTION ================*/
#include "..\..\Utilities\Std_Types.h"
#include "..\..\Utilities\registers.h"
#include "..\..\Utilities\Common_Macros.h"
#include "..\..\MCAL\EXT_INT\ext_interrupt.h"
/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/

/*===============TYBS DEFINTION ================*/
typedef enum
{
	ENU_ICU_NO_CLOCK		= 0 ,
	ENU_ICU_F_CPU_CLOCK		= 1 ,
	ENU_ICU_F_CPU_8			= 2 ,
	ENU_ICU_F_CPU_64		= 3 ,
	ENU_ICU_F_CPU_256		= 4 ,
	ENU_ICU_F_CPU_1024		= 5 ,
	ENU_ICU_MAX_CLOCK		= 6
}enu_icu_clock_t;

typedef enum
{
	ENU_ICU_FALLING			= 0 ,
	ENU_ICU_RISING			= 1 ,
	ENU_ICU_MAX_EDGETYP		= 2
}enu_icu_edgetype_t;

typedef enum
{
	ENU_ICU_INVALID_EDGETYP		= 0 ,
	ENU_ICU_INVALID_CLOCK		= 1 ,
	ENU_ICU_INVALID_INPUT		= 2 ,
	ENU_ICU_INVALID_CHANNEL		= 3 ,
	ENU_ICU_VALID				= 4 ,
	ENU_ICU_MAX_ERROR			= 5
}enu_icu_error_t;

typedef enum
{
	ENU_TIMER_CHANNEL_ID0		= 0 ,
	ENU_TIMER_CHANNEL_ID1		= 1 ,
	ENU_TIMER_CHANNEL_ID2		= 2 ,
	ENU_TIMER_MAX_CHANNEL		= 3
}enu_timer_channel_id_t;


typedef enum
{
	ENU_ICU_CHANNEL_ID0		= 0 ,
	ENU_ICU_CHANNEL_ID1		= 1 ,
	ENU_ICU_CHANNEL_ID2		= 2 ,
	ENU_ICU_MAX_CHANNEL		= 3
}enu_icu_channel_id_t;

typedef struct
{
	enu_icu_channel_id_t	enu_icu_channel_id;
	enu_timer_channel_id_t	enu_timer_channel_id;
	enu_icu_clock_t			enu_icu_clock;
	enu_icu_edgetype_t		enu_icu_edgetype;
}enu_icu_configtype_t;

/*===============GLOBAL VARIBALS ================*/


/*=========================APIS=========================*/

/**
 * @brief       DIO_pinMode                 : function to init interrupt id and interrupt edge type and timer id and clock
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_init(const enu_icu_configtype_t * Config_Ptr);


/**
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_setCallBack(void(*a_ptr)(void));

/**
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_setEdgeDetectionType(const enu_icu_edgetype_t enu_icu_edgetype);

/**
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_getTimerValue(uint16* u16_timer_value);

/**
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
enu_icu_error_t Icu_clearTimerValue(void);

/**
 * @brief       DIO_pinMode                 :
 *
 * @param[in]   port						:	
 * @param[in]   pin							:
 * @param[in]   direction					:	
 *
 * @return      VALID_OPERATION				:   
 *              INVALID_PORT_ID 			:   
 *				INVALID_PIN_ID				:
 *				INVALID_DIRECTION			:	
 */
void Icu_DeInit(void);



#endif /* ICU_H_ */