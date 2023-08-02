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


//timer 0 registers
#define TCCR0	(*((volatile uint8*)0x53))
#define TCNT0	(*((volatile uint8*)0x52))
#define OCR0	(*((volatile uint8*)0x5C))
#define TIMSK	(*((volatile uint8*)0x59))	//Timer/Counter Interrupt Mask Register – TIMSK
#define TIFR	(*((volatile uint8*)0x58))	//Timer/Counter Interrupt Flag Register – TIFR
//timer 1 registers
#define TCCR1A	(*((volatile uint8*)0x4F))
#define TCCR1B	(*((volatile uint8*)0x4E))
#define TCNT1H	(*((volatile uint8*)0x4D))
#define TCNT1L	(*((volatile uint8*)0x4C))
#define TCNT1	(*((volatile uint16*)0x4C))
#define OCR1AH	(*((volatile uint8*)0x4B))
#define OCR1AL	(*((volatile uint8*)0x4A))
#define OCR1A	(*((volatile uint16*)0x4A))
#define OCR1BH	(*((volatile uint8*)0x49))
#define OCR1BL	(*((volatile uint8*)0x48))
#define OCR1B	(*((volatile uint16*)0x48))
#define ICR1H	(*((volatile uint8*)0x47))
#define ICR1L	(*((volatile uint8*)0x46))
#define ICR1	(*((volatile uint16*)0x46))
//timer 2 registers
#define TCCR2	(*((volatile uint8*)0x45))
#define TCNT2	(*((volatile uint8*)0x44))
#define OCR2	(*((volatile uint8*)0x43))
#define ASSR	(*((volatile uint8*)0x42))
#define SFIOR	(*((volatile uint8*)0x50))


/*======timer0 pin names ====== */
//TCCR0 timer counter control register

#define CS00  0
#define CS01  1
#define CS02  2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7
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

/*======timer1 pin names ====== */
//Timer/Counter1 Control Register A – TCCR1A

#define WGM10	0
#define WGM11	1
#define FOC1B	2
#define FOC1A	3
#define COM1B0	4
#define COM1B1	5
#define COM1A0	6
#define COM1A1	7
//Timer/Counter1 Control Register B – TCCR1B
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM12	3
#define WGM13	4
#define ICES1	6
#define ICNC1	7

/*======timer2 pin names ====== */

//Timer/Counter Control Register – TCCR2
#define CS20	0
#define CS21	1
#define CS22	2
#define WGM21	3
#define COM20	4
#define COM21	5
#define WGM20	6
#define FOC2	7
//Asynchronous Status Register – ASSR
#define TCR2UB	0
#define OCR2UB	1
#define TCN2UB	2
#define AS2		3


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
