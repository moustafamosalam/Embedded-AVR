#ifndef 		USART_PRIVATE_H
#define 		USART_PRIVATE_H

#define 	UDR  		*((volatile u8 *)0x2C)
#define 	UCSRA 		*((volatile u8 *)0x2B) 
#define 	UCSRB		*((volatile u8 *)0x2A)
#define 	UBRRL		*((volatile u8 *)0x29)
#define 	UBRRH		*((volatile u8 *)0x40)
#define 	UCSRC 		*((volatile u8 *)0x40)


#endif