/*===============FILE ENCLUTION ================*/
#include "ext_interrupt.h"
/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/
#define INT0_MASK 0xFC
#define INT1_MASK 0xF3
#define INT2_MASK 0xBF
/*===============TYBS DEFINTION ================*/


/*===============GLOBAL VARIBALS ================*/


/*=========================APIS=========================*/
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
enu_interrupt_error_t Init_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id, enu_trigger_mode_t enu_trigger_mode  )
{
	enu_interrupt_error_t enu_interrupt_error = ENU_INT_VALID;
	if((enu_intrrupt_id >= ENU_INT0_ID) && ( enu_intrrupt_id < ENU_MAX_INT_ID))
	{
		if((enu_trigger_mode >= ENU_LOW_LEVEL) && (enu_trigger_mode < ENU_MAX_TRIGGER_MODE))
		{
			MCUCR = enu_trigger_mode
		}
		else
		{
			enu_interrupt_error = ENU_INT_INVALID_MODE;
		}
		
	}
	else
	{
		enu_interrupt_error = ENU_INT_INVALID_ID;
	}
	
	
	return enu_interrupt_error;
}

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
 enu_interrupt_error_t enable_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id );

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
 enu_interrupt_error_t disable_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id );
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
enu_interrupt_error_t interrupt0_set_callback (void(*f_ptr)(void));
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
enu_interrupt_error_t interrupt1_set_callback (void(*f_ptr)(void));
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
enu_interrupt_error_t interrupt2_set_callback (void(*f_ptr)(void));

#endif  //MCAL_EXTERNAL_INT_H_