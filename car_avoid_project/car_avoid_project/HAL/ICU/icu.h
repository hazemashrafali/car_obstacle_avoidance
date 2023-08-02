/*
 * icu.h
 *
 * Created: 2023-07-26 9:31:08 PM
 *  Author: HAZEM-PC
 */ 


#ifndef ICU_H_
#define ICU_H_

/*===============FILE ENCLUTION ================*/
#include "..\..\MCAL\EXT_INT\ext_interrupt.h"
#include "..\..\MCAL\TIMER\timer_interface.h"
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
	ENU_ICU_MAX_EDGETYPE	= 2
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
}str_icu_configtype_t;

/*===============GLOBAL VARIBALS ================*/

/*=========================APIS=========================*/

/**
 * @brief       Icu_init					: function used to initialize interrupt id , interrupt edge type , timer id and timer clock
 *
 * @param[in]   Config_Ptr					: pointer to structure of type str_icu_configtype_t	
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_init(const str_icu_configtype_t * Config_Ptr);

/**
 * @brief       Icu_setCallBack				: function used to set ICU callback function
 *
 * @param[in]   a_ptr						: pointer to function take void and return void
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_setCallBack(void(*a_ptr)(void));

/**
 * @brief       Icu_setEdgeDetectionType	: function used to set/change ICU edge detection type 
 *
 * @param[in]   enu_icu_edgetype			: `ICU edge type it should be [ENU_ICU_FALLING,ENU_ICU_RISING] 
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_setEdgeDetectionType(const enu_icu_edgetype_t enu_icu_edgetype);

/**
 * @brief       Icu_getTimerValue			: function used to read timer value
 *
 * @param[in]   u16_timer_value				: pointer to uint16 used to hold timer value
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_getTimerValue(uint16* u16_timer_value);

/**
 * @brief       Icu_clearTimerValue			: function used to clear timer value
 *
 * @param[in]   void						:
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
enu_icu_error_t Icu_clearTimerValue(void);

/**
 * @brief       Icu_DeInit					: function used to de_initialize the ICU
 *
 * @param[in]   void						:
 *
 * @return      ENU_ICU_INVALID_EDGETYP		: in case of invalid interrupt edge type
 *              ENU_ICU_INVALID_CLOCK 		: in case of invalid timer clock 
 *				ENU_ICU_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_ICU_INVALID_CHANNEL		: in case of invalid interrupt channel id
 *				ENU_ICU_VALID				: in case of valid operation
 */
void Icu_DeInit(void);



#endif /* ICU_H_ */