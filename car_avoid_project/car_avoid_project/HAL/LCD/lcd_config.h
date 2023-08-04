/*
 * lcd_config.h
 *
 * Created: 2023-07-18 2:54:20 PM
 *  Author: HAZEM-PC
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/*******************************************************************************
 *                             FILE INCLUSION                                  *
 *******************************************************************************/
#include "lcd.h"


/*******************************************************************************
 *                             configuration set                                *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 4

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be equal to 4 or 8"
#endif /*LCD_DATA_BITS_MODE*/


#if (LCD_DATA_BITS_MODE == 4)
/* if LCD_LAST_PORT_PINS is defined in the code, the LCD driver will use the last 4 pins in the gpio port for for data.
 * To use the first four pins in the gpio port for data just remove LCD_LAST_PORT_PINS */

#define LCD_LAST_PORT_PINS
#ifdef	LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID         PIN4_ID
#else
#define LCD_FIRST_DATA_PIN_ID         PIN0_ID
#endif

#endif /*LCD_DATA_BITS_MODE*/

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN1_ID
#define LCD_RW_PORT_ID                 PORTB_ID
#define LCD_RW_PIN_ID                  PIN2_ID
#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN3_ID
#define LCD_DATA_PORT_ID               PORTA_ID


#endif /* LCD_CONFIG_H_ */