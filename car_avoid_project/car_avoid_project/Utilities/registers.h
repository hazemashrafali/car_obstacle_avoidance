/*
 * registers.h
 *
 * Created: 2023-06-05 7:15:38 PM
 *  Author: HAZEM-PC
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "Std_Types.h"

#define PORTA	(*((volatile uint8*)0x3B))
#define DDRA	(*((volatile uint8*)0x3A))
#define PINA	(*((volatile uint8*)0x39))

#define PORTB	(*((volatile uint8*)0x38))
#define DDRB	(*((volatile uint8*)0x37))
#define PINB	(*((volatile uint8*)0x36))

#define PORTC	(*((volatile uint8*)0x35))
#define DDRC	(*((volatile uint8*)0x34))
#define PINC	(*((volatile uint8*)0x33))

#define PORTD	(*((volatile uint8*)0x32))
#define DDRD	(*((volatile uint8*)0x31))
#define PIND	(*((volatile uint8*)0x30))


#define TCCR0	(*((volatile uint8*)0x53))
#define TCNT0	(*((volatile uint8*)0x52))
#define OCR0	(*((volatile uint8*)0x5C))
#define TIFR	(*((volatile uint8*)0x58))
#define TIMSK	(*((volatile uint8*)0x59))

//External interrupt registers
#define MCUCR	(*((volatile uint8*)0x55))
#define SREG	(*((volatile uint8*)0x5F))
#define MCUCSR	(*((volatile uint8*)0x54))
#define GICR	(*((volatile uint8*)0x5B))
#define GIFR	(*((volatile uint8*)0x5A))


#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7
#define MAX_PIN 8

//TCCR0 timer counter control register
#define CS00	0
#define CS01	1
#define CS02	2
#define WGM01	3
#define COM00	4
#define COM01	5
#define WGM00	6
#define FOC0	7
//TIMSK interrupt mask register
#define TOIE0  0
#define OCIE0  1
#define TOIE1  2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2  6
#define OCIE2  7
//TIFR interrupt flag register
#define TOV0  0
#define OCF0  1
#define TOV1  2
#define OCF1B 3
#define OCF1A 4
#define ICF1  5
#define TOV2  6
#define OCF2  7

//MCU Control Register – MCUCR
#define SE		7
#define SM2		6
#define SM1		5
#define SM0		4
#define ISC11	3
#define ISC10	2
#define ISC01	1
#define ISC00	0

//MCU Control and Status Register – MCUCSR
#define JTD		7
#define ISC2	6 
#define JTRF	4
#define WDRF	3
#define BORF	2
#define EXTRF	1
#define PORF	0

//General Interrupt Control Register – GICR
#define INT1	7
#define INT0	6
#define INT2	5
#define IVSEL	1
#define IVCE	0

//General Interrupt Flag Register – GIFR
#define INTF1	7
#define INTF0	6	
#define INTF2	5


//timer ISR definition
#define EXT_INT0	__vector_1
#define EXT_INT1	__vector_2
#define EXT_INT2	__vector_3
#define TMR2_CMP	__vector_4
#define TMR2_OVF	__vector_5
#define TMR1_CPT	__vector_6
#define TMR1_CMP_A	__vector_7
#define TMR1_CMP_B	__vector_8
#define TMR1_OVF	__vector_9
#define TMR0_CMP	__vector_10
#define TMR0_OVF	__vector_11

//Macro defines the ISR
#define ISR_HANDLER(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used));\
void INT_VECT(void)

#endif /* REGISTERS_H_ */
