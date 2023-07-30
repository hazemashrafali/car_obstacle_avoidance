/*
 * global_int.c
 *
 * Created: 2023-07-26 9:32:33 PM
 *  Author: HAZEM-PC
 */ 

/*===============FILE ENCLUTION ================*/
#include "global_int.h"


/*================ APIS ================*/
void enable_global_interrupt (void)
{
	SET_BIT(SREG,PIN7);
}
void disable_global_interrupt (void)
{
	CLEAR_BIT(SREG,PIN7);
}