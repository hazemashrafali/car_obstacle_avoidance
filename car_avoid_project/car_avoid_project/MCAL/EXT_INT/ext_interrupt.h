
#ifndef MCAL_EXTERNAL_INT_H_
#define MCAL_EXTERNAL_INT_H_

/*===============FILE ENCLUTION ================*/
#
/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/

/*===============TYBS DEFINTION ================*/
typedef enum{
	ENU_INT0_ID		= 0 ,
	ENU_INT1_ID		= 1	,
	ENU_INT2_ID		= 2 ,
	ENU_MAX_INT_ID	= 3 
}enu_intrrupt_id_t;

typedef enum {
	ENU_LOW_LEVEL			= 0 ,
	ENU_LOGICAL_CHANGE		= 1 ,	
	ENU_FALLING				= 2 ,
	ENU_RISING				= 3 ,
	ENU_MAX_TRIGGER_MODE 	= 4
}enu_trigger_mode_t;

typedef enum {
	ENU_INT_INVALID_ID		= 0,
	ENU_INT_INVALID_MODE	= 1,
	ENU_INT_INVALID_INPUT	= 2,
	ENU_INT_VALID			= 3,
	ENU_MAX_INT_ERROR		= 4
}enu_interrupt_error_t;

/*===============GLOBAL VARIBALS ================*/


/*=========================APIS=========================*/
/**
 * @brief       Init_external_interrupt     : function used to initialize external interrupt source and trigger mode
 *
 * @param[in]   enu_intrrupt_id				: the interrupt id, it should be [ENU_INT0_ID,ENU_INT1_ID,ENU_INT2_ID]	
 * @param[in]   enu_trigger_mode			: the interrupt trigger mode, it should be [ENU_LOW_LEVEL,ENU_LOGICAL_CHANGE,ENU_FALLING,ENU_RISING]
 *
 * @return      ENU_INT_INVALID_ID			: in case invalid interrupt id   
 *              ENU_INT_INVALID_MODE 		: in case invalid interrupt trigger mode  
 *				ENU_INT_VALID				: in case of valid parameters	
 */
enu_interrupt_error_t Init_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id, enu_trigger_mode_t enu_trigger_mode  );

/**
 * @brief       enable_external_interrupt   : function used to enable external interrupt source
 *
 * @param[in]   enu_intrrupt_id				: the interrupt id, it should be [ENU_INT0_ID,ENU_INT1_ID,ENU_INT2_ID]	
 *
 * @return      ENU_INT_INVALID_ID			: in case invalid interrupt id   
 *              ENU_INT_INVALID_MODE 		: in case invalid interrupt trigger mode  
 *				ENU_INT_VALID				: in case of valid parameters	
 */
 enu_interrupt_error_t enable_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id );

/**
 * @brief       disable_external_interrupt  : function used to disable external interrupt source
 *
 * @param[in]   enu_intrrupt_id				: the interrupt id, it should be [ENU_INT0_ID,ENU_INT1_ID,ENU_INT2_ID]	
 *
 * @return      ENU_INT_INVALID_ID			: in case invalid interrupt id   
 *              ENU_INT_INVALID_MODE 		: in case invalid interrupt trigger mode  
 *				ENU_INT_VALID				: in case of valid parameters	
 */
 enu_interrupt_error_t disable_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id );
 
/**
 * @brief       interrupt0_set_callback     : function used to set call back function for interrupt 0
 *
 * @param[in]   f_ptr						: pointer to callback function
 *
 * @return      ENU_INT_INVALID_ID			: in case invalid interrupt id   
 *              ENU_INT_INVALID_MODE 		: in case invalid interrupt trigger mode  
 *				ENU_INT_VALID				: in case of valid parameters	
 *   			ENU_INT_INVALID_INPUT		: in case of invalid input
 */
enu_interrupt_error_t interrupt0_set_callback (void(*f_ptr)(void));

/**
 * @brief       interrupt1_set_callback     : function used to set call back function for interrupt 1
 *
 * @param[in]   f_ptr						: pointer to callback function
 *
 * @return      ENU_INT_INVALID_ID			: in case invalid interrupt id   
 *              ENU_INT_INVALID_MODE 		: in case invalid interrupt trigger mode  
 *				ENU_INT_VALID				: in case of valid parameters	
 *   			ENU_INT_INVALID_INPUT		: in case of invalid input
 */
enu_interrupt_error_t interrupt1_set_callback (void(*f_ptr)(void));

/**
 * @brief       interrupt2_set_callback     : function used to set call back function for interrupt 2
 *
 * @param[in]   f_ptr						: pointer to callback function
 *
 * @return      ENU_INT_INVALID_ID			: in case invalid interrupt id   
 *              ENU_INT_INVALID_MODE 		: in case invalid interrupt trigger mode  
 *				ENU_INT_VALID				: in case of valid parameters	
 *   			ENU_INT_INVALID_INPUT		: in case of invalid input
 */
enu_interrupt_error_t interrupt2_set_callback (void(*f_ptr)(void));

#endif  //MCAL_EXTERNAL_INT_H_