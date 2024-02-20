#ifndef 		TIMER0_INTERFACE_H
#define 		TIMER0_INTERFACE_H

#define 	TCCR0 		*((volatile u8 *)0x53)
#define 	TCNT0 		*((volatile u8 *)0x52) 
#define 	OCR0 		*((volatile u8 *)0x5C)
#define 	TIMSK 		*((volatile u8 *)0x59)

#define NORMAL_MODE   	0
#define CTC_MODE      	1
#define FAST_PWM      	2
#define PHASE_CORRECT 	3



#endif