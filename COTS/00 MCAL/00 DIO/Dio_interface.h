#ifndef			DIO_INTERFACE_H
#define			DIO_INTERFACE_H

void	DIO_voidSetPinDirection(u8 Port ,u8 Pin , u8 Direction );
void	DIO_voidSetPinValue(u8 Port ,u8 Pin , u8 Value );
u8		DIO_u8GetPinValue(u8 Port , u8 Pin);
//DIO_voidSetPinDirection(PORTA , PIN0 , OUTPUT); ==> DDRA = 0b00000001; A0 is output
//DIO_voidSetPinValue(PORTA , PIN0 , HIGH); ==> PORTA = 0b00000001; A0 HIGH
void	DIO_voidSetPortDirection(u8 Port , u8 Direction );
void	DIO_voidSetPortValue(u8 Port , u8 Value );

#define				PORTA			0
#define				PORTB			1
#define				PORTC			2
#define				PORTD			3

#define				PIN0			0
#define				PIN1			1
#define				PIN2			2
#define				PIN3			3
#define				PIN4			4
#define				PIN5			5
#define				PIN6			6
#define				PIN7			7


#define				INPUT			0
#define				OUTPUT			1

#define				HIGH			1
#define				LOW				0



#endif