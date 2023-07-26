/*===============FILE ENCLUTION ================*/
#include "ext_interrupt.h"
/*===============EXTERNAL VARIBALS ================*/

/*===============MACROS DEFINTION ================*/
#define INT0_MASK 0xFC
#define INT1_MASK 0xF3
#define INT2_MASK 0xBF
/*===============TYBS DEFINTION ================*/


/*===============GLOBAL VARIBALS ================*/
static volatile void (*gl_callbackptr_0)(void) = NULL_PTR;
static volatile void (*gl_callbackptr_1)(void) = NULL_PTR;
static volatile void (*gl_callbackptr_2)(void) = NULL_PTR;
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
			if(enu_intrrupt_id == ENU_INT0_ID)
			{
				MCUCR = (MCUCR & INT0_MASK) | (enu_trigger_mode) ;
			}
			else if (enu_intrrupt_id == ENU_INT1_ID)
			{
				MCUCR = (MCUCR & INT1_MASK) | ((enu_trigger_mode) << ISC10) ;
			}
			else if (enu_intrrupt_id == ENU_INT2_ID)
			{
				if((enu_trigger_mode == ENU_FALLING) || (enu_trigger_mode == ENU_RISING))
				{
					MCUCSR = (MCUCSR & INT2_MASK) | ((enu_trigger_mode) << ISC2) ;
				}
				else
				{
					enu_interrupt_error = ENU_INT_INVALID_MODE;
				}	
			}
			else
			{
				enu_interrupt_error = ENU_INT_INVALID_MODE;
			}
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
 enu_interrupt_error_t enable_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id )
 {
	enu_interrupt_error_t enu_interrupt_error = ENU_INT_VALID;
	if((enu_intrrupt_id >= ENU_INT0_ID) && ( enu_intrrupt_id < ENU_MAX_INT_ID))
	{
		if(enu_intrrupt_id == ENU_INT0_ID)
		{
			SET_BIT(GICR,INT0);
		}
		else if (enu_intrrupt_id == ENU_INT1_ID)
		{
			SET_BIT(GICR,INT1);
		}
		else if (enu_intrrupt_id == ENU_INT2_ID)
		{
			SET_BIT(GICR,INT2);
		}
		else
		{
			// do nothing
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
 enu_interrupt_error_t disable_external_interrupt( enu_intrrupt_id_t enu_intrrupt_id )
 {
	 enu_interrupt_error_t enu_interrupt_error = ENU_INT_VALID;
	 if((enu_intrrupt_id >= ENU_INT0_ID) && ( enu_intrrupt_id < ENU_MAX_INT_ID))
	 {
		 if(enu_intrrupt_id == ENU_INT0_ID)
		 {
			 CLEAR_BIT(GICR,INT0);
		 }
		 else if (enu_intrrupt_id == ENU_INT1_ID)
		 {
			 CLEAR_BIT(GICR,INT1);
		 }
		 else if (enu_intrrupt_id == ENU_INT2_ID)
		 {
			 CLEAR_BIT(GICR,INT2);
		 }
		 else
		 {
			 // do nothing
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
enu_interrupt_error_t interrupt0_set_callback (void(*f_ptr)(void))
{
	enu_interrupt_error_t enu_interrupt_error = ENU_INT_VALID;
	if (f_ptr != NULL_PTR)
	{
		gl_callbackptr_0 = f_ptr;
		
	}
	else
	{
		enu_interrupt_error = ENU_INT_INVALID_INPUT ;
	}
	return enu_interrupt_error ;
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
enu_interrupt_error_t interrupt1_set_callback (void(*f_ptr)(void))
{
		enu_interrupt_error_t enu_interrupt_error = ENU_INT_VALID;
		if (f_ptr != NULL_PTR)
		{
			gl_callbackptr_1 = f_ptr;
			
		}
		else
		{
			enu_interrupt_error = ENU_INT_INVALID_INPUT ;
		}
		return enu_interrupt_error ;
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
enu_interrupt_error_t interrupt2_set_callback (void(*f_ptr)(void))
{	
	enu_interrupt_error_t enu_interrupt_error = ENU_INT_VALID;
	if (f_ptr != NULL_PTR)
	{
		gl_callbackptr_2 = f_ptr;
		
	}
	else
	{
		enu_interrupt_error = ENU_INT_INVALID_INPUT ;
	}
	return enu_interrupt_error ;
}

ISR_HANDLER(EXT_INT0)
{
	if(gl_callbackptr_0 != NULL_PTR)
	{
		gl_callbackptr_0();
	}
}

ISR_HANDLER(EXT_INT1)
{
	if(gl_callbackptr_1 != NULL_PTR)
	{
		gl_callbackptr_1();
	}
}

ISR_HANDLER(EXT_INT2)
{
	if(gl_callbackptr_2 != NULL_PTR)
	{
		gl_callbackptr_2();
	}
}
