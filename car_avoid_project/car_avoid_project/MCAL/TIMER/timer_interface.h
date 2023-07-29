/*
 * timer_interface.h
 *
 * Created: 2023-07-26 9:32:51 PM
 *  Author: HAZEM-PC
 */ 

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/*===============FILE ENCLUTION ================*/
#include "..\..\Utilities\Std_Types.h"
#include "..\..\Utilities\registers.h"
#include "..\..\Utilities\Common_Macros.h"

/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/

/*===============TYBS DEFINTION ================*/
typedef enum
{
	ENU_TMR_CHANNEL_0	= 0,
	ENU_TMR_CHANNEL_1	= 1,
	ENU_TMR_CHANNEL_2	= 2,
	MAX_ENU_TMR_CHANNEL	= 3
}enu_tmr_channel_id_t;
	
typedef enum
{
	ENU_TMR_NORMAL_MODE	= 0,
	ENU_TMR_CMP_MODE	= 1,
	ENU_MAX_TMR_MODE	= 2
}enu_tmr_mode_t;

typedef enum
{
	ENU_TMR_INT_ENABLE	= 0,
	ENU_TMR_INT_DISABLE	= 1,
	ENU_MAX_TMR_STATE		= 2
}enu_tmr_interrupt_state_t;

typedef enum
{
	ENU_TMR_CMP_DISCONNECT	= 0,
	ENU_TMR_CMP_TOGGLE		= 1,
	ENU_TMR_CMP_CLEAR		= 2,
	ENU_TMR_CMP_SET			= 3,
	ENU_MAX_TMR_CMP_MODE	= 4	
}enu_tmr_cmp_mode_t;

typedef enum
{
	ENU_TMR_NO_CLK			= 0,
	ENU_TMR_CLK_1			= 1,
	ENU_TMR_CLK_8			= 2,
	ENU_TMR_CLK_32			= 3,
	ENU_TMR_CLK_64			= 4,
	ENU_TMR_CLK_256			= 5,
	ENU_TMR_CLK_1024		= 6,
	ENU_TMR_CLK_EXT_FALLING	= 7,
	ENU_TMR_CLK_EXT_RISING	= 8,
	ENU_TMR_MAX_CLK			= 9 
}enu_tmr_clk_t;

typedef struct
{
	enu_tmr_channel_id_t		enu_tmr_channel_id;
	enu_tmr_mode_t				enu_tmr_mode;
	enu_tmr_interrupt_state_t	enu_tmr_interrupt_state;
	enu_tmr_cmp_mode_t			enu_tmr_cmp_mode;
	enu_tmr_clk_t				enu_tmr_clk;
	uint16						u16_tmr_initial_value;
	uint16						u16_tmr_compare_value;
}str_tmr_config_t;


typedef enum
{
	ENU_TMR_INVALID_ID			= 0,
	ENU_TMR_INVALID_MODE		= 1,
	ENU_TMR_INVALID_INT_STATE	= 2,
	ENU_TMR_INVALID_CMP_MODE	= 3,
	ENU_TMR_INVALID_CLK			= 4,
	ENU_TMR_INVALID_INPUT		= 5,
	ENU_TMR_VALID				= 6,
	ENU_TMR_MAX_ERROR			= 7
}enu_tmr_error_t;

/*===============GLOBAL VARIBALS ================*/

	
/*================APIs================*/

/**
 * @brief       timer_init					: function used to initialize specific timer channel
 *
 * @param[in]   ptr_str_tmr_config			: pointer to structure of type str_tmr_config_t	
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_init	(str_tmr_config_t* ptr_str_tmr_config);

/**
 * @brief       timer_setInitialValue		: function used to set timer initial value
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   u16_tmr_initial_value		: timer initial value, in case of [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_2] it should be less than (256)
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_setInitialValue	(enu_tmr_channel_id_t enu_tmr_channel_id, uint16 u16_tmr_initial_value);

/**
 * @brief       timer_setCompareValue		: function used to set timer compare value
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   u16_tmr_compare_value		: timer compare value, in case of [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_2] it should be less than (256)
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_setCompareValue	(enu_tmr_channel_id_t enu_tmr_channel_id, uint16 u16_tmr_compare_value);

/**
 * @brief       timer_setClock				: function used to set timer clock source
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   enu_tmr_clk					: timer clock source, please refer to each timer clock table in the data sheet
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_setClock	(enu_tmr_channel_id_t enu_tmr_channel_id, enu_tmr_clk_t enu_tmr_clk);

/**
 * @brief       timer_setCallBack			: function used to set timer callback function 
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   f_ptr						: pointer to function
 * @param[in]	enu_tmr_mode				: timer mode which refer to [normal - compare]
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_setCallBack	(enu_tmr_channel_id_t enu_tmr_channel_id , volatile void (*f_ptr) (void) , enu_tmr_mode_t enu_tmr_mode);

/**
 * @brief       timer_start					: function used to start the timer to count
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_start	(enu_tmr_channel_id_t enu_tmr_channel_id);

/**
 * @brief       timer_stop					: function used to stop the timer 
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_stop	(enu_tmr_channel_id_t enu_tmr_channel_id);

/**
 * @brief       timer_getValue				: function used to read timer value
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[out]  ptr_u16_tmr_value			: reference to variable of timer value
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_getValue	(enu_tmr_channel_id_t enu_tmr_channel_id , uint16* ptr_u16_tmr_value);

/**
 * @brief       timer_enableNotification	: function used to enable timer interrupt source
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   enu_tmr_mode				: timer mode which refer to [normal - compare]
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_enableNotification	(enu_tmr_channel_id_t enu_tmr_channel_id,enu_tmr_mode_t enu_tmr_mode);

/**
 * @brief       timer_disableNotification	: function used to disable timer interrupt source
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[in]   enu_tmr_mode				: timer mode which refer to [normal - compare]
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_disableNotification	(enu_tmr_channel_id_t enu_tmr_channel_id,enu_tmr_mode_t enu_tmr_mode);

/**
 * @brief       timer_getStatus				: function used to get timer state if it is [ready - busy]
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 * @param[out]  ptr_u8_tmr_state			: reference to variable of timer state
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_getStatus	(enu_tmr_channel_id_t enu_tmr_channel_id,uint8* ptr_u8_tmr_state);

/**
 * @brief       timer_deInit				: function used to clear timer initialization
 *
 * @param[in]   enu_tmr_channel_id			: timer channel id, it should be [ENU_TMR_CHANNEL_0,ENU_TMR_CHANNEL_1,ENU_TMR_CHANNEL_2]
 *
 * @return      ENU_TMR_INVALID_ID			: in case of invalid interrupt edge type
 *              ENU_TMR_INVALID_MODE 		: in case of invalid timer mode 
 *				ENU_TMR_INVALID_INT_STATE	: in case of invalid timer interrupt state
 *				ENU_TMR_INVALID_CMP_MODE	: in case of invalid compare mode
 *				ENU_TMR_INVALID_CLK			: in case of invalid timer clock source
 *				ENU_TMR_INVALID_INPUT		: in case of invalid passing argument Ex. timer channel id - null pointer - value out of range
 *				ENU_TMR_VALID				: in case of valid operation
 */
enu_tmr_error_t timer_deInit	(enu_tmr_channel_id_t enu_tmr_channel_id);



#endif /* TIMER_INTERFACE_H_ */