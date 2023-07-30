/*
 * global_int.h
 *
 * Created: 2023-07-26 9:32:23 PM
 *  Author: HAZEM-PC
 */ 


#ifndef GLOBAL_INT_H_
#define GLOBAL_INT_H_

/*===============FILE ENCLUTION ================*/
#include "..\..\Utilities\Std_Types.h"
#include "..\..\Utilities\registers.h"
#include "..\..\Utilities\Common_Macros.h"

/*================ APIS ================*/
void enable_global_interrupt (void);
void disable_global_interrupt (void);


#endif /* GLOBAL_INT_H_ */